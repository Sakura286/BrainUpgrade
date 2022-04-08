#include<stdio.h>
#include<stdarg.h>

int sum(int argc, ...) {
    va_list argv;
    int total = 0;
    va_start(argv, argc);
    for (int i = 0; i < argc; i++)
        total += va_arg(argv, int);
    va_end(argv);
    return total;
}

int main() {
    setbuf(stdin, 0);
    printf("%d\n", sum(3, 2, 55, 6));
    printf("%d\n", sum(4, 22, 55, 23, 14));
    return 0;
}
