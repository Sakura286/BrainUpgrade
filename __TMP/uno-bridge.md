
# Memo in UNO

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
