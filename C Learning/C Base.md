# C语言基础

## 8 指针

### 8.4 通过指针引用字符串

三种字符串申明方式

```c
char str1[] = "abc";                //方法1
char str2[] = {'a','b','c','\0'};   //方法2
char * str3 = "abc";                //方法3
```

C程序的数据分为四个部分

1. 程序代码和数据，这里面有相当的部分是**只读**的，地址最低
2. 堆，`malloc`和`free`使用的场所，在1之上
3. 栈，放在顶端，存放变量及*正在运行*的函数，会自动增长消亡
4. 共享库，大约在内存的中间位置

方法1和方法2申请的字符数组在栈里，而方法3申请的字符串在**程序代码和数据**里，在编译时已经提前作为程序数据读入；所以，使用方法3申请的字符串**不能修改其内部的值，也不能通过`scanf`的方法修改输入该字符指针的值；

参见[指针修改字符串字面量？ \- 知乎][1]

## 9 结构体

### 9.1 定义和使用结构体变量

结构体类型 `struct xxx`不能省去`struct`

声明变量的时候就会申请内存单元

结构体本身是可以作为函数返回值的

### 9.5 共用体

共用体示例

```c
union TMP{
    int i;
    char ch;
    float f;
};

union TMP tmp1,tmp2;
tmp1.i = 54;
tmp2.ch = 'A';
printf("%c", tmp1.ch);
printf("%c", tmp2.float);
```

结果

```c
6
0.000000
```

例中共用体中的int char float使用同一起始地址，**取值与存值**都是按照**数据类型**来的

初始化样例

```c
union TMP tmp1 = {16};          //默认对第一个值赋值
union TMP tmp2 = {.ch = 'c'};   //指定一个值赋值
```

需要注意的是，不能对多余一个值同时赋值

C99允许同类型的共用体变量互相赋值

```c
tmp1 = tmp2;
```

### 9.6 枚举

枚举示例

```c
enum Weekday{sun, mon, tue, wed, thur, fri, sat};
enum Weekday wrokday, weekend;
workday = mon;  //可以用枚举成员赋值
weekend = sun;
workday = 1;    //也可以用数字赋值，只要不超过界限
printf("%d",weekend);
```

结果

```c
0   //枚举类型值从0开始
```

所以可以把枚举看成一个特定的数组

## 10 文件

要想使用`exit(0)`需要`#include<stdlib.h>`

### `fopen()`

```c
FILE* fopen(char *filename,char *mode);
```

如果访问文件出错，例如只读模式打开一个不存在的文件，则返回NULL指针

注意，w模式会破坏文件原有的内容，编辑已有的应该是a模式

### `fgetc()`与`fputc()`

返回的EOF的值是-1

### `fgets()`与`fputs()`

```c
char* fgets(char* s, int , FILE* fp);
```

从fp处开始读取**count-1**大小的字符串，后加"\\0"后赋值到s指向的内存空间，该函数返回的也是该内存空间的地址，如果出错会**返回NULL，s不做处理**

如果count\<0那么啥也不做

如果提前遇到换行符或者文件尾，则会提前返回

```c
int fputs(char* s,FILE* fp);
```

输出成功，返回非负值（Win64测试下是0），否则返回EOF

### `rewind()`

```c
void rewind(FILE* fp);
```

用于重置fp指向文件头

- 当以 r 或 w 模式打开文件时，使用该函数会使fp回到文件头，值得注意的是，如果是 w 模式，回到文件头后如果继续写，会类似于键盘上的insert模式，把前面的数据覆盖掉
- 当以 a 模式打开文件时，虽然会指向文件头，但继续添加的字符依然会接到文件的末尾，然后

### `fseek()`

```c
int fseek(FILE *fp, long offset, int origin);
```

origin有三个常量

- `SEEK_SET`
- `SEEK_CUR`
- `SEEK_END`

### `ftell()`

```c
long ftell(FILE* fp);
```

返回fp相对于文件头的偏移量，以字节表示

## 内嵌汇编

可能会有错误，并不是特别理解

示例1：

```c
//本段代码测试的是看push %rsp做的究竟是什么
long long stack1;
long long stack2;
asm("movq %%rsp,%[before]\n\t"
    "push %%rsp\n\t"
    "pop %[end]"
    :[before] "=r" (stack1),
    [end] "=r" (stack2)
);
printf("%x\n",stack1);
printf("%x",stack2);
```

注意，asm里面的参数有四个，分别是

1. 汇编代码
2. 输出
3. 输入
4. 会被修改的寄存器

即`asm ( "statements" : output_regs : input_regs : clobbered_regs)`，每一部分之间都用冒号进行分隔，靠后的部分如果没有可以省去冒号

### 汇编代码

示例代码2：

```c
asm("movq %%rsp,%[before]\n\t"
    "push %%rsp\n\t"
    "pop %[end]")
```

该部分为**一整个字符串**，如果汇编有多行的话，用`\n\t`隔开，若想要较为美观的效果，可参照示例2

寄存器有三种表示方式

#### 直接指定方式

注意要多加一个%号，例如`%%rsp`

#### 数字占位符

