/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */
#include <com/sun/star/uno/genfunc.hxx>
#include <sal/log.hxx>
#include <typelib/typedescription.hxx>
#include <uno/data.h>
#include <osl/endian.h>
#include "bridge.hxx"
#include "cppinterfaceproxy.hxx"
#include "types.hxx"
#include "vtablefactory.hxx"
#include "call.hxx"
#include "share.hxx"

#include <stdio.h>
#include <string.h>

using namespace com::sun::star::uno;

//#define BRDEBUG

#include <rtl/strbuf.hxx>
#include <rtl/ustrbuf.hxx>
using namespace ::std;
using namespace ::osl;
using namespace ::rtl;


#ifndef ANDROID
#include <sys/sysmips.h>


#ifdef ANDROID
#include <unistd.h>

/*
    MARK: 几个重要术语的区分：
    type reference description
*/

namespace CPPU_CURRENT_NAMESPACE
{
  /*
      MARK: 什么是 complex struct 呢？
      simple type
      一点暂时理解的伪代码：
      bool is_complex_struct(Description)
      {
        Description -> CompoundDescription

        for (Reference in CompundDescription)
        {
          if (Reference is struct or exception)
          {
            Reference -> Description
            if is_complex_struct(Reference)
            {
              return true
            }
          }
          else if (Reference NOT SimpleType)
          {
            return true
          }
        }

        if (CompoundDescription has son && is_complex_struct(Son))
        {
          return true;
        }
        return false;
      }
      再简练一点：
      is_complex_struct --+-> member --+--> if NOT simple type and NOT struct or exception ----> TRUE
                          |            |
                          |            +--> if struct or exception ----> is_complex_struct(member) RECURSE
                          |
                          +-> has son-----> is_complex_struct(son) RECURSE
                          |
                          +-> FALSE
  */
  bool is_complex_struct(const typelib_TypeDescription * type)
  /*
      MARK：既然不是按引用传值，为什么要用 const 指定？
  */
  {
      const typelib_CompoundTypeDescription * p
          = reinterpret_cast< const typelib_CompoundTypeDescription * >(type);
      /*    typelib_CompoundTypeDescription : Type description for exception types.
            即：把 typelib_TypeDescription* 类型强行解释成 typelib_CompoundTypeDescription* 类型
      */
      for (sal_Int32 i = 0; i < p->nMembers; ++i)
      /*  nMembers : number of members
          MARK: 有怎样的“members”？
      */
      {
          if (p->ppTypeRefs[i]->eTypeClass == typelib_TypeClass_STRUCT ||
              p->ppTypeRefs[i]->eTypeClass == typelib_TypeClass_EXCEPTION)
          /*  
                            +--------------+       +---------------+         +------------+
                            |              |       | ppTypeRefs[i] |         |            |
                            |              |       +---------------+         |            |
                            |              |       |    .....      |         |            |
                            |              |       +---------------+         |            |
                            |    .....     |       | ppTypeRefs[2] |         |   ......   |
              +-------+     +--------------+       +---------------+         +------------+
              |   p   | --> |  ppTypeRefs  | ----> | ppTypeRefs[1] | ------> | eTypeClass |
              +-------+     +--------------+       +---------------+         +------------+
                            |    .....     |       | ppTypeRefs[0] |         |   ......   |
                            +--------------+       +---------------+         +------------+

             pointer   typelib_CompoundTypeDescription   pointer     typelib_typeDescriptionReference

              ppTypeRefs :   members of the struct or exception
              ppTypeRefs     为 typelib_TypeDescriptionReference** 类型
              ppTypeRefs[i]  为 typelib_TypeDescriptionReference*  类型
              eTypeClass     为 typelib_TypeClass                  类型
          */
          {
              typelib_TypeDescription * t = 0;
              TYPELIB_DANGER_GET(&t, p->ppTypeRefs[i]);
              bool b = is_complex_struct(t);
              /* 递归了
              */
              TYPELIB_DANGER_RELEASE(t);
              if (b) {
                  return true;
              }
          }
          else if (!bridges::cpp_uno::shared::isSimpleType(p->ppTypeRefs[i]->eTypeClass))
              return true;
      }
      if (p->pBaseTypeDescription != 0)
      /*  pBaseTypeDescription : pointer to base type description, else 0
          为 typelib_CompoundTypeDescription* 类型
          链表
      */
          return is_complex_struct(&p->pBaseTypeDescription->aBase);
      /*  aBase : inherits all members of typelib_TypeDescription
          aBase  为 typelib_TypeDescription  类型
          &aBase 为 typelib_TypeDescription* 类型
      */
      return false;
  }

  /*
                  no                          yes                                    yes
    simple type ------> struct or exception ------> size > 16 or is_complex_struct ------> TRUE
        |                        |                                |
        | yes                    | no                             | no
        v                        v                                v
      FALSE                    TRUE                             FALSE

    综合is_complex_struct、isSimpleType、return_in_hidden_param这三个方法，可以猜测
    return_in_hidden_param 判断了是不是“简单”的数据类型
    “简单”包括基础数据类型及数据量不大（<16），或是没有藏有什么“东西”（我也不知道是什么，is_complex_struct()没有看明白）
    的struct或exception
  */
  bool return_in_hidden_param( typelib_TypeDescriptionReference *pTypeRef )
  {
      if (bridges::cpp_uno::shared::isSimpleType(pTypeRef))
      /*  https://docs.libreoffice.org/bridges/html/namespacebridges_1_1cpp__uno_1_1shared.html
          Determines whether a type is a "simple" type (VOID, BOOLEAN, BYTE, SHORT, UNSIGNED SHORT
           LONG, UNSIGNED LONG, HYPER, UNSIGNED HYPER, FLOAT, DOUBLE, CHAR, or an enum type).
          Parameters
            type - a non-null pointer to a type description reference
          Returns
            true if the given type is "simple"
      */
          return false;
      else if (pTypeRef->eTypeClass == typelib_TypeClass_STRUCT ||
               pTypeRef->eTypeClass == typelib_TypeClass_EXCEPTION)
      /*
          mark: struct 和 exception 有什么特殊的？
      */
      {
          typelib_TypeDescription * pTypeDescr = 0;
          TYPELIB_DANGER_GET( &pTypeDescr, pTypeRef );
          /*  Gets a description from the reference. The description may not be locked by this call.
              You must use the TYPELIB_DANGER_RELEASE macro to release the description fetched with
              this macro.
              信息：1. 从 reference 获得 description
                   2. description 可能未锁，（可能所以）必须要手动释放该 description
              猜测：TYPELIB_DANGER_GET 把 typelib_TypeDescriptionReference * 转为了 typelib_TypeDescription**
              矛盾：TYPELIB_DANGER_GET 第一个参数是 typelib_TypeDescription** 类型
                                  而 pTypeDescr 是 typelib_TypeDescription*  类型
              纠正：silly，这里的&是取地址而不是引用
                    所以传给 TYPELIB_DANGER_GET 的第一个参数是 typelib_TypeDescription** 无误
          */

          //A Composite Type not larger than 16 bytes is returned in up to two GPRs
          bool bRet = pTypeDescr->nSize > 16 || is_complex_struct(pTypeDescr);
          /*  https://docs.libreoffice.org/bridges/html/namespaceCPPU__CURRENT__NAMESPACE.html
              CPPU_CURRENT_NAMESPACE::is_complex_struct
          */

          TYPELIB_DANGER_RELEASE( pTypeDescr );
          return bRet;
      }
      return true;
  }
}

