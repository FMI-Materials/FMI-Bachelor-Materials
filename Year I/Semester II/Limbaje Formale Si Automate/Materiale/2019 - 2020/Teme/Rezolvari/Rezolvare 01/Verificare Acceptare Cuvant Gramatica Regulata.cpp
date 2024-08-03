#include <iostream>
#include <cstring>

using namespace std;
int numarSimboluriNeterminale, numarSimboluriTerminale, numarProductii;
char *simboluriNeterminale;
char *simboluriTerminale;
struct productie{
    char simbolNeterminal1, simbolTerminal, simbolNeterminal2;
}*reguliDeProductie;
char simbolCurent;

void citireGramaticaRegulata(){
    numarSimboluriNeterminale = numarSimboluriTerminale = numarProductii = 0;
    int i;
    cout<<"Numar simboluri neterminale? ";
    cin >> numarSimboluriNeterminale;
    simboluriNeterminale = new char[numarSimboluriNeterminale];
    cout<<"Scrieti "<<numarSimboluriNeterminale<<" simboluri neterminale: ";
    for (i=0;i<numarSimboluriNeterminale;i++)
        cin >> simboluriNeterminale[i];
    cout<<"Numar simboluri terminale? ";
    cin >> numarSimboluriTerminale;
    simboluriTerminale = new char[numarSimboluriTerminale];
    cout<<"Scrieti "<<numarSimboluriTerminale<<" simboluri terminale: ";
    for (i = 0; i < numarSimboluriTerminale; i++)
        cin >> simboluriTerminale[i];
    cout<<"Scrieti numarul de productii: ";
    cin >> numarProductii;
    reguliDeProductie = new productie[numarProductii];
    for (i = 0; i < numarProductii; i++) {
        cin >> reguliDeProductie[i].simbolNeterminal1;
        cin >> reguliDeProductie[i].simbolTerminal;
        cin >> reguliDeProductie[i].simbolNeterminal2;
    }
}
///afisare gramatica
void afisare(){
    int i;
    cout << numarSimboluriNeterminale << endl;
    for (i = 0; i < numarSimboluriNeterminale; i++)
        cout << simboluriNeterminale[i] << ' ';
    cout << endl << numarSimboluriTerminale << endl;
    for (i = 0; i < numarSimboluriTerminale; i++)
        cout << simboluriTerminale[i] << ' ';
    cout << endl << numarProductii << endl;
    for (i = 0; i < numarProductii; i++) {
        cout << reguliDeProductie[i].simbolNeterminal1 << ' ';
        cout << reguliDeProductie[i].simbolTerminal << ' ';
        cout << reguliDeProductie[i].simbolNeterminal2 << endl;
    }
    cout << simbolCurent;
}

///verificare cuvant --- return true, in cazul in care cuvantul apartine limbajului generat de gramatica si false, in caz contrar
bool verificare(char *cuvant){
    int i;
    if (cuvant[0] == '\0') ///am ajuns la finalul cuvantului
    {
        if (simbolCurent == '_')
            return true;
        for (i = 0; i < numarProductii; i++) {
            if ((reguliDeProductie[i].simbolNeterminal1 == simbolCurent) &&
                (reguliDeProductie[i].simbolTerminal == '_') &&
                (reguliDeProductie[i].simbolNeterminal2 == '_'))
                ///daca avem o productie de tipul simbol curent -> gramatica generata de cuvantul vid
                return true; ///cuvantul apartine limbajului generat de gramatica
        }
        return false;
    }
    else ///nu am ajuns la finalul cuvantului
    {
        char simbolAuxiliar = simbolCurent;
        for (i = 0; i < numarProductii; i++)
            ///caut regulile de productie de forma (simbol curent) -> (caracterul la care am ajuns) sau
            /// (simbol curent) -> (caracterul la care am ajuns) (simbol neterminal)
            if (reguliDeProductie[i].simbolNeterminal1 == simbolAuxiliar && reguliDeProductie[i].simbolTerminal == cuvant[0])
            {
                simbolCurent = reguliDeProductie[i].simbolNeterminal2;
                if (verificare(cuvant + 1)) return true; ///tai prima litera, deoarece a fost verificata
            }
        return false;
    }
}
int main() {
    int numarCuvinte, i;
    citireGramaticaRegulata();
    simbolCurent='S'; ///simbolul de start este mereu S
    cout<<"Numar de cuvinte: ";
    cin >> numarCuvinte;
    cout<<"Cuvinte: ";
    for (i = 0; i < numarCuvinte; i++) {
        char *cuvant = new char[101];
        cin >> cuvant;
        if (strcmp(cuvant, "_") == 0) ///daca am cuvantul vid
            cuvant[0] = '\0';
        if (verificare(cuvant))
            cout << "Cuvantul " << cuvant << " apartine limbajului generat de gramatica" << '\n';
        else cout << "Cuvantul " << cuvant << " nu apartine limbajului generat de gramatica" << '\n';
        delete[] cuvant;
        simbolCurent = 'S'; ///reinitializare a simbolului curent (de start)
    }
    delete[] simboluriNeterminale;
    delete[] simboluriTerminale;
    delete[] reguliDeProductie;
    return 0;
}

/*
Ex 1
2
S A
3
a b c
4
SaS
SbA
A__
AcA
*/
