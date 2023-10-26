#include <bits/stdc++.h>
using namespace std;
ofstream out ("test5.in");
/*
 0 - insereaza
 1 - sterge
 2 - min
 3 - max
 4 - succesor
 5 - predecesor
 6 - k_element
 7 - cardinal
 8 - este_in
 */
int main() {

    srand(time(NULL));
    for (int i = 1; i <= 100000; i++) {
        out << 0 << ' ' <<rand()%(214748364*2) - 214723<< '\n';
    }
    for (int i = 1; i <=5000; i++) {
        int x=rand()%8 + 1;out<<x;
        if(x==2||x==3||x==7)// daca interogam min, max sau cardinal, nu avem nevoie de 2 numere de input
            out<<"\n";
        else //altfel avem nevoie de 2 nr pt input
            out<<" "<<rand()%(214748364*2) - 214723<<"\n";
    }
    return 0;
}
