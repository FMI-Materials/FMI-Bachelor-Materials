#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("rmq.in");
ofstream fout("rmq.out");

int main()
{
    int n,m;
    fin>>n>>m;

    int log2[n+1];
    log2[1] = 0;
    for(int i = 2; i <=n; i++){
        log2[i] = log2[i/2]+1;
    }

    int minima[18][n+1];
    for(int i = 1; i <= n; i++){
        fin>>minima[0][i];
    }

    ///RMQ
    for(int j = 1; (1<<j) <= n; j++){
        for(int i = 1; i-1+(1<<j) <= n; i++){
            minima[j][i] = min(minima[j-1][i], minima[j-1][i+(1<<(j-1))]);
        }

    }
    ///Rezolvarea query-urilor - O(1)
    for(int i = 1; i <= m; i++){
        int x,y;
        fin>>x>>y;
        int lungime = y-x+1;
        int aux = log2[lungime];
        ///cout<<x<<" "<<y<<" "<<aux<<" "<<min(minima[aux][x], minima[aux][y-(1<<aux)+1])<<endl;
        fout<<min(minima[aux][x], minima[aux][y-(1<<aux)+1])<<endl;
    }

    fin.close();
    fout.close();
    return 0;
}