例如`%0`，`%1`…，`%9`,最多为10个，指令中使用占位符表示的操作数，总被视为long型（4，个字节），但对其施加的操作根据指令可以是字或者字节，当把操作数当作字或者字节使用时，默认为低字或者低字节。对字节操作可以显式的指明是低字节还是次字节。方法是在%和序号之间插入一个字母，“b”代表低字节，“h”代表高字节，例如：%h1。

#### 指定名称作为占位符

数字占位符只有10个而且难以管理，可以自己命名占位符，格式如例：`%[shit]`

### 输出

每一个寄存器的格式如下：
`[shit] "=r" (num)`

其中，第一部分是自定义占位符，我们在上面的汇编里把这个寄存器称作`shit`
第二部分`"=r"`表示存放位置为寄存器，写作`"=m"`表示存放位置为内存
第三部分指代要把内容输出到哪个**变量**，此例中变量为`num`

### 输入

每一个寄存器的格式如下：
`[fuck] "r" (inum)`

第一部分是自定义占位符，我们在上面的汇编里把这个寄存器称作`fuck`
第二部分`"r"`表示为寄存器，写作`"m"`表示为内存，注意和输出相比这里**没有等号**
第三部分指代要把内容从哪个**变量**读取，此例中变量为`inum`

### 会被修改的寄存器

参考资料1：[GCC内嵌汇编 - An Amateur Programmer's Blogs](https://dirtysalt.github.io/html/gcc-asm.html)
参考资料2：[内嵌汇编- BraveY](https://bravey.github.io/2019-10-31-%E5%86%85%E5%B5%8C%E6%B1%87%E7%BC%96.html)
参考资料3：[C语言的内嵌汇编 - 知乎](https://zhuanlan.zhihu.com/p/348372132)
参考资料4：[CS:APP3e Web Aside ASM:EASM:Combining Assembly Code with C Programs](http://csapp.cs.cmu.edu/3e/waside/waside-embedded-asm.pdf)

## 其他

### 整数类型

包含在`<stdint.h>`内，例如128位int可用`__int128`表示，而64位整数最大值可用`INT64_MAX`表示

### 随机数（rand(),srand())

`rand()`函数包含在`<stdlib.h>`中，生成0\~RAND_MAX之间的整数，RANDMAX的值至少为32767

`rand()`函数每次生成的随机数都一致，是因为种子在每次启动计算机时都是随机的，所以需要`srand()`来进行重新播种，其用法如下：

```c
    void srand(unsigned int);
```

`srand()`只需要初始化**一次**，`rand()`的值便会不断变化

正确用法：

```c
    srand((unsigned)time(NULL));
    for(int i=0;i<10;i++){
        printf("%d ",rand());
    }
```

错误用法：

```c
    for(int i=0;i<10;i++){
        srand((unsigned)time(NULL));
        printf("%d ",rand());
    }
```

如果把`srand()`写在里面，会在每一次循环里都初始化，最后输出的序列结果反而是固定的

注意：上面的例子里使用了`<time.h>`，把系统时间当做了重新播种的种子。若使用其他的一个数字，生成的序列里元素之间是随机的，但是生成的序列是固定的，例如如果用`10`当种子在我这台电脑的此次开机中会一直生成`71 16899 3272 13694 13697 18296 6722 3012 11726 1899`这个序列

> 生成的随机数貌似不均匀，Mark一下等待之后解决 *(2022.03.17)*

### 标准输入输出

#### 输入带空格的字符串

用`scanf("%s",array)`的话遇到空格就停止接收后面的字符了，那怎么才能接收带空格的字符串呢？

1. 用`gets()` ，它可以接收带空格的字符串， 直到回车才结束输入

    ```c
    char buf[80]={0}; 
    gets(buf);   //可以读取空格， 回车结束输入
    ```

2. 使用`"%[^\n]"`也是可以接收输入一个带空格的字符串，直到回车结束接收

    ```c
    char buf[10] = {0};
    scanf("%[^\n]",buf); //可以读取空格，回车结束输入
    ```

注意：`scanf_s("%s",buf,10)`不能接收带空格的字符串输入，虽然它的指定长度是10， 但是遇到空格时即使没有满10个字符它也自动结束输入了。

[1]:<https://www.zhihu.com/question/28191923>

## 内存

### 三个函数

#### calloc

```c
void *calloc(size_t num, size_t size);
```

注意内存分配用的数字皆为无符号整数。分配num个size字节大小的空间，**初始化为0**，返回该片空间的地址。

#### malloc

```c
void *malloc(size_t num);
```

分配num字节的内存，并返回该部分内存的地址，不做初始化。

#### realloc

```c
void *realloc(void *address, size_t newsize);
```

address是要调整的内存区域的地址

- 是空指针：相当于malloc()，申请一块newsize的内存，不作初始化
- 不是空指针：会将该片内存调整到newsize大小
  - 如果newsize比原本的内存区域小：舍弃掉newsize之后的部分
  - 如果newsize并原本的内存区域大：原本部分内存中的数据将会保留，新申请的空间不作初始化
    - 如果newsize比该片堆内存小，则仅将原本的区域扩展，并返回原来的地址
    - 如果newsize比该片对内存大，则将内容复制到新的内存区域，free()掉先前区域
