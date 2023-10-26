#include <iostream>
#include <fstream>
using namespace std;
struct arbore
{
    
    int info;
    arbore * stang, * drept;
};
arbore* radacina;

void inserare(arbore *& rad, int nr)
{
    if (rad == NULL)
    {
        rad = new arbore;
        rad->info = nr;
        rad->stang = rad->drept = NULL;
        return;
    }
    if (nr < rad->info)
        inserare(rad->stang, nr);
    else
        if (nr > rad->info)
            inserare(rad->drept, nr);
        else
            cout << nr << " exista deja in arbore" << endl;
}
void SRD(arbore* r)
{

    if (r != NULL) {

        SRD(r->stang);
        cout << r->info << " ";
        SRD(r->drept);

    }

}
void SDR(arbore* r, int cheie, int &bec)//folosit in cautare
{

    if (r != NULL) {

        SDR(r->stang, cheie, bec);
        SDR(r->drept, cheie, bec);
        if (r->info == cheie)
        {
            bec = 1;
            return;
        }

    }

}
int cauta(arbore* r, int cheie)
{
    int bec = 0;
    SDR(r, cheie, bec);
    return bec;
}
void RSD(arbore* r)
{

    if (r != NULL) {

        cout << r->info << " ";
        RSD(r->stang);
        RSD(r->drept);
      

    }

}


void stergere(arbore *& rad, int nr)
{
    arbore * p, * q;
    if (rad == NULL)
    {
        cout << " arborele nu contine " << nr << endl;
        return;
    }
    if (nr < rad->info)
        stergere(rad->stang, nr);
    if (nr >rad->info)
        stergere(rad->drept, nr);
    if (nr == rad->info)
    {
        if (rad->drept == NULL)
        {
            q = rad;
            rad = q->stang;
            delete q;

        }
        else
            if (rad->stang == NULL)
            {
                q = rad;
                rad = q->drept;
                delete q;
            }
            else
            {
                for (q = rad, p = rad->stang; p->drept; q = p, p = p->drept);
                rad->info = p->info;
                if (rad->stang == p)
                    rad->stang = p->stang;
                else
                    q->drept = p->stang;
                delete p;
            }
    }
}
void citire()
{
    int i, n,nr;
    ifstream f("in.txt");
    f>> n;
    for (i = 0; i < n; i++)
    {
            f >> nr;
            inserare(radacina, nr);
    }
    
    
}

int main()
{
    
    //6 4 9 2 1 5 3 7 8 n=9;
    int x;
    citire();
    cout << "SRD: ";
    SRD(radacina);
    cout << endl << "RSD: ";
    RSD(radacina);
    cout<<endl<<"sterg cheia x: ";
    cin >> x;
    stergere(radacina, x);
    cout << "dupa stergere: "<<endl;
    cout << "SRD: ";
    SRD(radacina);
    cout << endl << "RSD: ";
    RSD(radacina);
    cout << endl << "dati o cheie x de cautat: ";
    cin >> x;
    cout << cauta(radacina, x);
    cout << endl << "dati o cheie x de inserat: ";
    cin >> x;
    inserare(radacina, x);
    cout << "dupa inserare: " << endl;
    cout << "SRD: ";
    SRD(radacina);
    cout << endl << "RSD: ";
    RSD(radacina);

   
    

}


