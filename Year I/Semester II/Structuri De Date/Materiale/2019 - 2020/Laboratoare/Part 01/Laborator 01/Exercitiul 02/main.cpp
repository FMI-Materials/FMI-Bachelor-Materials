#include <iostream>
#include <fstream>
using namespace std;

int lastAlmost(int a[100], int k, int e){

}

int main()
{
    ifstream fin("date.in");
    int v[100];
    fin>>n;
    for(int i = 0; i < n; i++)
        fin>>v[i];
    cout<<lastAlmost(v, 2, 5);
    fin.close();
    return 0;
}
