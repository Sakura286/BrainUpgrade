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



[1]:<https://www.zhihu.com/question/28191923>
