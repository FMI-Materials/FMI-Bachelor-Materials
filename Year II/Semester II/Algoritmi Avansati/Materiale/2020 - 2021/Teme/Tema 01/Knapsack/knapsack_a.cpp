#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

int max_sum(int k, const vector<int>& nums){
    int total = 0;
    unordered_set<int> values;
    values.insert(0);
    for(auto num: nums)
        for(auto val: values)
            if(val + num <= k){
                total = max(total, val + num);
                values.insert(val + num);
            }
    return total;
}

int main(){
    ifstream fin("data.in");
    int k, x;
    vector<int> nums;
    fin>>k;
    while(fin>>x)
        nums.emplace_back(x);
    cout<<max_sum(k, nums);
    return 0;
}