namespace
{

  static typelib_TypeClass cpp2uno_call(
      bridges::cpp_uno::shared::CppInterfaceProxy * pThis,
      const typelib_TypeDescription * pMemberTypeDescr,
      typelib_TypeDescriptionReference * pReturnTypeRef, // 0 indicates void return
      sal_Int32 nParams, typelib_MethodParameter * pParams,
      void ** gpreg, void ** fpreg, void ** ovrflw,
      sal_uInt64 * pRegisterReturn /* space for register return */ )
  {
    /*  Most MIPS ABIs view the arguments as a struct, of which the
        first N words go in registers and the rest go on the stack.  If I < N, the
        With word might go in With integer argument register or the With
        floating-point one.  For these ABIs, we only need to remember the number
        of words passed so far.  We are interested only in n64 ABI,so it is the
        case.
        */
    /*
        https://www.openoffice.org/udk/cpp/man/cpp_bridges.html
        The cpp2uno_call() function reads C++ parameters from the call stack and 
        converts to binary (C-) UNO, if needed (C++ and UNO values are binary compatible
        concerning the memory layout). If the UNO dispatch call has returned and
        no exception has been signalled (pUnoExc), all out parameters are written back to C++.
    */
    unsigned int nREG = 0; // MARK

    fprintf(stderr, "cpp2uno_call:begin\n");

    // return
    typelib_TypeDescription * pReturnTypeDescr = 0;
    if (pReturnTypeRef) // type: typelib_TypeDescriptionReference
      TYPELIB_DANGER_GET( &pReturnTypeDescr, pReturnTypeRef );

    void * pUnoReturn = 0;
    void * pCppReturn = 0; // complex return ptr: if != 0 && != pUnoReturn, reconversion need // MARK

    if (pReturnTypeDescr)
    {
      if (CPPU_CURRENT_NAMESPACE::return_in_hidden_param( pReturnTypeRef ) )
      {
        pCppReturn = gpreg[nREG]; // complex return via ptr (pCppReturn) // gpreg is void** // MARK
        /*
            grep - void**
            grep[nREG] - 
        */
        nREG++;

        pUnoReturn = ( bridges::cpp_uno::shared::relatesToInterfaceType( pReturnTypeDescr )
            ? alloca( pReturnTypeDescr->nSize )
            : pCppReturn); // direct way
        /*
          bridges::cpp_uno::shared::relatesToInterfaceType
          Determines whether a type relates to an interface type (is itself an interface type, or might contain entities of interface type).
          Parameters
            type : a non-null pointer to a type description
          Returns
            true if the given type relates to an interface type
          
          alloca()
          ::description
          The alloca() function allocates size bytes of space in the stack
          frame of the caller.  This temporary space is automatically freed
          when the function that called alloca() returns to its caller.
          ::return value
          The alloca() function returns a pointer to the beginning of the
          allocated space.  If the allocation causes stack overflow,
          program behavior is undefined.
          
          若 pReturnTypeDescr 是接口类型或包含接口类型，则分配该type尺寸的内存（并返回指针），
          否则直接返回gpreg[nREG]

          MARK: 这是在做啥？
        */
        fprintf(stderr, "cpp2uno_call:complexreturn\n");
      }
      else
      /*
          也就是说 DANGER_GET 了个空？
      */
      {
        pUnoReturn = pRegisterReturn; // direct way for simple types

        fprintf(stderr, "cpp2uno_call:simplereturn\n");

      }
    }

    // pop this
    nREG++; // MARK??

    // stack space
    static_assert(sizeof(void *) == sizeof(sal_Int64), "### unexpected size!");
    /*
        static_assert 编译期间断言
        确保指针为64位（8字节）
    */
    // parameters
    void ** pUnoArgs = (void **)alloca( 4 * sizeof(void *) * nParams );
    /*
        即申请了 4 * nParams 个 void** 指针的空间
    */
    void ** pCppArgs = pUnoArgs + nParams;
    // indices of values this have to be converted (interface conversion cpp<=>uno)
    sal_Int32 * pTempIndices = (sal_Int32 *)(pUnoArgs + (2 * nParams));
    /*
        pTempIndices 指向了 pUnoArgs 指向的空间的正中间的位置，不过类型变成了 Int32
    */
    // type descriptions for reconversions
    typelib_TypeDescription ** ppTempParamTypeDescr = (typelib_TypeDescription **)(pUnoArgs + (3 * nParams));
    /*
        ppTempParamTypeDescr*
                +-- +-----------------+
                |   | void* x nParams |
                |   +-----------------+ <------ ppTempParamTypeDescr* - typelib_TypeDescription**
                |   | void* x nParams |
        alloca  |   +-----------------+ <------ pTempIndices - sal_Int32*
                |   | void* x nParams |
                |   +-----------------+ <------ pCppArgs     - void**
                |   | void* x nParams |
                +-- +-----------------+ <------ pUnoArgs     - void**

    */

    sal_Int32 nTempIndices   = 0;

    fprintf(stderr, "cpp2uno_call:nParams=%d\n", nParams);

    for ( sal_Int32 nPos = 0; nPos < nParams; ++nPos )
    {
      const typelib_MethodParameter & rParam = pParams[nPos];
      /*
          typelib_MethodParameter: Description of an interface method parameter.
      */

      typelib_TypeDescription * pParamTypeDescr = 0;
      TYPELIB_DANGER_GET( &pParamTypeDescr, rParam.pTypeRef );
      /*
          typelib_MethodParameter 的 pTypeRef 类型是 typelib_TypeDescriptionReference *
          老生常谈了，先申请 Description， 然后使用 DANGER_GET 从 Reference 获取 Description
          最后肯定有个 RELEASE 来销毁这个 Description（就在这个for 循环的结尾）
      */

      if (!rParam.bOut && bridges::cpp_uno::shared::isSimpleType( pParamTypeDescr )) // value
      {
        /*
            sal_Bool  bOut;
            true: the call type of this parameter is [out] or [inout]
            false: the call type of this parameter is [in]

            这里做了个判断，如果这个 parameter 的 call type 为 out 或 inout 并且 是一个简单类型，那么 ↓
        */

        fprintf(stderr, "cpp2uno_call:Param %u, type %u\n", nPos, pParamTypeDescr->eTypeClass);

        switch (pParamTypeDescr->eTypeClass)
        {
          case typelib_TypeClass_FLOAT:
          case typelib_TypeClass_DOUBLE:
            if (nREG < MAX_FP_REGS) {
              /*  定义在同目录的 share.hxx 里
                  #define MAX_FP_REGS    (8)
              */
              fprintf(stderr, "cpp2uno_call:fpr=%p\n", fpreg[nREG]);

              pCppArgs[nPos] = &(fpreg[nREG]);
              pUnoArgs[nPos] = &(fpreg[nREG]);
              /*
                  MARK：为什么 pCppArgs 和 pUnoArgs 都要存放一样的数据？
              */
            } else {

              fprintf(stderr, "cpp2uno_call:fpr=%p\n", ovrflw[nREG - MAX_FP_REGS]);

              pCppArgs[nPos] = &(ovrflw[nREG - MAX_FP_REGS]);
              pUnoArgs[nPos] = &(ovrflw[nREG - MAX_FP_REGS]);
              /*
                  看起来溢出了的数据在 ovrflw 处
              */
            }
            nREG++;
            break;


          default:
            if (nREG < MAX_GP_REGS) {

              fprintf(stderr, "cpp2uno_call:gpr=%p\n", gpreg[nREG]);

              pCppArgs[nPos] = &(gpreg[nREG]);
              pUnoArgs[nPos] = &(gpreg[nREG]);
            } else {

              fprintf(stderr, "cpp2uno_call:gpr=%p\n", ovrflw[nREG - MAX_GP_REGS]);

              pCppArgs[nPos] = &(ovrflw[nREG - MAX_GP_REGS]);
              pUnoArgs[nPos] = &(ovrflw[nREG - MAX_GP_REGS]);
            }
            nREG++;
            break;
            /*
                浮点数与非浮点数的唯一区别，就在于处理浮点数时使用 FP ， 处理普通数字时使用 GP
                看起来这里的 FP GP 并不是 frame pointer 和 global pointer
                而是 float p?? 和 general p?? MARK
                或许，是用 fp 作为浮点数栈指针， 而 gp 作为整型的栈指针？
            */
        }
        // no longer needed
        TYPELIB_DANGER_RELEASE( pParamTypeDescr );
      }
      else // ptr to complex value | ref
      {

        fprintf(stderr,"cpp2uno_call:ptr|ref\n");

        void *pCppStack;
        if (nREG < MAX_GP_REGS) {
          pCppArgs[nPos] = pCppStack = gpreg[nREG];
          /*
              注意，碰到复杂类型只存到 pCppArgs 了，并且只用 gpreg
              注意这里有个连等！
          */
        } else {
          pCppArgs[nPos] = pCppStack = ovrflw[nREG - MAX_GP_REGS];
        }
        nREG++;

        fprintf(stderr, "cpp2uno_call:pCppStack=%p\n", pCppStack);


        if (! rParam.bIn) // is pure out
        {
          // uno out is unconstructed mem!
          pUnoArgs[nPos] = alloca( pParamTypeDescr->nSize );
          /*
              上文中没有赋值的 pUnoArgs 在这里出现了
              所以这里只是申请了个空间，暂时啥也没动
          */
          pTempIndices[nTempIndices] = nPos; 
          /*
              这里存的是数字， pTempIndices 是 sal_Int32*，那么 pTempIndices[i] 是 sal_Int32 类型
              在进入循环之前，nTempIndices 是 0
          */
          // will be released at reconversion
          ppTempParamTypeDescr[nTempIndices++] = pParamTypeDescr;
          /*
              还是得搬出这张图来
                      +-- +-----------------+
                      |   | void* x nParams |
                      |   +-----------------+ <------ ppTempParamTypeDescr - typelib_TypeDescription**
                      |   | void* x nParams |
              alloca  |   +-----------------+ <------ pTempIndices - sal_Int32*
                      |   | void* x nParams |
                      |   +-----------------+ <------ pCppArgs     - void**
                      |   | void* x nParams |
                      +-- +-----------------+ <------ pUnoArgs     - void**
              可以看出上面一系列做了这样的操作
              1. pCppArgs[nPos] = pCppStack = gpreg[nREG];
                 把 gpreg[i] 里的指针存到了 pCppArgs
              2. pUnoArgs[nPos] = alloca( pParamTypeDescr->nSize );
                 根据 description 里描述的数据大小，申请对应的内存空间，并在 pUnoArgs 处保存指针
              3. pTempIndices[nTempIndices] = nPos;
                 往 pTempIndices 处存了一个数 nPos
              4. ppTempParamTypeDescr[nTempIndices++] = pParamTypeDescr;
                 往 ppTempParamTypeDescr 处存一个指针，指针内容是 description*
              
              说起来，（从下往上）第三块内存能放

              MXXK：我忽略了一个重要的问题，alloca既然是分配栈内存的，那么返回的指针是在低地址还是在高地址？
              不可能，因为像上图分配各个区域的时候，是从低地址开始的
          */
        }
        // is in/inout
        /*
            MARK: 所以 啥是 in/out ？？？？
        */
        else if (bridges::cpp_uno::shared::relatesToInterfaceType( pParamTypeDescr ))
        {
        /*
            Determines whether a type relates to an interface type (is itself an interface type,
            or might contain entities of interface type).
            Parameters
            type - a non-null pointer to a type description
            Returns
            true if the given type relates to an interface type
            Definition at line 41 of file types.cxx.
        */
          uno_copyAndConvertData( pUnoArgs[nPos] = alloca( pParamTypeDescr->nSize ),
              pCppStack, pParamTypeDescr,
              pThis->getBridge()->getCpp2Uno() );
          /**
              在 /include/uno/data.h 中

              Copy construct memory with given value. The size of the destination value
              must be larger or equal to the size of the source value. Interfaces are
              converted/ mapped by mapping parameter

              @param pDest            pointer to destination value memory
              @param pSource          pointer to source value
              @param pTypeDescr       type description of source
              @param mapping          mapping to convert/ map interfaces

              CPPU_DLLPUBLIC void SAL_CALL uno_copyAndConvertData(
                void * pDest, void * pSource,
                struct _typelib_TypeDescription * pTypeDescr, struct _uno_Mapping * mapping )
                SAL_THROW_EXTERN_C();

                对比上文只有in时的 pUnoArgs[nPos] = alloca( pParamTypeDescr->nSize );
                这里（in/out）看起来不仅申请了空间，还把内存赋值过去了
          */
          pTempIndices[nTempIndices] = nPos; // has to be reconverted
          // will be released at reconversion
          ppTempParamTypeDescr[nTempIndices++] = pParamTypeDescr;

          fprintf(stderr, "cpp2uno_call:related to interface,%p,%d,pUnoargs[%d]=%p\n",
                          pCppStack, pParamTypeDescr->nSize, nPos, pUnoArgs[nPos]);

        }
        else // direct way
        {
          pUnoArgs[nPos] = pCppStack;

          fprintf(stderr, "cpp2uno_call:direct,pUnoArgs[%d]=%p\n", nPos, pUnoArgs[nPos]);

          // no longer needed
          TYPELIB_DANGER_RELEASE( pParamTypeDescr );
        }
      }
    }

    fprintf(stderr, "cpp2uno_call2,%p,unoargs=%p\n", pThis->getUnoI()->pDispatcher, pUnoArgs);


    // ExceptionHolder
    uno_Any aUnoExc; // Any will be constructed by callee
    uno_Any * pUnoExc = &aUnoExc;

    // invoke uno dispatch call
    (*pThis->getUnoI()->pDispatcher)( pThis->getUnoI(), pMemberTypeDescr, pUnoReturn, pUnoArgs, &pUnoExc );
    /*
        bridges::cpp_uno::shared::CppInterfaceProxy * pThis
        https://docs.libreoffice.org/bridges/html/classbridges_1_1cpp__uno_1_1shared_1_1CppInterfaceProxy.html
       
        Position: bridges/inc/cppinterfaceproxy.hxx
        
        origin:
        // Interface for individual CPP--UNO bridges:
        Bridge * getBridge() { return pBridge; }
        uno_Interface * getUnoI() { return pUnoI; }
        typelib_InterfaceTypeDescription * getTypeDescr() { return pTypeDescr; }
        const OUString& getOid() const { return oid; }

        pUnoI 是 private 类型， getUnoI() 只是取出了这个 uno_Interface * 的类型

        查阅 uno_Interface 的定义，在 include/uno/dispatcher.h 中

        注释： The binary C uno interface description.
        代码： uno_DispatchMethod pDispatcher;
        对该行代码的注释： dispatch function

        uno_DispatchMethod 的定义同样在该文件中：

        typedef void (SAL_CALL * uno_DispatchMethod)(
          struct _uno_Interface * pUnoI,
          const struct _typelib_TypeDescription * pMemberType,
          void * pReturn,
          void * pArgs[],
          uno_Any ** ppException );
          
        Function pointer declaration for the binary C uno dispatch function. Any pure out or return
        value will be constructed by the callee, iff no exception is signalled.
        If an exception is signalled, the any *ppException is properly constructed by the callee,
        otherwise the pointer *ppException is set to 0.
        An attribute get call is indicated by a non-null return pointer.

        @param pUnoI        uno interface the call is performed on
        @param pMemberType  member type description of a method or attribute
        @param pReturn      pointer to return value memory;
                            pointer may be undefined if void method, null if attribute set call.
        @param pArgs        an array of pointers to arguments values.
                            (remark: the value of an interface reference stores a
                            uno_interface *, so you get it by *(uno_Interface **)pArgs[n])
        @param ppException  pointer to pointer to unconstructed any to signal an exception.

        MARK：这是在构造什么东西？？？

    */
    fprintf(stderr, "cpp2uno_call2,after dispatch\n");

    // in case an exception occurred...
    if (pUnoExc)
    {
      // destruct temporary in/inout params
      for ( ; nTempIndices--; )
      /*
          一种简略写法，从 nTempIndices - 1 (包括) 循环到 0 (包括)
          因为最后一次 nTempIndices + 1 了但是相应的内存空间没有赋值，所以首先 - 1 再继续操作
      */
      {
        sal_Int32 nIndex = pTempIndices[nTempIndices];

        if (pParams[nIndex].bIn) // is in/inout => was constructed
          uno_destructData( pUnoArgs[nIndex], ppTempParamTypeDescr[nTempIndices], 0 );
        TYPELIB_DANGER_RELEASE( ppTempParamTypeDescr[nTempIndices] );
      }
      if (pReturnTypeDescr)
        TYPELIB_DANGER_RELEASE( pReturnTypeDescr );

      CPPU_CURRENT_NAMESPACE::raiseException( &aUnoExc, pThis->getBridge()->getUno2Cpp() );
      // has to destruct the any
      // is here for dummy
      return typelib_TypeClass_VOID;
      /*
          MARK
      */
    }
    else // else no exception occurred...
    {
      // temporary params
      for ( ; nTempIndices--; )
      {
        sal_Int32 nIndex = pTempIndices[nTempIndices];
        typelib_TypeDescription * pParamTypeDescr = ppTempParamTypeDescr[nTempIndices];

        if (pParams[nIndex].bOut) // inout/out
        {
          // convert and assign
          uno_destructData( pCppArgs[nIndex], pParamTypeDescr, cpp_release );
          uno_copyAndConvertData( pCppArgs[nIndex], pUnoArgs[nIndex], pParamTypeDescr,
              pThis->getBridge()->getUno2Cpp() );
        }
        // destroy temp uno param
        uno_destructData( pUnoArgs[nIndex], pParamTypeDescr, 0 );

        TYPELIB_DANGER_RELEASE( pParamTypeDescr );
      }
      // return
      if (pCppReturn) // has complex return
      {
        if (pUnoReturn != pCppReturn) // needs reconversion
        {
          uno_copyAndConvertData( pCppReturn, pUnoReturn, pReturnTypeDescr,
              pThis->getBridge()->getUno2Cpp() );
          // destroy temp uno return
          uno_destructData( pUnoReturn, pReturnTypeDescr, 0 );
        }
        // complex return ptr is set to return reg
        *(void **)pRegisterReturn = pCppReturn;
      }
      if (pReturnTypeDescr)
      {
        typelib_TypeClass eRet = (typelib_TypeClass)pReturnTypeDescr->eTypeClass;
        TYPELIB_DANGER_RELEASE( pReturnTypeDescr );
        return eRet;
      }
      else
        return typelib_TypeClass_VOID;
    }
  }


