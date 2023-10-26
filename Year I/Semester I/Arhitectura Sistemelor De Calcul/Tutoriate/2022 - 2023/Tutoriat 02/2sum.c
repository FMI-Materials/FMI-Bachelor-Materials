/* Se citesc de la tastatura doua numere, n si x.
 * Se citeste un array de n numere. 
 * Afisati indicii a doua numere din array care au suma egala cu x.
 *
 * Am rezolvat problema in O(n^2), optim se rezolva in O(n) cu un hashmap, insa am preferat aceasta abordare pentru faptul
 * ca este infinat mai simpla in assembly. Plus ca hashmap-urile nu fac parte din materia de laborator.
 *
 * Problema originala (solutia este sub forma unui subprogram):
 * https://leetcode.com/problems/two-sum/
 *
 * Cineva care si-a postat rezolvarea in assembly pe leetcode - va recomand sa va uitati desi rezolvarea este pe 64 biti:
 * https://youtu.be/lALPErFlfNQ
 */

#include <stdio.h>

int n, x;
int v[100];
int main(){
   scanf("%d %d", &n, &x);

   for(int i = 0; i < n; ++i)
        scanf("%d", &v[i]);

   for(int i = 0; i < n; ++i)
       for(int j = i+1; j < n; ++j)
           if(v[i] + v[j] == x){
                printf("%d %d\n", i, j); return 0;}

   return 0;
}
