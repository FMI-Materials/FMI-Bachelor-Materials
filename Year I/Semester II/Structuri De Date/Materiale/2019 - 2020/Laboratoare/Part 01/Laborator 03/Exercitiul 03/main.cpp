#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;
unordered_map<int, int> harta;
long long v[2000];
int main()
{
    ifstream fin("progr.in");
    ofstream fout("progr.out");
    int nr_q, n, i;
    fin>>nr_q;
    while(nr_q-- > 0){
        harta.clear();
        fin>>n;
        int counter = 0;
        for(i = 0; i < n; i++)
            fin>>v[i];
        for(i = 0; i < n-1; i++){
            for(int j = i+1; j < n; j++){
                int x = v[i], y = v[j];
                if(x<y) swap(x,y);
                if(harta.find(y-x) == harta.end()){
                    harta[y-x] = 1;
                    counter ++;
                }
            }
        }
        fout<<counter<<endl;
    }
    fin.close();
    fout.close();
    return 0;
}