  /**
   * is called on incoming vtable calls
   * (called by asm snippets)
   */
  /*
      sal_Int32 nFunctionIndex 源自 privateSnippetExecutor $v0， 不知晓用途 ×
         根据 codeSnippet ， v0 是传入的 functionIndex
         codeSnippet 由 addLocalFunctions 调用
         the function offset of the first vtable slot (typically coded into the code snippet for that vtable slot)
      sal_Int32 nVtableOffset  源自 privateSnippetExecutor $v1,  不知晓用途 ×
         根据 codeSnippet ， v1 是当时的 vtableOffset
         codeSnippet 由 addLocalFunctions 调用
         the offset of this vtable (needed to adjust the this pointer, typically
         coded into the code snippets for all the filled vtable slots)


      void ** gpreg ， 指向栈区 a0~a7 的存放起始处
      void ** fpreg ， 指向栈区 f12~f19 的存放起始处
      void ** ovrflw ， 指向栈底
      sal_uInt64 * pRegisterReturn ， 指向栈顶 
  */
  typelib_TypeClass cpp_vtable_call(
      sal_Int32 nFunctionIndex,
      sal_Int32 nVtableOffset,
      void ** gpreg, void ** fpreg, void ** ovrflw,
      sal_uInt64 * pRegisterReturn /* space for register return */ )
  {
    static_assert( sizeof(sal_Int64)==sizeof(void *), "### unexpected!" );
    /*
        MARK：所以这里是在检查 sal_Int64 还是 void *？
    */

    fprintf(stderr, "in cpp_vtable_call nFunctionIndex is %d\n", nFunctionIndex);
    fprintf(stderr, "in cpp_vtable_call nVtableOffset is %d\n", nVtableOffset);
    fprintf(stderr, "in cpp_vtable_call gp=%p, fp=%p, ov=%p\n", gpreg, fpreg, ovrflw);


    // gpreg:  [ret *], this, [other gpr params]
    // fpreg:  [fpr params]
    // ovrflw: [gpr or fpr params (properly aligned)]
    void * pThis;
    if (nFunctionIndex & 0x80000000 )
    {
      nFunctionIndex &= 0x7fffffff;
      pThis = gpreg[1];
      /*
          如果最高位为 1 ，那么把该位置 0
      */
    }
    else
    {
      pThis = gpreg[0];
    }
    /*
      结合 codeSnippet() ， 如果 HasHiddenParam ， 那么 pThis 得向上指 1 位
      MARK 为什么“ HasHiddenParam ”需要单独处理？
    */

    fprintf(stderr, "cpp_vtable_call, pThis=%p, nFunctionIndex=%d, nVtableOffset=%d\n",
                pThis, nFunctionIndex, nVtableOffset);


    pThis = static_cast< char * >(pThis) - nVtableOffset;
    
    bridges::cpp_uno::shared::CppInterfaceProxy * pCppI =
        bridges::cpp_uno::shared::CppInterfaceProxy::castInterfaceToProxy( pThis );
    /*
      CppInterfaceProxy * CppInterfaceProxy::castInterfaceToProxy(void * pInterface)
      pInterface == &pProxy->vtables (this emulated offsetof is not truly portable ):
    */
    fprintf(stderr, "cpp_vtable_call, pCppI=%p\n", pCppI);

    typelib_InterfaceTypeDescription * pTypeDescr = pCppI->getTypeDescr();

    if (nFunctionIndex >= pTypeDescr->nMapFunctionIndexToMemberIndex)
    {
      SAL_WARN(
          "bridges",
          "illegal " << OUString::unacquired(&pTypeDescr->aBase.pTypeName)
              << " vtable index " << nFunctionIndex << "/"
              << pTypeDescr->nMapFunctionIndexToMemberIndex);
      throw RuntimeException(
          ("illegal " + OUString::unacquired(&pTypeDescr->aBase.pTypeName)
           + " vtable index " + OUString::number(nFunctionIndex) + "/"
           + OUString::number(pTypeDescr->nMapFunctionIndexToMemberIndex)),
          (XInterface *)pThis);
    }

    // determine called method
    sal_Int32 nMemberPos = pTypeDescr->pMapFunctionIndexToMemberIndex[nFunctionIndex];
    assert(nMemberPos < pTypeDescr->nAllMembers);

    TypeDescription aMemberDescr( pTypeDescr->ppAllMembers[nMemberPos] );


    OString cstr( OUStringToOString( aMemberDescr.get()->pTypeName, RTL_TEXTENCODING_ASCII_US ) );
    fprintf(stderr, "calling %s, nFunctionIndex=%d\n", cstr.getStr(), nFunctionIndex );

    typelib_TypeClass eRet;
    switch (aMemberDescr.get()->eTypeClass)
    {
      case typelib_TypeClass_INTERFACE_ATTRIBUTE:
        {

    fprintf(stderr, "cpp_vtable_call interface attribute\n");

          typelib_TypeDescriptionReference *pAttrTypeRef =
              reinterpret_cast<typelib_InterfaceAttributeTypeDescription *>( aMemberDescr.get() )->pAttributeTypeRef;

          if (pTypeDescr->pMapMemberIndexToFunctionIndex[nMemberPos] == nFunctionIndex)
          {
            // is GET method
            eRet = cpp2uno_call( pCppI, aMemberDescr.get(), pAttrTypeRef,
                0, 0, // no params
                gpreg, fpreg, ovrflw, pRegisterReturn );
          }
          else
          {
            // is SET method
            typelib_MethodParameter aParam;
            aParam.pTypeRef = pAttrTypeRef;
            aParam.bIn      = sal_True;
            aParam.bOut     = sal_False;

            eRet = cpp2uno_call( pCppI, aMemberDescr.get(),
                0, // indicates void return
                1, &aParam,
                gpreg, fpreg, ovrflw, pRegisterReturn );
          }
          break;
        }
      case typelib_TypeClass_INTERFACE_METHOD:
        {

    fprintf(stderr, "cpp_vtable_call interface method\n");

          // is METHOD
          switch (nFunctionIndex)
          {
            case 1: // acquire()

    fprintf(stderr, "cpp_vtable_call method acquire\n");

              pCppI->acquireProxy(); // non virtual call!
              eRet = typelib_TypeClass_VOID;
              break;
            case 2: // release()

    fprintf(stderr, "cpp_vtable_call method release\n");

              pCppI->releaseProxy(); // non virtual call!
              eRet = typelib_TypeClass_VOID;
              break;
            case 0: // queryInterface() opt
              {

    fprintf(stderr, "cpp_vtable_call method query interface opt\n");

                typelib_TypeDescription * pTD = 0;
                TYPELIB_DANGER_GET( &pTD, reinterpret_cast< Type * >( gpreg[2] )->getTypeLibType() );
                if (pTD)
                {
                  XInterface * pInterface = 0;
                  (*pCppI->getBridge()->getCppEnv()->getRegisteredInterface)
                      ( pCppI->getBridge()->getCppEnv(),
                      (void **)&pInterface,
                      pCppI->getOid().pData,
                      reinterpret_cast<typelib_InterfaceTypeDescription *>( pTD ) );

                  if (pInterface)
                  {
                    ::uno_any_construct( reinterpret_cast< uno_Any * >( gpreg[0] ),
                                         &pInterface, pTD, cpp_acquire );

                    pInterface->release();
                    TYPELIB_DANGER_RELEASE( pTD );

                    reinterpret_cast<void **>( pRegisterReturn )[0] = gpreg[0];
                    eRet = typelib_TypeClass_ANY;
                    break;
                  }
                  TYPELIB_DANGER_RELEASE( pTD );
                }
              } // else perform queryInterface()
            default:

    fprintf(stderr, "cpp_vtable_call method query interface\n");

              typelib_InterfaceMethodTypeDescription *pMethodTD =
                  reinterpret_cast<typelib_InterfaceMethodTypeDescription *>( aMemberDescr.get() );

              eRet = cpp2uno_call( pCppI, aMemberDescr.get(),
                  pMethodTD->pReturnTypeRef,
                  pMethodTD->nParams,
                  pMethodTD->pParams,
                  gpreg, fpreg, ovrflw, pRegisterReturn );
          }
          break;
        }
      default:
        {

    fprintf(stderr, "cpp_vtable_call no member\n");

          throw RuntimeException( "no member description found!", (XInterface *)pThis );
        }
    }

    return eRet;
  }

