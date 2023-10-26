#include <iostream>
#include <vector>
#include <queue>
/**
 Se dă o matrice n*m (n,m <= 1000), cu p<= 100 puncte marcate cu 1 (restul valorilor din matrice vor fi 0).
 Distanța dintre 2 puncte ale matricei se măsoară în locații străbătute mergând pe orizontală
 și pe verticală între cele 2 puncte (distanța Manhattan). Se dă o mulțime Mde qpuncte din matrice
 (q<= 1000000). Să se calculeze cât mai eficient pentru fiecare dintre cele qpuncte date,
 care este cea mai apropiată locație marcată cu 1 din matrice. (Licență iunie 2015)

 */
using namespace std;
vector<int> matrice[1001];
int n,m;
bool inMatrice(int i, int j){
    return (1<= i && i <=n) && (1<=j && j <=m);
}
void parcurgere(int p, int q){
    vector<int> b[1001];
    for(int i = 0;i <= n; ++i)
        for(int j = 0;j <= m; ++j)
            b[i].push_back(0);

    queue<pair<int,int>> coada;
    coada.push(make_pair(p,q));
    b[p][q] = 1;
    if(matrice[p][q] == 1){
        cout << 0 << "[" << p << ", " << q << "]";
    }
    else{
        int dx[5] = {-1,0,1,0};
        int dy[5] = {0,1,0,-1};
        int mi = 999999999;
        int pma1 = -1, pma2 = -1;
        while(!coada.empty()){
            int x,y;
            x = coada.front().first;
            y = coada.front().second;
            coada.pop();
            //cout << x << " " << y << endl;
            for(int i = 0;i < 4; ++i){
                int xn = x, yn = y;
                xn += dx[i];
                yn += dy[i];
                //cout << xn << " " << yn << endl;
                if(inMatrice(xn,yn) && (b[xn][yn]==0 || b[xn][yn] > b[x][y]+1)){
                    b[xn][yn] = b[x][y] + 1;
                    if(matrice[xn][yn] == 1 && b[xn][yn] < mi){
                        mi = b[xn][yn];
                        pma1 = xn;
                        pma2 = yn;
                    }
                coada.push(make_pair(xn,yn));
                }
            }
        }
        cout << mi - 1 << " [" << pma1 << ", " << pma2 << "]";
    }
    cout << '\n';
}
void citire(){
    cin >> n >> m;
    for(int i = 0; i <= n; ++i){
        for(int j = 0;j <= m;++j){
            matrice[i].push_back(0);
        }
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1;j <= m;++j){
            int x;
            cin >> x;
            matrice[i][j] = x;
        }
    }
}
int main() {
    citire();
    int q;
    cin >> q;
    for(int i = 0;i < q; ++i){
        int x, y;
        cin >> x >> y;
        parcurgere(x,y);
    }
    return 0;
}
