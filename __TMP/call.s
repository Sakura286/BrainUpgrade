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

        .text
        .globl	privateSnippetExecutor
.LFB0 = .
        .cfi_startproc
        .cfi_personality 0x80,DW.ref.__gxx_personality_v0
        .cfi_lsda 0,.LLSDA0
        .ent	privateSnippetExecutor
        .type	privateSnippetExecutor, @function
privateSnippetExecutor:
        addi	sp,sp,-160
        .cfi_def_cfa_offset 160
        sd	ra,152(sp)
        .cfi_offset 31, -8
.LEHB0 = .
        // Save the float point registers
        // 将浮点寄存器内的64位存内存
        fsd	fa1,80(sp)
        fsd	fa2,88(sp)
        fsd	fa3,96(sp)
        fsd	fa4,104(sp)
        fsd	fa5,112(sp)
        fsd	fa6,120(sp)
        fsd	fa7,128(sp)
        fsd	fa8,136(sp)
        // Save the general purpose registers
        sd	a0,16(sp)
        sd	a1,24(sp)
        sd	a2,32(sp)
        sd	a3,40(sp)
        sd	a4,48(sp)
        sd	a5,56(sp)
        sd	a6,64(sp)
        sd	a7,72(sp)
        // Load arguments
        // a0=index
        add	a0,t4,zero
        // a1=offset
        add	a1,t5,zero
        // a2=gpregptr
        addi	a2,sp,16
        // a3=fpregptr
        addi	a3,sp,80
        // a4=ovrflw
        addi	a4,sp,160
        /*
        MIPS
        +----------------+ 160 <------ ovrflw & old sp
        | return address |
        +----------------+ 152
        |  what in here? |
        +----------------+ 144
        |      f19       |
        +----------------+ 136
        |                |
        |      ....      |
        |                |
        +----------------+
        |      f12       |
        +----------------+ 80  <------ fpregptr
        |      a7        |
        +----------------+ 72
        |                |
        |      ....      |
        |                |
        +----------------+
        |      a0        |
        +----------------+ 16  <------ gpregptr
        |                |
        |     empty      |
        |                |
        +----------------+ 0   <------ sp
        
        MXXK: 在reference card里，MIPS是没有 a4~a7 寄存器的：
        a0~a3 t0~t7 s0~s7 t8~t9

        但是参考了某一个文档
        https://chromium.googlesource.com/v8/v8/+/3.29.45/src/mips64/simulator-mips64.h?autodive=0%2F%2F
        a0~a7 t0~t4 s0~s7 t8~t9

        可见原来的 t0~t3 被替换为了函数参数寄存器
        MARK：所以说 reference card 里的调用标准仅供参考？那到底怎么才能找到所需的呢？

        */

        // Call cpp_vtable_call
        // 因为在 codeSnippet 里， cpp_vtable_call 的地址放在了 t9
        // rv 的 codeSnippet 里， cpp_vtable_call 的地址放在了 t6
        // a5=retregptr
        move	a5,sp
        jalr	ra,t6,0
        
        /*
            MARK: 跳转 cpp_vtable_call 后的汇编还需要进一步理解
        */

.LEHE0 = .
        // Perform return value
        /*
            MARK: 我不明白为什么要这样比较
            猜测：在typelib里，float是10，double是11，这是在判断返回值是否为浮点数
            我至今不明白为什么要用两个寄存器作返回值……

            顺便，这里的浮点返回寄存器我不知道怎么替换，就把仅有的两个顶上了 MARK：Linus说：“先这样办。”
            bullshit
        */
        li	a1,10
        beq	a0,a1,.Lfloat
        li	a1,11
        beq	a0,a1,.Lfloat
        fld	fa0,0(sp)
        fld	fa1,8(sp)
        ld	a0,0(sp)
        ld	a1,8(sp)
        jal     zero,.Lfinish
.Lfloat:
        fld	fa0,0(sp)
        fld	fa1,8(sp)

.Lfinish:
        ld	ra,152(sp)
        .cfi_restore 31
        jalr	zero,ra,0
        addi	sp,sp,160
        .cfi_def_cfa_offset 0

        .end	privateSnippetExecutor
        .cfi_endproc
.LFE0:
        .globl	__gxx_personality_v0
        .section	.gcc_except_table,"aw",@progbits
        .align	3
.LLSDA0:
        .byte	0xff
        .byte	0x80
        .uleb128 .LLSDATT0-.LLSDATTD0
.LLSDATTD0:
        .byte	0x1
        .uleb128 .LLSDACSE0-.LLSDACSB0
.LLSDACSB0:
        .uleb128 .LEHB0-.LFB0
        .uleb128 .LEHE0-.LEHB0
        .uleb128 0
        .uleb128 0
.LLSDACSE0:
        .byte	0x7f
        .byte	0
        .align	3
        .8byte	DW.ref._ZTIi
.LLSDATT0:
        .byte	0x1
        .byte	0
        .text
        .size	privateSnippetExecutor, .-privateSnippetExecutor
        .hidden	DW.ref._ZTIi
        .weak	DW.ref._ZTIi
        .section	.data.DW.ref._ZTIi,"awG",@progbits,DW.ref._ZTIi,comdat
        .align	3
        .type	DW.ref._ZTIi, @object
        .size	DW.ref._ZTIi, 8
DW.ref._ZTIi:
        .dword	_ZTIi
        .hidden	DW.ref.__gxx_personality_v0
        .weak	DW.ref.__gxx_personality_v0
        .section	.data.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
        .align	3
        .type	DW.ref.__gxx_personality_v0, @object
        .size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
        .dword	__gxx_personality_v0