  extern "C" void privateSnippetExecutor( ... );

  /*
      MXXK: privateSnippetExecutor() 的实体在哪？
      回答： 在call.s里
  */

  int const codeSnippetSize = 0x44;

  /*
      0x44: BIN(1000100) DEC(88)
      MXXK: 为什么是0x44?
      回答：因为生成的 codeSnippet 指令占 44 个字节
  */

  /*
      总结：生成了一段汇编，该段汇编：
      1. 把 functionIndex 放到 $v0
      2. 把 privateSnippetExecutor 放到 $t0
      3. 把 cpp_vtable_call 放到 $t9
      4. 把 vtableOffset 放到 $v1
      5. 跳转到 $t0，即运行 privateSnippetExecutor 函数（在 call.s ）里
  */
  unsigned char *  codeSnippet( unsigned char * code,
      sal_Int32 functionIndex, sal_Int32 vtableOffset,
      bool bHasHiddenParam )
  /*
      从x86的 cpp2uno.cxx 扒过来的部分

      Generate a trampoline that redirects method calls to
      privateSnippetExecutor().
    
      privateSnippetExecutor() saves all the registers that are used for
      parameter passing on x86_64, and calls the cpp_vtable_call().
      When it returns, privateSnippetExecutor() sets the return value.
    
      Note: The code snippet we build here must not create a stack frame,
      otherwise the UNO exceptions stop working thanks to non-existing
      unwinding info.

      作为参考，扒拉
            code
            functionOffset++
            vtableOffset
            CPPU_CURRENT_NAMESPACE::return_in_hidden_param(reinterpret_cast<typelib_InterfaceAttributeTypeDescription * >(member)->pAttributeTypeRef));
  */

