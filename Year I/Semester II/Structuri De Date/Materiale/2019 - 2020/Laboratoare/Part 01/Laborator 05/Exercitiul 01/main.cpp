#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int n, v[1000000], m;
vector<pair<int, int>> bitonic;
int main()
{
    ifstream fin("bitone.in");
    ofstream fout("bitone.out");
    fin>>n;
    int cresc, descresc, k = 0;
    pair<int, int> aux = make_pair(1,1);
    fin>>v[0];
    for(int i = 1; i < n; i++){
        fin>>v[i];
        if(v[i]==v[i-1]){
            k++;
        }
        if(v[i]>v[i-1]){
            if(descresc){
                cresc = 1;
                descresc = 0;
                if(i!=1){ aux.second = i;
                bitonic.push_back(aux);}
                aux.first = i-k;
                k = 0;

            }
        }
        else if(v[i] < v[i-1]){
            if(cresc){
                cresc = 0;
                descresc = 1;
                k = 0;
            }
        }
    }
    aux.second = n;
    bitonic.push_back(aux);/*
    for(auto& i: bitonic){
        cout<<i.first<<" "<<i.second<<endl;
    }*/
    int nr_set = bitonic.size();
    fin>>n;
    for(int i = 0; i < n; i++){
        int a, b;
        fin>>a>>b;
        if(a >= bitonic[nr_set-1].first || a == b){
            fout<<"1";
        }
        else{
            int stg = 0, dr = nr_set-1, poz_a, poz_b;
            while(stg <= dr){
                if(stg == dr){
                    poz_a = stg;
                    break;
                };
                int mij = stg + (dr-stg)/2;
                if(bitonic[mij+1].first > a && bitonic[mij].first <= a){
                    poz_a = mij;
                    break;
                }
                else if(bitonic[mij].first > a) dr = mij-1;
                else stg = mij + 1;
            }
            if(b >= bitonic[nr_set-1].second) poz_b = nr_set-1;
            else if(b <= bitonic[0].second) poz_b = 0;
            else{
                stg = 0; dr = nr_set-1;
                while(stg <= dr){
                    if(stg == dr){
                        poz_b = stg;
                        break;
                    };
                    int mij = stg + (dr-stg)/2;
                    if(bitonic[mij].second >= b && bitonic[mij-1].second < b){
                        poz_b = mij;
                        break;
                    }
                    else if(bitonic[mij].second > b) dr = mij-1;
                    else stg = mij + 1;
                }
            }
            ///cout<<"*"<<poz_a<<"+"<<poz_b<<"*";
            if(poz_a == poz_b || b <= bitonic[poz_a].second) fout<<"1";
            else fout<<"0";
        }
    }
    fin.close();
    fout.close();
    return 0;
}
