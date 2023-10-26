#include <iostream>
#include <fstream>

using namespace std;

int v[500000],n;

void unionVect(int left, int right, int middle){
    int c[right-left+1];
    int i = left, j = middle + 1, k = 0;
    while(i <= middle && j <= right){
        if(v[i]<v[j]){
            c[k++] = v[i];
            i++;
        }
        else{
            c[k++] = v[j];
            j++;
        }

    }
    while(i <= middle){
        c[k++] = v[i];
        i++;
    }
    while(j <= right){
        c[k++] = v[j];
        j++;
    }
    for(int i = left; i <= right; i++){
        v[i] = c[i-left];
    }
}

void mergeSort(int left, int right){
    if(left<right){
        int middle = left + (right-left)/2;
        mergeSort(left,middle);
        mergeSort(middle+1, right);
        unionVect(left, right, middle);
    }
}

int main()
{
    ifstream fin("algsort.in");
    ofstream fout("algsort.out");
    fin>>n;
    for(int i = 0; i < n; i++){
        fin>>v[i];
    }
    mergeSort(0,n-1);
    for(int i = 0; i < n; i++){
        fout<<v[i]<<" ";
    }
    fin.close();
    fout.close();
    return 0;
}