  {

     fprintf(stderr,"in codeSnippet functionIndex is %d\n", functionIndex);
     fprintf(stderr,"in codeSnippet vtableOffset is %d\n", vtableOffset);
     fflush(stderr);


    if ( bHasHiddenParam )
      functionIndex |= 0x80000000;
    /*
      若 HasHiddenParam ，把最高位置 1 （因为是32位的类型）
      MARK ，不完全知道为什么这样做
      这里的位运算并没有实际对数据造成改变，只是附带了一些信息，
      cpp_vtable_call() 里会在读出这个信息后改回去
    */

    unsigned int * p = (unsigned int *) code;

    assert((((unsigned long)code) & 0x3) == 0 );  //aligned to 4 otherwise a mistake
    /*
        0x3 = 0011，4B 对齐？
    */

    /* generate this code */
    /*
       # index
        0:   3c020000        lui     v0,0x0
        4:   34420000        ori     v0,v0,0x0
       # lui 把 16 位立即数填充到寄存器高 16 位，低 16 位补 0
       # MXXK：64位的MIPS指令中，这条会不会是填充32位呢？
       # No，指令字长是32位，给立即数的部分依然是16位
       # ori 把寄存器与立即数相与
       # MARK：与0相与，这不是什么也没做吗？

       # privateSnippetExecutor
        8:   3c0c0000        lui     t0,0x0
        c:   358c0000        ori     t0,t0,0x0
       10:   000c6438        dsll    t0,t0,0x10
       14:   358c0000        ori     t0,t0,0x0
       18:   000c6438        dsll    t0,t0,0x10
       1c:   358c0000        ori     t0,t0,0x0
       # dsll 双字逻辑左移
       # MARK：MIPS64中的字是32位吗？
       # 

       # cpp_vtable_call
       20:   3c190000        lui     t9,0x0
       24:   37390000        ori     t9,t9,0x0
       28:   0019cc38        dsll    t9,t9,0x10
       2c:   37390000        ori     t9,t9,0x0
       30:   0019cc38        dsll    t9,t9,0x10
       34:   37390000        ori     t9,t9,0x0
       # offset
       38:   3c030000        lui     v1,0x0
       3c:   01800008        jr      t0
       40:   34630000        ori     v1,v1,0x0
     */
     /*
        每条指令有32位长，即4B，那么每条指令所在的地址为0、4、8、c(12)、10(16)
     */
     /*
        functioIndex           Int32
        privateSnippetExecutor Int64
        cpp_vtable_call        Int64
        vtableOffset           Int32
     */
    * p++ = 0x3c020000 | ((functionIndex>>16) & 0x0000ffff);
    /*
        0011 1100 0000 0010 (0000 0000 0000 0000) 替换为 functionIndex 的 16 ~ 31 位
        opcode: 001111 -> 0F -> lui
        rs    : 00000  -> $zero
        rt    : 00010  -> $v0
        把 $v0 的高16位替换为 functionIndex 的 16 ~ 31 位
    */
    * p++ = 0x34420000 | (functionIndex & 0x0000ffff);
    /*
        0011 0100 0100 0010 (0000 0000 0000 0000) 替换 functionIndex 的 0 ~ 15 位
        opcode: 001101 -> 0D -> ori
        rs    : 00010  -> 2  -> $v0
        rt    : 00010  -> 2  -> $v0
        喔，前面作者写的注释里的0x0实际上需要被替换
        把 $v0 的低16位替换位 functionIndex 的 0 ~ 15 位
    */
    * p++ = 0x3c0c0000 | ((((unsigned long)privateSnippetExecutor) >> 48) & 0x0000ffff);
    * p++ = 0x358c0000 | ((((unsigned long)privateSnippetExecutor) >> 32) & 0x0000ffff);
    * p++ = 0x000c6438;
    * p++ = 0x358c0000 | ((((unsigned long)privateSnippetExecutor) >> 16) & 0x0000ffff);
    * p++ = 0x000c6438;
    * p++ = 0x358c0000 | (((unsigned long)privateSnippetExecutor) & 0x0000ffff);
    /*
        将 privateSnippetExecutor 的地址给到 $t0
    */
    * p++ = 0x3c190000 | ((((unsigned long)cpp_vtable_call) >> 48) & 0x0000ffff);
    * p++ = 0x37390000 | ((((unsigned long)cpp_vtable_call) >> 32) & 0x0000ffff);
    * p++ = 0x0019cc38;
    * p++ = 0x37390000 | ((((unsigned long)cpp_vtable_call) >> 16) & 0x0000ffff);
    * p++ = 0x0019cc38;
    * p++ = 0x37390000 | (((unsigned long)cpp_vtable_call) & 0x0000ffff);
    /*
        将 cpp_vtable_call 的地址放到 $t9
    */
    * p++ = 0x3c030000 | ((vtableOffset>>16) & 0x0000ffff);
    * p++ = 0x01800008;
    * p++ = 0x34630000 | (vtableOffset & 0x0000ffff);
    /*
        将 vtableOffset 存放到 $v1
        MXXK: 这里为什么要jr？
        推测：应该是延迟指令槽，把填充 $v1 低 16 位的指令放到了 jr 之后
        指向的这段代码如果要执行，那么会跳转到t0，即执行 privateSnippetExecutor() 函数
        所以，MXXK： privateSnippetExecutor() 函数在哪？是怎么执行的？
        privateSnippetExecutor() 在同文件夹下的 call.s 里，看起来是在执行这个 codeSnippet 时拉起的
        MARK： codeSnippet 被插入到了哪里？是怎么被运行的？
        猜测：这种有一部分调用入口单独分离出来的情况，记得之前看虚函数教程的时候见过……虚表？

    */
    return (code + codeSnippetSize);

  }

}

