/*Tema 27. Clasa „teatru”
Reprezentată prin:
Denumire piesă,
        Număr actori implicați,
        Preț bilet,
Rating
        Metode ce se doresc a fi implementate (se va defini un vector de piese de teatru)
Să se determine ratingul mediu al pieselor de la teatru
Să se determine piesa cu cel mai scump bilet și să se afișeze toate informațiile despre aceasta
Să se sorteze piesele în ordine descrescătoare după dimensiunea distribuției și să se returneze vectorul de piese astfel sortat
Să se sorteze piesele în ordine alfabetică după numele piesei și să se returneze vectorul de piese astfel sortat
CERINTA BONUS : Scrierea unei metode ce permite eliminarea posibilelor piese duplicate prezente in vector prin utilizarea operatorului "==" pentru a face verificarea in cauza.
*/
#include <iostream>
#include <cstring>


using namespace std;
class Teatru {
private:
    char *denumirePiesa;
    int numarActoriImplicati;
    double pretBilet;
    double rating;

    //set
    void set_denumirePiesa(char a[256]);
    void set_numarActoriImplicati(int x);
    void set_pretBilet(double x);
    void set_rating(double x);

public:
    //get
    char *get_denumirePiesa();
    int get_numarActoriImplicati();
    double get_pretBilet();
    double get_rating();


    //constructori
    // constructor fara parametrii
    Teatru(){
        this->denumirePiesa = NULL;
        this->numarActoriImplicati = 0;
        this->pretBilet = 0;
        this->rating = 0;
    }
    // constructor de copiere
    Teatru(const Teatru &t) {
        this->denumirePiesa = new char[256];
        strcpy(this->denumirePiesa, t.denumirePiesa);
        this->numarActoriImplicati = t.numarActoriImplicati;
        this->pretBilet = t.pretBilet;
        this->rating = t.rating;
    }
    // constructor cu parametrii
    Teatru(char *denumirePiesa, int nrActoriImplicati, double pretBilet, double rating) {
        this->denumirePiesa = new char[256];
        strcpy(this->denumirePiesa, denumirePiesa);
        this->numarActoriImplicati = nrActoriImplicati;
        this->pretBilet = pretBilet;
        this->rating = rating;
    }

    //destructor
    ~Teatru() {
        if (denumirePiesa != NULL) {
            cout << "DA, trebuie eu sa eliberez memoria\n";
            delete[]denumirePiesa;
        }
        denumirePiesa = NULL;
    }

    //supradefinirea  =
    Teatru& operator=(const Teatru &teatru);
    //supradefinirea  ==
    friend bool operator==(const Teatru &a, const Teatru &b) ;
    //supradefinirea  !=
    friend bool operator!=(const Teatru& a, const Teatru& b);
    //supradefinirea  >>
    friend istream& operator>>(istream &is, Teatru &teatru);
    //supradefinirea  <<
    friend ostream& operator<<(ostream &os, const Teatru &teatru);

