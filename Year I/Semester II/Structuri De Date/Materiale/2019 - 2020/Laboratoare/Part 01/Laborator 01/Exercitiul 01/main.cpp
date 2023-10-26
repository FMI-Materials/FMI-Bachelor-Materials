#include <iostream>

#include <fstream>
using namespace std;
int n;
pair<int,int> minCirc(int a[100]){
    int left = 0, right = n-1, i;
    if(a[0]<a[n-1]) return make_pair(a[0], 0);
    while(left<=right){
        if(left == right) return make_pair(a[left], left);
        i = left + (right-left)/2;
        if(a[i] < a[i-1]) return make_pair(a[i], i);
        else if(a[i] > a[n-1]) left = i + 1;
        else right = i - 1;
    }
}

int firstCirc(int a[100], int e){
    pair<int, int> valori = minCirc(a);
    int nrmin = valori.first;
    if(e < nrmin || (e > a[valori.second-1] && valori.second !=0) || (e > a[n-1] && valori.second == 0)) return -1;
    else if( e == nrmin) return valori.second;
    else{
        int left, right;
        int poz = valori.second;
        if(e > a[n-1]){
            left = 0;
            right = poz -1;
        }
        else{
            left = poz +1;
            right = n - 1;
        }
        int i;
        while(left<=right){
            i = left + (right-left)/2;
            if(a[i] == e) return i;
            if(a[i] < e) left = i + 1;
            else right = i - 1;
        }
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
    cout<<minCirc(v).first<< " "<<minCirc(v).second<<endl;
    cout<<firstCirc(v, 36);
    fin.close();
    return 0;
}