/*
应该是将缓存内容写回内存
*/
void bridges::cpp_uno::shared::VtableFactory::flushCode(unsigned char const *bptr, unsigned char const *eptr)
{
#ifndef ANDROID
  (void) bptr;
  (void) eptr;
  sysmips(FLUSH_CACHE, 0, 0, 0);
#else
  cacheflush((long) bptr, (long) eptr, 0);
}

struct bridges::cpp_uno::shared::VtableFactory::Slot { void * fn; };

bridges::cpp_uno::shared::VtableFactory::Slot *
bridges::cpp_uno::shared::VtableFactory::mapBlockToVtable(void * block)
/*
    Given a pointer to a block, turn it into a vtable pointer.
*/
{
    return static_cast< Slot * >(block) + 2;
}

// 286 codeSnippetSize:0x44;
/*
    Calculate the size of a raw vtable block.

    Parameters
    slotCount - the number of virtual function slots the returned vtable block shall support
                (if there are any platform-specific slots, like an RTTI pointer, or a pointer
                to a destructor, they are not covered by slotCount)
    Returns
    the size of the raw vtable block, in bytes

    也就是说 slotCount 并不包括那两个 —— 用作 null 和 desctructor 的（见initializeBlock
    注意，每个槽增加了codeSnippetSize
    MARK，WHY？
*/
std::size_t bridges::cpp_uno::shared::VtableFactory::getBlockSize(
    sal_Int32 slotCount)
{
    return (slotCount + 2) * sizeof (Slot) + slotCount * codeSnippetSize;
}


