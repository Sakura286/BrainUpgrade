# C++ 基础

## 面向过程基本语法

### 初始化数据

**C风格初始化**(C-like initialization)，继承自 C 语言

**构造函数初始化**(constructor initialization)， C++ 引入

**统一初始化**(uniform initialization)， C++ 11 引入

### 类型自动推导

类型自动推导(type deduction)，有两个关键字`auto`和`decltype`

```c++
int foo = 0;
auto bar = foo; // int bar = foo;
decltype(foo) tars; // int tars;
```

### 逗号运算符

```c++
a = ( b = 3 , b + 2)
```

最后的结果为 b = 3 , a = 5，只有最靠右的会赋值到a

### 原始字符串

原始字符串(raw string)语法

```raw
std::string s1 = R"NOT_PRINT_FLAG(String content)NOT_PRINT_FLAG";
```

`NOT_PRINT_FLAG`需要前后一致，可以省略，最后只输出`String content`部分的内容

### 数字常量的表示

| 前缀 | 举例 | 含义                  |
| ---- | ---- | --------------------- |
| 无   | 14   | 十进制(decimal)       |
| 0    | 016  | 八进制(octal)         |
| 0x   | 0xE  | 十六进制(hexadecimal) |

| 后缀     | 含义         |
| -------- | ------------ |
| u 或 U   | 无符号       |
| l 或 L   | 长整型       |
| ll 或 LL | 超长整型     |
| f 或 F   | 单精度浮点型 |
| l 或 L   | 双精度浮点型 |

### endl 与换行符

参考：[菜鸟教程 - C++中 \n 与 endl 的区别是什么？](https://www.runoob.com/note/23593)

`endl`会刷新缓冲区，而换行符`\n`不会。

以下三个语句含义相同

```c++
std::cout << std::endl;
std::cout << '\n' << std::flush;
std::cout << '\n'; std::fflush(stdout);
```

**猜测**：有时候需要写入文件或屏幕，用endl可以保证避免残留
**据说**：endl可能会使程序的效率低下
**MARK**：什么是缓冲区？缓冲区是怎么运作的？

### 输入字符串

cin碰到空格就停下，所以得用其他的办法输入带空格的字符串

```c++
#include <string>
...
getline(cin, mystr);
cout << mystr << endl;
```

### 字符串作为流

```c++
#include <string>
#include <sstream>
...
int i;
getline(cin, mystr);
stringstream(mystr) >> price;
```

### 范围循环

```c++
string str {"Hello!"};
for (auto c : str)
{
    cout << c << endl;
}
```

## 函数

### 无参数的函数

往往这样声明

```c++
type FuncName(void){ statements }
```

显式地使用`void`，是C时代的遗留风格，不用也没关系

### 程序退出状态

| 值           | 描述                                |
| ------------ | ----------------------------------- |
| 0            | 成功退出                            |
| EXIT_SUCCESS | 成功退出（同上），定义在`<cstdlib>` |
| EXIT_FAILURE | 程序错误，定义在`<cstdlib>`         |

### 内联函数

在函数类型之前使用`inline`关键字，在编译时会直接把代码扩展到调用函数的位置，这样可以避免跳转的开销，适用于比较短的函数（我觉得可以说是适用于“叶子函数”吧）

不过现在的编译器优化（optimization）已经可以自动识别可以扩展为内联函数的函数了

### 参数的默认值

### 模板
