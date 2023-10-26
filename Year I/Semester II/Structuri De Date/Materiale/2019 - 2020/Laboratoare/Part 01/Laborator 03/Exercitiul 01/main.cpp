#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;
unordered_map<long, long> val;
long long a,b,c,d,e,n,m, x, y, k=0;
int main()
{
    ifstream fin("muzica.in");
    ofstream fout("muzica.out");
    fin>>n>>m>>a>>b>>c>>d>>e;
    for(int i = 1; i <= n; i++){
        fin>>x;
        val[x] = 1;
    }
    x = a; y = b;
    while(m--){
        ///cout<<m<<" "<<x<<" "<<k<<endl;
        if(val[x] == 1){
            k++;
            val[x] = 0;
        }
        x = (c*y + d*x)%e;
        swap(x,y);
    }
    fout<<k;
    fin.close();
    fout.close();
    return 0;
}
