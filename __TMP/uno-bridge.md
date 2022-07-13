# Memo in UNO

## 7-13 小结

1. 为了理解 cpp2uno.cxx 的源代码，翻阅了一定的资料与源代码，并为大部分的代码片段做了较为详尽的笔记或图解，虽然暂时核心内容（我觉得是传入数据的组织方式）还不求甚解
2. 理清了mips64 里 call.s 与 cpp2uno.cxx 里的调用关系，整体代码分成了两块：
   1. 将 vtable block 转为 slot 列表，在 slot 列表之前增添析构函数，并对每个 slot 添加 codeSnippet；包括 `flushCode`、`mapBlockToVtable`、`getBlockSize`、`initializeBlock`、`addLocalFunctions`、`codeSnippet`
   2. `codeSnippet` 函数使用位操作生成了汇编代码，该段汇编将`cpp_vtable_call`、`privateSnippetExecutor`的地址放到合适的寄存器，并跳转`privateSnippetExecutor`；`privateSnippetExecutor`在`call.s`里，开辟栈并将大量寄存器压栈，保存了栈内数据地址的指针后调用了`cpp_vtable_call`，而`cpp_vtable_call`在运行过程中又调用了`cpp2uno_call`，`cpp2uno_call`又调用了`return_in_hidden_param` `is_complex_struct`来判断数据的类型是否为复杂数据类型（接口、方法）等，开辟内存存放指向 cpp 数据与 uno 数据的指针，并调用外部定义的函数来进行数据转换

3. （错误尝试）对此项目使用IDE Clion，尝试无果后发现 Jetbrain 官方明确表示暂时不支持 LibreOffice 的Makefile —— 继续VS Code
4. （未尝试）暂时对此段代码本身的理解就到这里了，需要了解数据的组织方式，目前能想到的有三种途径
   1. 读官方文档，了解 uno 有关的各种数据类型
   2. 在 qemu-system 里调试单元测试，观察数据是怎样传入的
   3. 顺着源代码扒拉出调用的逻辑链（见下），不过emm……读起来大概挺费事，先大致浏览建立个印象


```plain
addLocalFunctions 在 bridges/source/cpp_uno/shared/vtablefactory.cxx 实现
                  由 VtableFactory::createVtables() 调用
createVtables     在 bridges/source/cpp_uno/shared/vtablefactory.cxx 实现
                  由 VtableFactory::getVtables() 调用
getVtables        在 bridges/source/cpp_uno/shared/cppinterfaceproxy.cxx 实现
                  由 CppInterfaceProxy::create() 调用
create()          在 bridges/source/cpp_uno/shared/bridge.cxx 实现
                  由 uno2cppMapping() 调用
uno2cppMapping()  是 Bridge 类的友元函数 ，该类在 bridges/source/cpp_uno/shared/bridge.hxx 里定义
```



## 资料

[Lazy Hackers Guide To Porting](https://wiki.openoffice.org/wiki/Lazy_Hackers_Guide_To_Porting)

[Implementing a C++ - UNO bridge](https://svn.apache.org/repos/asf/openoffice/ooo-site/trunk/content/udk/cpp/man/cpp_bridges.html)

[A Guide to C++ UNO](https://svn.apache.org/repos/asf/openoffice/ooo-site/trunk/content/udk/cpp/man/tutorial/unointro.html)

[UNO C++ Bridges - OpenOffice Wiki](https://wiki.openoffice.org/wiki/Documentation/DevGuide/AdvUNO/UNO_C%2B%2B_Bridges)

[LibreOffice Developer's Guide: Chapter 5 - Advanced UNO](https://wiki.documentfoundation.org/Documentation/DevGuide/Advanced_UNO#UNO_C.2B.2B_Bridges)

RISCV调用规范
[Chapter 18 - Calling Convention](https://riscv.org/wp-content/uploads/2015/01/riscv-calling.pdf)

### 一个查阅类名及命名空间的好办法

1. 打开[LibreOffice Modules](https://docs.libreoffice.org/)
2. 随便点开一个模块，例如[bridges (libreoffice.org)](https://docs.libreoffice.org/bridges.html)
3. 把最后形如`bridges.html`的部分改为`bridges/html`的形式

这是个查阅bridge部分的好网站
可以查阅命名空间：[LibreOffice Module bridges (master): Namespace List](https://docs.libreoffice.org/bridges/html/namespaces.html)
可以查阅类：[LibreOffice Module bridges (master): Class List](https://docs.libreoffice.org/bridges/html/annotated.html)
可以查阅文件：[LibreOffice Module bridges (master): File List](https://docs.libreoffice.org/bridges/html/files.html)

## 关于 loongarch64 `cpp2uno.cxx`

### 1. 未命名命名空间

直接namespace { }，没有名字，见  `#47`~`#398`

unnamed namespace，`namespace`后紧接花括号，其中的变量与函数不能跨文件使用，相当于在文件中进行静态声明

### 2. 全局命名空间

global namespace，在全局作用域中定义的名字，使用时双冒号左侧的内容可省略

### dlopen dlsym dlclose

**MARK**

### 3. extern "C"

`#45` `#224` `#317`

**MARK**

### 4. typelib等

`typelib_InterfaceTypeDescription` `#426`
`typelib_TypeDescription` `#432`

`TYPELIB_DANGER_GET()` `#433`
参考：[LibreOffice: typelib/typedescription.h File Reference](https://api.libreoffice.org/docs/cpp/ref/a00251.html)

`typelib_TypeClass_INTERFACE_ATTRIBUTE` `#436`
`typelib_InterfaceAttributeTypeDescription` `#438`

引用链1：`include/typedescription.hxx` -> `include/tepeclass.h`

## 关于 mips64 `cpp2uno.cxx`

### 1. typelib等

同样有 `TYPELIB_DANGER_GET()`等代码

### 2. fprintf

看到很多debug信息都使用fprintf函数输出，所以所以输出到哪儿？如何进行这样的调试呢？

和这个`https://wiki.openoffice.org/wiki/Uno/Binary/Spec/Debug_Bridge`有关系吗？

**MARK**：找到进行调试的办法

### 3. flushCode做了什么？

reference `https://docs.libreoffice.org/bridges/html/classbridges_1_1cpp__uno_1_1shared_1_1VtableFactory.html`
code `https://docs.libreoffice.org/bridges/html/vtablefactory_8hxx_source.html`

```c++
// This function is not defined in the generic part, but instead has to be
// defined individually for each CPP--UNO bridge:
static void flushCode(
    unsigned char const * begin, unsigned char const * end);
// Flush all the generated code snippets of a vtable, on platforms that require it.
//Parameters
//    begin  points to the start of the code snippet area
//    end    points behind the end of the code snippet area
```

什么是 generated code snippet of a vtable ? **MARK**
注意到 loongarch64 cpp2uno.cxx #367 的代码

```c++
std::size_t const codeSnippetSize = 0x24;
```
