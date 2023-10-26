#include <iostream>
#include <vector>

using namespace std;
int n;
vector <int> muchii[1001], ctc, s, p;
int nrc;
void dfs1(int x){
    s[x] = 1;
    for(int i = 0;i < muchii[x].size(); ++i)
        if(s[i] == 0 && muchii[x][i] == 1)
            dfs1(i);
}
void dfs2(int x){
    p[x] = 1;
    for(int i = 0;i < muchii[x].size(); ++i)
        if(p[i] == 0 && muchii[i][x] == 1)
            dfs2(i);
}
int main() {
    int m;
    cin >> n >> m;
    for(int i = 0; i <= n; ++i){
        ctc.push_back(0);
        s.push_back(0);
        p.push_back(0);
    }
    for(int i = 0; i <= n; ++i)
        for(int j = 0; j <=n; ++j)
            muchii[i].push_back(0);
    for(int i = 0;i < m; ++i){
        int x, y;
        cin >> x >> y;
        muchii[x][y] = 1;
    }

    for(int i = 1;i <= n; ++i)
        if(ctc[i] == 0)
        {
            for(int j = 1; j <=n; ++j)
                s[j] = p[j] = 0;
            nrc ++;
            dfs1(i);
            dfs2(i);
            for(int j = 1; j <= n ; ++j)
                if(s[j] == 1 && p[j] == 1)
                    ctc[j] = nrc;
        }
    cout << nrc << "\n";

    for(int i =1 ; i <= nrc ;++i)
    {
        for(int j =1 ; j <= n ; ++j)
            if(ctc[j] == i)
                cout << j << " ";
        cout << endl;
    }

    return 0;
}
