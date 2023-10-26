#include <iostream>
#include <string>
#include <fstream>

#include "btree.h"

using namespace std;

ifstream fin("abce.in");
ofstream fout("abce.out");

void execute(BTree *b, int op, int x, int y = 0){
    if(op==1)
        b->insert(x);
    if(op==2)
        b->remove(x);
    if(op==3)
        fout<<(int)b->contains(x)<<'\n';
    if(op==4)
        fout<<b->search(x, true)<<'\n';
    if(op==5)
        fout<<b->search(x, false)<<'\n';
    if(op==6)
        b->print(fout, x, y);
}

int main() {

    int n, op, x, y;
    BTree b(3);

    fin>>n;
    while(n--){
        fin>>op>>x;
        if(op==6) fin>>y;
        execute(&b, op, x, y);
    }

    return 0;
}