/*
    Initialize a raw vtable block.

    Parameters
    block - the start address of the raw vtable block
    slotCount - the number of slots
    vtableNumber - zero-based count across all the most derived type's vtables (for vtable's "offset to top" slot)
    type - non-null most derived type (for vtable's "typeinfo pointer" slot)
    Returns
    a pointer past the last vtable slot
    
    这里并没有传入 vtableNumber ，而生成的 slots 大小应该由 block 决定

    初始化Slot list，最后返回的指针指向了slot list 最后一个元素的顶部
    即，最后的指针指向了slots所在内存区域的结尾（顶部）
*/
bridges::cpp_uno::shared::VtableFactory::Slot *
bridges::cpp_uno::shared::VtableFactory::initializeBlock(
    void * block, sal_Int32 slotCount, sal_Int32,
    typelib_InterfaceTypeDescription *)
{
    Slot * slots = mapBlockToVtable(block);
    slots[-2].fn = 0; //null
    slots[-1].fn = 0; //destructor
    return slots + slotCount;
}

/*
    https://docs.libreoffice.org/bridges/html/classbridges_1_1cpp__uno_1_1shared_1_1VtableFactory.html#aa9e8f20f20514109a6b1c8780ce84487

    unsigned char * bridges::cpp_uno::shared::VtableFactory::addLocalFunctions	(
      Slot ** 	slots,
      unsigned char * 	code,
      sal_PtrDiff 	writetoexecdiff,
      typelib_InterfaceTypeDescription const * 	type,
      sal_Int32 	functionOffset,
      sal_Int32 	functionCount,
      sal_Int32 	vtableOffset 
    )	
    Fill the vtable slots corresponding to all local (i.e., not inherited) functions of a 
    given interface type (and generate any necessary code snippets for them).

    Parameters
      slots - on input, points past the vtable slot to be filled with the last virtual
              function local to the given type; on output, points to the vtable slot 
              filled with the first virtual function local to the given type
      code - points to the start of the area where code snippets can be generated
      writetoexecdiff - when the same code area is mapped twice, once for writing for code-generation,
                        and once for code-execution, then this records the offset from a writable address
                        to its executable address
      type - the interface type description for which to generate vtable slots
      functionOffset - the function offset of the first vtable slot (typically coded into the
                       code snippet for that vtable slot)
      functionCount - the number of vtable slots to fill (the number of local functions of the
                      given type, passed in so that it doesn't need to be recomputed)
      vtableOffset - the offset of this vtable (needed to adjust the this pointer, typically
                     coded into the code snippets for all the filled vtable slots)
    Returns
      a pointer to the remaining code snippet area
*/
/*
    对于 sal_PtrDiff ，根据 include/sal/types.h 
    #if SAL_TYPES_SIZEOFPOINTER == 4
      typedef sal_Int32           sal_PtrDiff;
    #elif SAL_TYPES_SIZEOFPOINTER == 8
      typedef sal_Int64           sal_PtrDiff;
    也就是说，pointer的尺寸是 64， 则 sal_PtrDiff 其实就是 sal_Int64
*/
/*
    addLocalFunctions 由 VtableFactory::createVtables() 调用
    createVtables     在 bridges/source/cpp_uno/shared/vtablefactory.cxx 实现，由 VtableFactory::getVtables() 调用
    getVtables        在 bridges/source/cpp_uno/shared/cppinterfaceproxy.cxx 实现，由 CppInterfaceProxy::create() 调用
    create()          在 bridges/source/cpp_uno/shared/bridge.cxx 实现，由 uno2cppMapping() 调用
    uno2cppMapping()  是 Bridge 类的友元函数 ，该类在 bridges/source/cpp_uno/shared/bridge.hxx 里定义
*/
/*
           +-----------------+
           |                 |
           |    .........    |
           |                 |
           +-----------------+
           |                 |
    +----->| CodeSnippet 02  |
    |      |                 |
    |      +-----------------+
    |      |                 |
    |  +-->| CodeSnippet 01  |
    |  |   |                 |
    |  |   +-----------------+ <----- code(start)
    |  |   |    Slot   n     |
    |  |   +-----------------+
    |  |   |      ...        |
    |  |   +-----------------+
    +--+---|    Slot  02     |
       |   +-----------------+
       +---|    Slot  01     |
           +-----------------+ <----- s(start)

    图示的 Slot 里的 fn* 指向的区域没有加上 writetoexecdiff 偏移
*/
/*
    传入数据：
      writetoexecdiff = reinterpret_cast<sal_uIntPtr>(block.exec) - reinterpret_cast<sal_uIntPtr>(block.start)
      type = type2
      functionOffset = baseOffset.getFunctionOffset(type2->aBase.pTypeName)
      functionCount = bridges::cpp_uno::shared::getLocalFunctions(type2)
*/
/*
    MARK：7-14
    现在有几个量对不起来：
    getPrimaryFunctions(type)  [即 slotcount ]
    getLocalFunctions(type) [即 functionCount]
    baseOffset.getFunctionOffset(type2->aBase.pTypeName) [即 functionOffset ]
    blocks.size()


*/
unsigned char * bridges::cpp_uno::shared::VtableFactory::addLocalFunctions(
    Slot ** slots, unsigned char * code, sal_PtrDiff writetoexecdiff,
    typelib_InterfaceTypeDescription const * type, sal_Int32 functionOffset,
    sal_Int32 functionCount, sal_Int32 vtableOffset)
{
   (*slots) -= functionCount; // *slots 类型为 Slot*，MARK，所以这里的functioncount是多大呢？
    Slot * s = *slots;        // 不知道赋给了哪个代码块


   fprintf(stderr, "in addLocalFunctions functionOffset is %d\n", functionOffset);
   fprintf(stderr, "in addLocalFunctions vtableOffset is %d\n", vtableOffset);
   fprintf(stderr, "nMembers=%d\n", type->nMembers);
   fflush(stderr);

  /*
      Not all members are always initialized (not yet initialized members being null); there are three levels:

      Minimally, only aBase, pBaseTypeDescription, aUik, nBaseTypes, and ppBaseTypes are initialized;
          aBase.bComplete is false. This only happens when an interface type description is created with
          typelib_static_mi_interface_type_init or typelib_static_interface_type_init.
      At the next level, nMembers, ppMembers, nAllMembers, ppAllMembers are also initialized;
          aBase.bComplete is still false. This happens when an interface type description is created with
          typelib_typedescription_newMIInterface or typelib_typedescription_newInterface.
      At the final level, pMapMemberIndexToFunctionIndex, nMapFunctionIndexToMemberIndex,
          and pMapFunctionIndexToMemberIndex are also initialized; aBase.bComplete is true.
          This happens after a call to typelib_typedescription_complete.
  */
  for (sal_Int32 i = 0; i < type->nMembers; ++i) {
    /*
        看起来这个 nMember 只包括了 local function 
        而 slot 的总数是包括 primary function 的
        MARK ： 上面可能在胡说
    */
    typelib_TypeDescription * member = 0;
    TYPELIB_DANGER_GET(&member, type->ppMembers[i]);
    /*  TYPELIB_DANGER_GET在include/typelib/typedescription.h中
        member 的类型是 typelib_TypeDescription 指针 ，这是一个链表
    */
    assert(member != 0);
    /*  也就是说得确保 member 不为空
        typidescription.h 注释里说， TYPELIB_DANGER_GET 从 reference 中获取了 description
        reference description 这是啥？ MARK
    */
    switch (member->eTypeClass) {
    /*  member->eTypeClass 的类型是typelib_TypeClass (注释：type class of type)
        typelib_TypeClass 在 typeclass.h 中，为枚举类型，其中枚举了各种数据类型
    */
      case typelib_TypeClass_INTERFACE_ATTRIBUTE:
      /*  枚举值26（注释：type class of interface attribute）
      */
        // Getter:
        (s++)->fn = code + writetoexecdiff;
        /*  这时候指针 s 可能指向 Slot 列表的 0 或者 -2 的位置
            具体的位置得看 functionCount 是 initializeBlock() 申请的块数，还是 +2 后的块数
            code: points to the start of the area where code snippets can be generated
            writetoexecdiff: when the same code area is mapped twice, once for writing for
                             code-generation, and once for code-execution, then this records
                             the offset from a writable address to its executable address
            
            然后 s 指向了 Slot 列表里的下一个槽
        */
        code = codeSnippet(
            code, functionOffset++, vtableOffset,
            CPPU_CURRENT_NAMESPACE::return_in_hidden_param(
              reinterpret_cast<
              typelib_InterfaceAttributeTypeDescription * >(
                member)->pAttributeTypeRef));
        /*
            这里把 typelib_TypeDescriptionReference 强制转换成了 typelib_InterfaceAttributeTypeDescription
            然后查看是不是复杂类型(return_in_hidden_param)

            执行 codeSnippet ，会在原code指向的地址生成一些汇编代码，该段汇编会做如下几件事：
            1. 把 functionOffset 放到 $v0
            2. 把 privateSnippetExecutor() 入口放到 $t0
            3. 把 cpp_vtable_call() 入口放到 $t9
            4. 把 vtableOffset 放到 $v1
            5. 跳转到 privateSnippetExecutor()

            codeSnippet执行完后
            code = code + codeSnippetSize;
        */
        /*
            根据 rv 的调用规范，
        */
        // Setter:
        if (!reinterpret_cast<
            typelib_InterfaceAttributeTypeDescription * >(
              member)->bReadOnly)
        /*
            喔，因为是属性，所以如果可写的话还需要一个 setter ？
        */
        {
          (s++)->fn = code + writetoexecdiff;
          code = codeSnippet(code, functionOffset++, vtableOffset, false);
        }
        break;

      case typelib_TypeClass_INTERFACE_METHOD:
      /*  枚举值25（注释：type class of interface method）
      */
        (s++)->fn = code + writetoexecdiff;
        code = codeSnippet(
            code, functionOffset++, vtableOffset,
            CPPU_CURRENT_NAMESPACE::return_in_hidden_param(
              reinterpret_cast<
              typelib_InterfaceMethodTypeDescription * >(
                member)->pReturnTypeRef));
        break;

      default:
        assert(false);
        break;
    }
    TYPELIB_DANGER_RELEASE(member);
  }
  return code;
}



/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
