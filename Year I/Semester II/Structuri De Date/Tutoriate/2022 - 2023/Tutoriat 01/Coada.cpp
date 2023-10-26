/*
Rezolvarea problemei https://www.pbinfo.ro/probleme/876/coada

*/
#include <iostream>
#include <queue> // avem nevoie de aceasta biblioteca ca sa avem acces la clasa queue

using namespace std;

void SolveNormal()
{
    int T;
    cin >> T;
    int Nmax = 1000;
    int Coada[Nmax];
    int Left = 0, Right = 0;
    while(T--)
    {
        char query[10];
        cin >> query;
        // Nu verificam tot cuvantul, ci doar ce avem nevoie ca sa distingem opeartiile intre ele
        if(query[1] == 'u')
        {
            int x;
            cin >> x;
            if(Right == Nmax)
            {
                //Realocam coada
                int aux[Nmax];

                for(int i = Left; i < Right; ++i)
                    aux[i] = Coada[i];

                for(int i = 0; i < (Right - Left); ++i)
                    Coada[i] = aux[Left + i];

                Right = Right - Left + 1;
                Left = 0;

                //cout << "Coada plina!\n";
                continue;
            }
            Coada[Right++] = x;
        }
        else if(query[0] == 'p')
        {
            if(Left == Right)
            {
                //cout << "Coada goala!\n";
                continue;
            }
            Left++;
        }
        else
        {
            if(Left == Right)
            {
                //cout << "Coada goala!\n";
                continue;
            }
            cout << Coada[Left] << '\n';
        }
    }
}

void SolveSTL()
{
    int T;
    cin >> T;
    queue<int> Coada; // Coada de int-uri
    while(T--)
    {
        char query[10];
        cin >> query;
        if(query[1] == 'u')
        {
            int x;
            cin >> x;
            Coada.push(x);
        }
        else if(query[0] == 'p')
        {
            if(!Coada.empty())
                Coada.pop();
        }
        else
        {
            cout << Coada.front() << '\n';
        }
    }
}

int main()
{
    SolveNormal();
    //SolveSTL();
    return 0;
}
