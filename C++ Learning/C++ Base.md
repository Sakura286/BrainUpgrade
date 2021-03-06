# C++ 基础

[TOC]

## 重要的例子（多练）

### 函数指针练习

1. 申请一个函数指针
2. 将函数指针作为参数输入另一个函数
3. 使用函数指针调用该函数

### 动态内存练习

1. 用`new (nothrow)`申请一块内存，判断是否为空
2. 向该内存写数据：尝试直接操作指针
3. 读该内存数据：尝试使用[]操作符
4. 删除该内存

### 结构体练习

1. 申请一个结构体数组
2. 将结构体嵌套使用
3. 使用指针访问结构体（两种办法）

## 面向过程基本语法

### 初始化数据

**C风格初始化**(C-like initialization)，继承自 C 语言

**构造函数初始化**(constructor initialization)， C++ 引入

**统一/通用初始化**(uniform/universal initialization)， C++ 11 引入

```c++
int a = 1; // c-like initialization
int a (1); // constructor initialization
int a {1}; // universal initialization
```

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

### 按引用传参与传递复合类型的优化

```c++
void mult1(int a)  { a *= 2; }
void mult2(int& a) { a *= 2; }
int main()
{
    int x = 3;
    mult1(x); cout << x << endl; // 3
    mult2(x); cout << x << endl; // 6
}
```

默认情况下**按值传参**,调用函数的时候将传入参数的值复制一份，函数运算里使用复制后的副本，所以`mult1`并未改变x的值
如果想不做复制直接传进去，则可以**按引用传参**，就像`mult2`

按引用传参因为少了复制参数的值这一过程，所以额外开销会少一些，但如果参数是基本数据类型的话，这个开销会非常小。但是当传递的参数为复合类型的时候，复制一份的开销可能会非常大。

```c++
string concact(string a, string b) { return a + b; }
```

例如上面的函数，每次传入参数都需要把两个字符串复制一遍。为了避免这种开销，可以考虑按引用传参，像这样：

```c++
string concact(string& a, string& b) { return a + b; }
```

但是当按引用传参时，我们一般会认为这是要将做出的修改回传给调用者（这也正是按引用传参本来的目的），为了避免这些问题，可以用`const`修饰传入参数

```c++
string concact(const string& a, const string& b) { return a + b; }
```

这样，既可以享受按引用传递带来的减少开销的好处，又可以避免按引用传递后原值会遭到修改的可能

### 参数的默认值

一个原本有三个参数的函数可以传入0~3个参数，如果这样设置：

```c++
int sum(int a, int b = 2, int c = 3) { return a + b + c; }
cout << sum(1, 3, 5) << endl;   // 9
cout << sum(1, 3) << endl;      // 7
cout << sum(1) << endl;         // 6
cout << sum() << endl;          // 编译不通过，因为第一个参数未指定
```

### 函数原型

变量使用前必须要声明，同样的函数使用前必须要声明，不过在调用前只需要一个函数原型即可，函数的具体实现可以放在调用之后。这样做可以避免main函数过于靠后

```c++
int sum(int, int); // 可以不写变量名
int sum(int a, int b); //变量名与函数声明时的变量名没必要一样，看成助记符即可；不过Clang-tidy会有警告
int sum(int x, int y){ return x + y; } // 函数体
```

### 模板

```c++
template <class T, class U>
bool isEqual(T a, U b) { return a == b; }
int main(){ cout << isEqual<int, double>(10, 10.0) << endl; }
```

`class`可以和`typename`互换，调用模板函数的时候在尖括号里指定类型，也可以不指定

### 命名空间

在花括号之内的变量是局部变量，在所有花括号之外的是全局变量

为了避免使用同名变量时的歧义，可以把不同的变量定义在不同的命名空间中

```c++
namespace myNamespace1 { int a = 2; }
namespace myNamespace2 { int a = 3; }
cout << myNamespace2::a << endl; // a = 3
```

命名空间不一定必须要连续定义，例如：

```c++
namespace foo { int a; }
namespace bar { int b; }
namespace foo { int c; }
```

在不引起歧义的情况下，可以使用`using`关键字申明使用的命名空间，以省略前缀

```c++
using namespace myNamespace1;
cout << a << endl; // a = 2
```

原本在局部申明的变量会比`using namespace`拥有更高的优先级

```c++
namespace foo { int x = 5; }
int main()
{
    int x = 3;
    using foo::x; // 注意这是另外的写法
    cout << x << endl; // x = 3
}
```

`using`后起效的范围不会超出`using`所在的代码块{}

可以给命名空间起别名

```c++
namespace new_name = current_name;
```

### 变量的初始化

全局变量及命名空间内的变量使用静态存储方式，未显性初始化的变量会**自动初始化为0**
局部变量使用动态存储方式，未显性初始化的变量值是**未定的**

## 复合数据类型

### 数组

数组的大小必须是常量，因为数组的体积在编译的时候就定死了

可以初始化时不指定数组的大小，这样编译器会自动设置

```c++
int foo[] { 1, 3, 5, 7 }; // foo长度为4
```

