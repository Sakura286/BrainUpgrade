#include<stdio.h>
#include<stdlib.h>

int main() {
    setbuf(stdout, 0);
    FILE *fp;
    char ch, filename[10];
    printf("请输入所需文件名：");
    scanf("%s", filename);
    getchar();
    if ((fp = fopen(filename, "w")) == NULL) {
        printf("无法开启文件");
        exit(0);
    }
    printf("请输入一个准备存储到文件中的字符串（以#结束）:");
    ch = getchar();
    while (ch != '#') {
        fputc(ch, fp);
        putchar(ch);
        ch = getchar();
    }
    fclose(fp);
    putchar(10);
    return 0;
}