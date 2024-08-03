#include <iostream>
#include <fstream>
using namespace std;
int n;
int peak(int a[100]){
    int left = 0, right = n-1, mij;
    while(left <= right){
        if(left == right) return right;
        mij = left + (right-left)/2;
        if(mij == 0) return 0;
        else if(mij == n-1) return n-1;
        else if(a[mij] >= a[mij+1] && a[mij] > a[mij-1]) return mij;
        else if(a[mij] <= a[mij-1]) right = mij - 1;
        else left = mij + 1;
    }
}

int binarySearch(int a[100], int left, int right, int val){
    int mij;
    while(left <= right){
        mij = left + (right - left)/2;
        if(a[mij] == val) return mij;
        else if(a[mij] < val) left = mij + 1;
        else right = mij -1;
    }
    return -1;
}

int existsBitonic(int a[100], int e){
    int poz_peak = peak(a), left, right, mij;
    if(a[poz_peak] < e || a[0] > e || a[n-1] > e) return -1;
    else if(a[poz_peak] == e) return poz_peak;
    else{
        int x = binarySearch(a, 0, poz_peak + 1, e);
        int y = binarySearch(a, poz_peak + 1, n-1, e);
        if(x != -1) return x;
        else if(y != -1) return y;
        return -1;
    }
}

int main()
{

    ifstream fin("date.in");
    int v[100];
    fin>>n;
    for(int i = 0; i < n; i++)
        fin>>v[i];
    cout<<peak(v)<<endl;
    cout<<existsBitonic(v, 5);
    fin.close();
    return 0;
}