越界访问数组元素在编译阶段不会报错

### 库数组

普通数组在传参时只会传递指针，而使用库数组则会直接复制数组

```c++
#include <array>
int main()
{
    array<int, 3> foo {1, 3, 5};
    for (auto elem : foo)
    {
        cout << elem << endl;
    }
}
```

### 字符串

以null结尾的字符序列可以隐式转换为字符串，字符串可以通过调用`c_str()`方法来生成C的字符数组

```c++
char foo[] = "some text";
string bar = foo;
cout << bar << endl;         // printed as a library string
cout << bar.c_str() << endl; // printed as a c-string
```

### 指针 & const

```c++
int x;
      int *       p1 = &x;  // non-const pointer to non-const int
const int *       p2 = &x;  // non-const pointer to const int
      int * const p3 = &x;  // const pointer to non-const int
const int * const p4 = &x;  // const pointer to const int 
```

```c++
const int * p2a = &x;  //      non-const pointer to const int
int const * p2b = &x;  // also non-const pointer to const int
```

倒是不麻烦：

1. `const int *`与`int const *`意思都是**指向的数**不能被修改
2. `*`后面接`const`表明**指针本身**不能修改

**楷**：const 总是修饰它左边的类型，如果左边为空，则修饰右边。

### 空指针

可以用 `0` 或者 `nullptr` 指定，在部分库里，还可以用`NULL`指定

### 函数指针 & 指针函数

指针函数指的是函数的返回值是指针

函数指针指的是一个指向函数入口的指针

函数指针示例，请注意函数指针的申请与使用

```c++
int add(int a, int b){
    return a+b;
}
int sub(int a, int b){
    return a-b;
}
int operation(int a, int b, int (*function)(int, int)){
    return function(a,b);
}
int main(){
    int (*function)(int, int) = sub;
    cout << operation(3, 2, function) << endl;  // 1
    cout << operation(3, 2, add) << endl;       // 5
}
```

### 动态内存 - new

数组的长度是编译时确定的，但是如果我们采取如下的方式，可以运行时在堆内存里动态申请一个“数组”

```c++
int * foo = new int[5];
```

内存数量有限，可能会分配失败。堆内存分配失败有两种解决措施：

一、直接抛出`bad_alloc`异常

二、使用`nothrow`，若分配失败会返回一个空指针，该机制在`<new>`头文件里定义

```c++
int * foo = new (nothrow) int[5];
```

### 动态内存 - delete

可以用如下方式删除为指针分配的内存，第一种方式只删除了指针指向的值，第二种方式删除new+[]分配的一片空间

```c++
delete ptr;
delete[] ptr;
```

## 面向对象基本语法

### 类

访问修饰符(access psecifier):

- `public`所有成员可访问
- `private`只能本类的成员访问
- `protected`只能本类及子类(derived class)的成员可访问

函数在类里与类外定义的区别是，在类里定义会成为内联(inline)成员，对编译器优化可能会有影响，注意这两种定义方式：

```c++
class Human {
    public:
        void eat() { cout << "I can eat." << endl; }
        void read(string);
};
void Human::read(string str) { cout << "I am reading " << str << endl; }
```

### 构造函数

构造函数是没有任何返回值的，甚至没有`void`

构造函数不能显性调用，只能在声明对象的时候调用

```c++
class Human{
    string name;
    public:
        Human();
        Human(string);
};
Human::Human(){ name = "Mr. Dao"; }
Human::Human(string str){ name = str; }
int main(){
    Human p1("Bob");
    Human p2;
}
```

注意，在调用无参的构造函数时，不能使用`Human p3();`这样带括号的写法

### 构造函数的多种初始化方法

对于单参数的构造函数来说：

```c++
Human p1 ("Bob");
Human p2 = "Carlot"; // only for one parameter
Human p3 {"Dick"};
Human p4 = {"Einfersuchet"};
```

对于无参构造函数来说：

```c++
Human p1;
Human p2{};
```

### Member Initializer List

