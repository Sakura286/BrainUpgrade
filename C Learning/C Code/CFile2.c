#include<stdio.h>
#include<stdlib.h>

#define SIZE 2

typedef struct {
    char name[6];
    int number;
    char hobby[10];
} Student;

int save(Student *stu) {
    FILE *fp;
    if ((fp = fopen("student", "wb")) == 0) {
        printf("Shit!");
        exit(0);
    }
    for (int i = 0; i < SIZE; i++) {
        if ((fwrite(&stu[i], sizeof(Student), 1, fp) != 1)) {
            printf("Shit Again!");
        }
    }
    fclose(fp);
    return 0;
}

int main() {
    setbuf(stdout, 0);
    Student stu[SIZE];
    for (int i = 0; i < SIZE; i++) {
        scanf("%s %d %s", stu[i].name, &stu[i].number, stu[i].hobby);
    }
    save(stu);
    return 0;
}