/*
Rezolvarea problemei https://www.pbinfo.ro/probleme/875/stiva


*/
#include <iostream>
#include <stack>   // avem nevoie de aceasta biblioteca ca sa avem acces la clasa stack

using namespace std;

void SolveNormal()
{
    int T;
    cin >> T;
    int Nmax = 1000;
    int Stiva[Nmax];
    int MarimeStiva = 0;
    while(T--)
    {
        char query[10];
        cin >> query;
        // Nu verificam tot cuvantul, ci doar ce avem nevoie ca sa distingem opeartiile intre ele
        if(query[1] == 'u')
        {
            int x;
            cin >> x;
            if(MarimeStiva == Nmax)
            {
                //cout << "Stiva plina!\n";
                continue; // continue sare peste instructiunile urmatoare si trece la urmatoarea iteratie in while
            }

            Stiva[MarimeStiva++] = x;
        }
        else if(query[0] == 'p')
        {
            if(MarimeStiva == 0)
            {
                //cout << "Stiva goala!\n";
                continue;
            }
            // Nu vrem sa pierdem timp stergand efectiv elemente din memorie.
            // E suficient doar sa actualizam marimea curenta a stivei, permitand apoi la adaugare sa scriem peste elementele vechi.
            MarimeStiva--;
        }
        else
        {
            if(MarimeStiva == 0)
            {
                //cout << "Stiva goala!\n";
                continue;
            }
            cout << Stiva[MarimeStiva - 1] << '\n';
        }
    }
}

void SolveSTL()
{
    int T;
    cin >> T;
    stack<int> Stiva; // Stiva de int-uri
    while(T--)
    {
        string query; // echivalentul mult mai flexibil al lui char[]
        cin >> query;

        if(query[1] == 'u')
        {
            int x;
            cin >> x;
            Stiva.push(x); // Adauga x in varful stivei
        }
        else if(query[0] == 'p')
        {
            if(!Stiva.empty()) // metoda empty returneaza 1 daca stiva e goala, 0 altfe. Verificam intotdeauna daca stiva nu e goala
                Stiva.pop();
        }
        else
        {
            if(!Stiva.empty())
                cout << Stiva.top() << '\n';
        }
    }
}

int main()
{
    //SolveNormal();
    SolveSTL();
    return 0;
}
