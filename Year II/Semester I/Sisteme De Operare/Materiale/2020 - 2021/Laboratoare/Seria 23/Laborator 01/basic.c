#include <stdio.h>
#include <stdlib.h>

/// int add(int &a, int &b) -- illegal in C
/// new, delete -- malloc, free

int main()
{
    int i=0;
    for(i=0;i<10;i++){
        if(i%2==0){
            printf("%d\n", i);
        }
    }
    printf("%d\n", i);
    i=0;
    ///
    int * my_int_array = NULL;
    int * my_other_array = NULL;
    my_int_array = malloc(10 * sizeof(*my_int_array));
    my_other_array = calloc(10, sizeof(*my_other_array));
    if(my_int_array == NULL)
        goto err;
    printf("%lu", sizeof(my_int_array));
    for(i=0;i<10;i++)
        printf("%d\n", *(my_int_array+i));
err:
    free(my_int_array);
    return 0;
}
