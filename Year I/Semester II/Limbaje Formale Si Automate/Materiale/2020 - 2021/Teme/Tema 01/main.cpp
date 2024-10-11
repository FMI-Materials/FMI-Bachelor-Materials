#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

int nr_noduri, nr_muchii, start, final, nr_final, nod_initial, nod_final, nr_stringuri;

// a este matricea de adiacenta

char a[101][101], sir_caractere[101];
int v[101], drum;
int nr[101];

stack <int> stiva;

int parcurgere(int start, int index)
{
    stiva.push(start);
    int ok = 0;
    for(int i = start; i < nr_noduri; i++)
    {
        if(a[start][i] == sir_caractere[index])
        {
            parcurgere(i, index + 1);
            ok = 1;
        }
    }
    if(ok == 1)
    {
        if(stiva.size() == strlen(sir_caractere))
            return 1;
        else
            stiva.pop();
    }
    else
        stiva.pop();
    if(stiva.empty())
        return 0;
}

void afisare()
{
    while(!stiva.empty())
    {
        int top = stiva.top();
        stiva.pop();
        afisare();
        v[++drum] = top;
    }
}

int main()
{
    f >> nr_noduri >> nr_muchii;
    char z;
    for(int i = 0; i < nr_noduri; i++)
        for(int j = 0; j < nr_noduri; j++)
            a[i][j] = '*';

    for(int i = 0; i < nr_muchii; i++)
    {
        f >> nod_initial >> nod_final >> z;
        a[nod_initial][nod_final] = z;
    }

    f >> start >> nr_final;


    for(int i = 0; i < nr_final; i++)
        f >> nr[i];

    f >> nr_stringuri;

    for(int i = 0; i < nr_stringuri; i++)
    {
        drum = 0;
        f >> sir_caractere;
        g << sir_caractere << endl;
        int ok = 0;
        for(int j = 0; j < nr_final; j++)
        {
            final = nr[j];
            if(parcurgere(start, 0))
                ok = 1;
        }
        if(ok)
        {
            afisare();
            v[++drum] = final;
            for(int i = 1; i < drum; i++)
                if(a[v[i]][v[i+1]] == '*')
                    ok = 0;
            if(ok)
            {
                g << "DA " << endl << "Traseu ";
                for(int i = 1; i <= drum; i++)
                    g << v[i] << " ";
                g << endl;
            }
            else
                g << "NU" << endl;
        }
        else g << "NU" << endl;
    }
    return 0;
}