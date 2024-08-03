#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

set<int> s;
int h[200000];
int ops,cs;
long nr, k = 0;
void add(int nr){
    h[k++] = nr;
    s.insert(nr);
}

void del(int poz){
    int x = h[poz];
    s.erase(x);
}
int main()
{
    ifstream fin("heapuri.in");
    ofstream fout("heapuri.out");
    fin>>ops;
    for(int i=1;i<=ops;i++){
        fin>>cs;
        switch(cs){
        case 1:{
            fin>>nr;
            add(nr);
            break;
        }
        case 2:{
            fin>>nr;
            del(nr-1);
            break;
        }
        case 3:{
            fout<<*s.begin()<<endl;
            break;
        }
        }
    }
    fin.close();
    fout.close();
    return 0;
}