参考：[Member Initialization List - 简书](https://www.jianshu.com/p/e48d7d498bf9)

四种情况下需要使用Member Initializer List

1. 当初始化一个refernce member时
2. 当初始化一个const member时
3. 当调用一个base class的constructor，而他拥有一组参数时
4. 当调用一个member class 的constructor,而他有一组参数时

例如对于类：

```c++
class Rectangle {
    int width, height;
    public:
    Rectangle(int, int);
    int area() { return width * height; }
};
```

通常情况下初始化在构造函数内进行

```c++
Rectangle::Rectangle(int x, int y) { width = x; height = y; }
```

但是可以使用如下的member initialization方式

```c++
Rectangle::Rectangle(int x, int y) : width(x) { height = y; }
Rectangle::Rectangle(int x, int y) : width(x), height(y) { }
Rectangle::Rectangle(int x, int y) : width{x}, width{y} { } // uniform initialization
```

### 使用类指针

```c++
Rectangle obj(3, 4);
Rectangle * foo, * bar, *baz;
foo = &obj;
bar = new Rectangle(5,6);
baz = new Rectangle[2] { {2,5}, {3,6} };
```

### 运算符重载

[【C++】运算符重载关于const的分析（超详细）_萌宅鹿同学的博客-CSDN博客_运算符重载const](https://luzhenyu.blog.csdn.net/article/details/104465307)

### 静态成员

同一个类的多个成员共享同一个静态变量（函数）

```c++
class Human{
public:
    static int cnt;
    Human(){ cnt++; }
};
int Human::cnt = 0;
int main(){
    Human Bob; Human Kate;
    cout << Kate.cnt << endl;
    cout << Dummy::cnt << endl;
}
```

注意上面的例子

1. 静态成员需要在类的外部初始化
2. 可以使用对象访问静态成员，也可以使用`类名::静态成员`的方式来访问

### 常量成员函数

使用方法：

```c++
int get() const { return x; }
```

**问题**：`const int& get() {return x;}`这里的`const&`是什么？

使用const修饰的成员函数理论上是只读的，所以它不能修改非静态的变量，也不能调用非const的程序

```c++
class Example {
    int x;
    public:
    Example(int val) : x(val) { }
    const int& get() const { return x; }
    int& get { return x; };
};

int main(){
    Example foo(10);
    const Example bar(20);
    foo.get() = 15;
    // bar.get() = 25; // not valid
    cout << foo.get() << endl;
    cout << bar.get() << endl;
}
```

```c++
class Example {
    int x;
public:
    Example() : x(5) { };
    explicit Example(int val) : x(val) { }
    int& get() { return x; };
    [[nodiscard]] const int& get() const { return x; }
};
```

**疑问**：IDE自动建议的`explicit`和`[[nodiscard]]`关键字意味着什么？没看明白。

### 模板特化(template specialization)

使用模板时可以给不同的传入类型构建不同的实现

```c++
template <class T>
class Add {
    T element;
    public:
    Add(T arg) : element(arg) { }
    T increase() { return ++element; }
};
template <>         // 
class Add <char> {  // 在这里指定类型
    char element;   // 里面也不会指代别的类型
    public:
    Add(char arg) : element(arg) { }
    char uppercase() {
        if ( (element >= 'a') && (element <= 'z'))
            element += 'A' - 'a';
        return element;
    }
};                  // 一定有分号
int main(){
    Add<int> myint(7);
    Add<char> mychar('j');              // 注意申请方式
    cout << myint.increase() << endl;
    cout << mychar.uppercase() << endl; // 注意可以调用各自的方法
}
```

### 默认构造函数

如果显式定义了带参的构造函数，那么就不能再隐式地调用无参的构造函数

### 析构函数

若对象通过自动分配内存（new）分配了资源，那么在对象的生命周期结束时需要使用析构函数来销毁该数据

```c++
class Human {
    string* ptr;
    public:
    Human (const string& str) : ptr(new string(str)) { }
    ~Human() { delete ptr; }
}
```

### 拷贝构造函数

### 拷贝赋值

### 移动构造函数

### 移动赋值

### 隐式成员

### 友元函数与友元方法

```c++
class Human {
    string name;
    public:
    friend Human duplicate(const Human&); // Attention
    void transform(Animal a){
        name = a.animalName;
    }
};
Human duplicate(const Human& man){
    Human toolman;
    toolman.name = man.name;
    return toolman;
}
class Amimal {
    friend class Human; // Attention
    private:
    string animalName;
};
```

注意友元函数及友元类的使用方法。

虽然看起来很像，但是友元函数duplicate并不是Human的成员函数

### 再谈访问修饰符

在类里的访问修饰符(access psecifier):

- `public`所有成员可访问
- `private`只能本类的成员访问
- `protected`只能本类及子类(derived class)的成员可访问

继承语法

```c++
class Daughter : public Mother;
```

这里的`public`，指的是所有从Mother继承下来的成员（`public`和`protected`），都保持原来的性质不变

使用`protected`，则将继承下来的全部设为`protected`属性

使用`private`，全部设为`private`

一般用`public`

### 调用基类的构造函数

```c++
class Mother{
    public:
    Mother() { cout << "Mother" << endl; }
    Mother(const string& offspring) { cout << "Mother with " << offspring << endl; }
};
class Son : public Mother{
    public:
    Son() { cout << "Son" << endl; } // 其实这里隐式地调用了基类的无参构造函数
};
class Daughter : public Mother{
    public:
    Daughter() : Mother("Daughter") { cout << "Daughter" << endl; }  // 注意调用方式
};
int main(){
    Son son;
    cout << endl;
    Daughter daughter;
}
```

以下是输出：

```plain
Mother
Son

Mother with Daughter
Daughter
```

### 多态

若：

1. 子类与基类都实现了同名的函数
2. 有**一个基类指针指向了子类对象**
3. 使用该指针调用该同名函数

那么会调用基类的函数

如果基类中该函数使用virtual修饰

那么会调用子类的函数

**问题**：为什么IDE此时建议对子类的该函数使用override修饰？

**MARK**：对比之前看过的多态汇编实现原理——为啥不自己看一下汇编？

## 其他

### 类型转换

### 异常

### 预处理器指令
