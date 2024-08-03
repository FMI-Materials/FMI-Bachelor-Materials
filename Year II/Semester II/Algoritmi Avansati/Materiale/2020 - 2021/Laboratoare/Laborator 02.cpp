#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_set>

using namespace std;

ifstream fin("data.in");

vector<int> nums;
int k;

int bfs(){
    int sum = 0;
    unordered_set<int> vals;
    vals.insert(0);
    for(auto &num: nums)
        for(auto &val: vals)
            if(val + num <= k){
                sum = max(sum, val + num);
                vals.insert(val + num);
            }
    return sum;
}

int knapsack_a(){
    int x;
    fin>>k;
    while(fin>>x){
        if(x<=k)
            nums.emplace_back(x);
    }
    return bfs();
}

int knapsack_b(){
    int x, sum = 0, pm = -1;
    fin>>k;
    while(fin>>x){
        if(sum+x==k)
            return k;
        if(sum+x<k){
            sum+=x;
            pm = max(pm, x);
        }else if(pm < x){
            sum -= pm;
            sum += x;
            pm += x;
        }
    }
    return sum;
}

int main() {
    //cout<<knapsack_a();
    cout<<knapsack_b();
    return 0;
}
