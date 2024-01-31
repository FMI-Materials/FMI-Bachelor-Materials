#include <iostream>
#include <fstream>

using namespace std;

int max_sum(ifstream &in){
    int k, x, total = 0;
    in>>k;
    while(in>>x){
        if(x + total <= k)
            total += x;
        else if(total < x)
            total = x;
    }
    return total;
}

int main(){
    ifstream fin("data.in");
    cout<<max_sum(fin);
    return 0;
}