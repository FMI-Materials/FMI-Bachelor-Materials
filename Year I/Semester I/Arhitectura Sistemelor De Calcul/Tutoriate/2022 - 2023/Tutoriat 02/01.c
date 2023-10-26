#include <stdio.h>

int v[100], maxx, cnt, n;

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%d", &v[i]);
        if(v[i] > maxx)
        {
            maxx = v[i];
            cnt = 0;
        }
        if(maxx == v[i])   
             ++cnt;
    }
    printf("%d %d\n", maxx, cnt);
    return 0;
}
