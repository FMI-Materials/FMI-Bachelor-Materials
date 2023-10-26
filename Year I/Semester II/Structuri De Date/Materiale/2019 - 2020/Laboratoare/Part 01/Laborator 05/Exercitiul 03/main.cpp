#include <iostream>
#include <fstream>
using namespace std;

int v[500000],n;

void quickSort(int left, int right){
    int pivot = right;
    int i = left, j = right-1;
    while(i<j){
        while(v[i] < v[pivot] && i <right) i++;
        while(v[j] > v[pivot] && j > 0) j--;
        if(i<j) swap(v[i], v[j]);
    }
    swap(v[i],v[pivot]);
    if(left < i-1) quickSort(left, i-1);
    if(i+1 < right) quickSort(i+1, right);
}
int main()
{
    ifstream fin("algsort.in");
    ofstream fout("algsort.out");
    fin>>n;
    for(int i = 0; i < n; i++){
        fin>>v[i];
    }
    quickSort(0,n-1);
    for(int i = 0; i < n; i++){
        fout<<v[i]<<" ";
    }
    fin.close();
    fout.close();
    return 0;
}