    //Să se determine ratingul mediu al pieselor de la teatru
    friend double ratingMediu(Teatru *v, int n);
    //Să se determine piesa cu cel mai scump bilet și să se afișeze toate informațiile despre aceasta
    friend void biletScump(Teatru *v, int n);
    //Să se sorteze piesele în ordine descrescătoare după dimensiunea distribuției și să se returneze vectorul de piese astfel sortat
    friend void sortDistributie(Teatru *v, int n);
    //Să se sorteze piesele în ordine alfabetică după numele piesei și să se returneze vectorul de piese astfel sortat
    friend void sortAlfabetic(Teatru *v, int n);
    //CERINTA BONUS : Scrierea unei metode ce permite eliminarea posibilelor piese duplicate prezente in vector prin utilizarea operatorului "==" pentru a face verificarea in cauza.
    friend void eliminaDubluri(Teatru *v,int &n);
    //afisare vector
    friend void printVector(Teatru *v,int n);

};
Teatru & Teatru::operator=(const Teatru &teatru) {
    if(teatru.denumirePiesa==NULL){
        if(this->denumirePiesa!=NULL){
            char *del = this->denumirePiesa;
            this->denumirePiesa=NULL;
            delete[] del;
        }
    }
    else {
        if (this->denumirePiesa == NULL)
            this->denumirePiesa = new char[256];
        strcpy(this->denumirePiesa, teatru.denumirePiesa);
    }
    this->numarActoriImplicati=teatru.numarActoriImplicati;
    this->pretBilet=teatru.pretBilet;
    this->rating=teatru.rating;
    return *this;
}
bool operator==(const Teatru &a, const Teatru &b){
    int ok;
    if(a.denumirePiesa==NULL || b.denumirePiesa==NULL){
        if(a.denumirePiesa==NULL && b.denumirePiesa==NULL)
            ok=0;
        else
            ok=1;
    }
    else
        ok=strcmp(a.denumirePiesa,b.denumirePiesa);
    return ((ok==0) && (a.numarActoriImplicati == b.numarActoriImplicati) &&
            (a.pretBilet == b.pretBilet) && (a.rating == b.rating));
}
bool operator!=(const Teatru& a, const Teatru& b){
    return (!(a==b));
}
istream &operator>>(istream &is, Teatru &teatru){
    cout<<"Introduceti denumire piesa:\n";
    if(teatru.denumirePiesa==NULL)
        teatru.denumirePiesa=new char[256];
    is.getline(teatru.denumirePiesa,256);
    cout<<"Introduceti numarul de actori implicati:\n";
    is >> teatru.numarActoriImplicati ;
    cout<<"Introduceti pretul biletului:\n";
    is >>teatru.pretBilet;
    cout<<"Introduceti rating-ul:\n";
    is >> teatru.rating;
    is.get();
    return is;
}
ostream &operator<<(ostream &os, const Teatru &teatru) {
    os << "denumirePiesa: " << teatru.denumirePiesa << " numarActoriImplicati: " << teatru.numarActoriImplicati << " pretBilet: " << teatru.pretBilet << " rating: " << teatru.rating;
    return os;
}
//Să se determine ratingul mediu al pieselor de la teatru
double ratingMediu(Teatru *v, int n){
    double rating=0;
    for(int i = 0;i < n; ++i){
        rating+=v[i].rating;
    }
    return rating/n;
}
//Să se determine piesa cu cel mai scump bilet și să se afișeze toate informațiile despre aceasta
void biletScump(Teatru *v,int n){
    int index=0;
    for(int i=1; i<n; ++i){
        if(v[i].pretBilet>v[index].pretBilet)
            index=i;
    }
    cout << v[index]<<'\n';
}
//Să se sorteze piesele în ordine descrescătoare după dimensiunea distribuției și să se returneze vectorul de piese astfel sortat
void sortDistributie(Teatru *v, int n){
    Teatru aux; // se apeleaza constructorul
    for(int i=0; i<n; ++i)
        for(int j=i+1;j<n;++j)
            if(v[i].numarActoriImplicati<v[j].numarActoriImplicati){
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }
}
//Să se sorteze piesele în ordine alfabetică după numele piesei și să se returneze vectorul de piese astfel sortat
void sortAlfabetic(Teatru *v, int n){
    Teatru aux; // se apeleaza constructorul
    for(int i=0; i<n; ++i)
        for(int j=i+1;j<n;++j)
            if(strcmp(v[i].denumirePiesa,v[j].denumirePiesa)>0){
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }
}
//CERINTA BONUS : Scrierea unei metode ce permite eliminarea posibilelor piese duplicate prezente in vector prin utilizarea operatorului "==" pentru a face verificarea in cauza.
void eliminaDubluri(Teatru *v,int &n){
    for(int i=0;i<n;++i)
        for(int j=i+1;j<n;++j)
            if(v[i]==v[j]){
                for(int k=j+1;k<n;++k)
                    v[k-1]=v[k];
                --n;
                --j;
            }
}
void printVector(Teatru *v,int n){
    for(int i=0; i<n; ++i){
        cout<<v[i]<<'\n';
    }
}
//set
void Teatru::set_denumirePiesa(char a[256]){
    if(this->denumirePiesa == NULL)
        this->denumirePiesa=new char[256];
    strcpy(this->denumirePiesa,a);
}

void Teatru::set_numarActoriImplicati(int x){
    this->numarActoriImplicati=x;
}
void Teatru::set_pretBilet(double x){
    this->pretBilet=x;
}
void Teatru::set_rating(double x){
    this->rating=x;
}

//get
char* Teatru::get_denumirePiesa(){
    return denumirePiesa;
}
int Teatru::get_numarActoriImplicati(){
    return numarActoriImplicati;
}
double Teatru::get_pretBilet(){
    return pretBilet;
}
double Teatru::get_rating(){
    return rating;
}


int main() {
    int n;
    cout<<"Introducem numarul de piese de teatru:";
    cin>>n;
    cin.get();
    Teatru v[n];
    cout<<"Introducem piesele de teatru\n";
    for(int i = 0; i < n; ++i)
        cin >> v[i];
    cout<<'\n';
    cout<<"Piesele introduse sunt:\n";
    printVector(v,n);
    cout<<'\n';
    cout<<"Ratingul mediu este: "<<ratingMediu(v,n)<<'\n'<<'\n';
    cout<< "Cel mai scump bilet este:\n";
    biletScump(v,n);
    cout<<'\n'<<'\n';
    cout<<"Sortarea pieselor in ordine descrescatoare dupa dimensiunea distributiei:\n";
    sortDistributie(v,n);
    printVector(v,n);
    cout<<'\n'<<'\n';
    cout<<"Sortarea pieselor in ordine alfabetica dupa numele piesei:\n";
    sortAlfabetic(v,n);
    printVector(v,n);
    cout<<'\n'<<'\n';
    cout<<"Eliminarea posibilelor piese duplicate prezente in vector prin utilizarea operatorului ==:\n";
    eliminaDubluri(v,n);
    printVector(v,n);
    return 0;
}
