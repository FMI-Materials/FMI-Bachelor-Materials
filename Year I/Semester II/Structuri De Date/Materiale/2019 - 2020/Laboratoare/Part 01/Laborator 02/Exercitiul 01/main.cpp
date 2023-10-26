#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    vector<vector<int>> sol;
    int n,x,k = -1;
    vector<int> v;
    cin>>n;
    for(int i = 1; i <= n; i++){
        cin>>x;
        v.push_back(x);
    }
    for(int i:v){
        if(k == -1){
            vector<int> aux;
            aux.push_back(i);
            sol.push_back(aux);
            k = 0;
        }
        else{
            int ok = 1;
            for(int z = 0; z <= k; z++){
                if(sol[z].back() < i){
                    sol[z].push_back(i);
                    ok = 0;
                    break;
                }
            }
            if(ok){
                k++;
                vector<int> aux;
                aux.push_back(i);
                sol.push_back(aux);
            }

        }
    }
    for(vector<int> i:sol){
        for(int j:i){
            cout<<j<<" ";
        }
        cout<<endl;
    }
    return 0;
}
