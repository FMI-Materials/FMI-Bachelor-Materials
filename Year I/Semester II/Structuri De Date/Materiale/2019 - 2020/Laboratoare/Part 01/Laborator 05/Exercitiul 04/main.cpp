#include <iostream>
#include <fstream>
#include <vector>
#define MASK 255
using namespace std;
long n;
vector<int> elem;

void CountingSort(int div){
    vector<int> aux(n), frecventa(256);
    for(auto x : elem) frecventa[(x >> div) & MASK]++;
    for(int i = 1; i <= 255; i++)
        frecventa[i] += frecventa[i-1];
    for(int i = n-1; i >= 0; i--){
        aux[frecventa[(elem[i] >> div) & MASK]] = elem[i];
        frecventa[(elem[i] >> div) & MASK]--;
    }
    elem = aux;
}

void RadixSort(){
    for(int i = 0; i < 32; i += 8){
        CountingSort(i);
    }
}

int main()
{
    ifstream fin("radixsort.in");
    ofstream fout("radixsort.out");
    long i, a, b, c;
    fin>>n>>a>>b>>c;
    elem.push_back(b);
    for(i = 1; i < n; i++){
        elem.push_back((a*elem[i-1] + b) % c);
    }
    RadixSort();
    for(i = 0; i < elem.size() - 1; i += 10){
        cout<<elem[i]<<" ";
    }
    fin.close();
    fout.close();
    return 0;
}
