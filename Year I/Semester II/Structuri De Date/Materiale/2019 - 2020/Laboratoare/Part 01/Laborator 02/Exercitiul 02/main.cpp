#include <iostream>
#include <vector>
#include <stack>

using namespace std;
void Sort(vector<pair<int,int>>& v, int n){
    int ok = 1;
    while(ok){
        ok = 0;
        for(int i = 0; i < n-1; i++){
            if(v[i].first>v[i+1].first){
                ok = 1;
                swap(v[i],v[i+1]);
            }
        }
    }
}
int main()
{
    int n;
    pair<int,int> coord;
    vector<pair<int,int>> segments;
    cin>>n;
    for(int i = 1; i <= n; i++){
        cin>>coord.first>>coord.second;
        if(coord.first > coord.second)
            swap(coord.first,coord.second);
        segments.push_back(coord);
    }

    Sort(segments,n);
    stack<int> cuie;
    cuie.push(segments[0].second);
    for(pair<int,int>i:segments){
        if(i.first>cuie.top()){
            cuie.push(i.second);
        }
        else{
            int cui = cuie.top();
            cuie.pop();
            cui = min(cui,i.second);
            cuie.push(cui);
        }
    }
    cout<<cuie.size()<<endl;
    while(!cuie.empty()){
        cout<<cuie.top()<<" ";
        cuie.pop();
    }
    return 0;
}
