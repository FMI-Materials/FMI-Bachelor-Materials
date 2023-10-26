#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;
int main()
{
    unordered_map <int,int> date;
    ifstream fin("pariuri.in");
    ofstream fout("pariuri.out");
    int n,m,i,j;
    fin>>n;
    for(int i = 1; i <= n; i++){
        fin>>m;
        int x,y;
        for(int j = 1; j <= m; j++){
            fin>>x>>y;
            if(date.find(x) == date.end()){
                date[x] = y;
            }
            else{
                date[x] += y;
            }
        }

    }
    fout<<date.size()<<endl;
    for(pair<int,int> i:date){
        fout<<i.first<<" "<<i.second<<" ";
    }
    fin.close();
    fout.close();
    return 0;
}
