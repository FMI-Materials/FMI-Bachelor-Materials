#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

void* reverse(void *v){
    int len = 0;
    while(((char*)v)[++len]!='\0');
    char *rev = malloc(sizeof(char) * len);
    for(int i=0;i<len;++i)
        rev[i] = ((char*)v)[len-i-1];
    return rev;
}

int main(int argc, char **argv){
    pthread_t thr;
    void *result;
    if (pthread_create(&thr, NULL, reverse, argv[1])) {
        perror(NULL);
        return errno ;
    }
    if(pthread_join(thr,& result)){
        perror(NULL);
        return errno;
    }
    printf("%s\n", result);
    return 0;
}
