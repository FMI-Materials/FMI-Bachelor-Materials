#include <stdio.h>

int main()
{
    int admin = 0;
    char buffer[10];
    gets(buffer);
    if (admin) {
        printf ("You are admin.\n");
    }
    else {
        printf ("You are not admin");
    }

    return 0;
}

/**
 * $ gcc -g -m32 -o ex1 ex1.c -fno-stack-protector
 * $ ./ex1
 * > 12312312312345
 * > You are admin.
 */