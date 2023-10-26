#include <iostream>
#include <string.h> // biblioteca de care apartin memcpy si memset
#include <vector>

using namespace std;

class Vector
{
    int N;
    int VectorSize; // de obicei se alege un numar putere de-a lui doi
    int *v;
public:
    // CONSTRUCTORS & DESTRUCTORS
    Vector(int,int,int); // Vector Size
    ~Vector();
    // SIZE & CAPICITY METHODS
    void Resize();
    int GetSize();
    int GetCapacity();
    bool isEmpty();
    // ELEMENT ACCESS
    int At(int);
    int Front();
    int Back();
    // MODIFIERS
    void Assign(int,int,int);
    void Push_Back(int);
    void Pop_Back();
    // BONUS DE LA MINE
    void Print();
    void PrintToCap();
};

/*
Vectorul are o capacitate data
(in std::vector lucrul acesta se intampla in culise,
fiind nevoie doar sa-i dam marimea de lucru la declarare, adica N-ul nostru)
*/
Vector::Vector(int N, int val, int VectorSize)
{
    this->N = N;
    this->VectorSize = VectorSize;
    this->v = new int[VectorSize]();  // initializeaza un vector cu toate elemente 0, datorita parantezelor din urma lasate goale.
                                    // Punand orice valoare in ele, vectorul se va initializa cu aceasta peste tot.
    for(int i = 0; i < N; ++i)
        v[i] = val;
}

/*
Metoda care se apeleaza cand marimea vectorului atinge capacitatea.
Ca std::vector, o sa alocam de doua ori mai multa memorie, deoarece calculatorul lucreaza mai usor cu multipli si mai ales puteri de-ale lui 2.
*/
void Vector::Resize()
{
    int aux[N];
    memcpy(aux,v,sizeof(aux)); // copiaza toate datele din v in aux.
                               // Este echivalentul unui for de la 0 la N - 1 in care facem atribuirea aux[i] = v[i]
    delete[] v;
    VectorSize *= 2;
    v = new int[VectorSize];

    memcpy(v,aux,sizeof(aux));
}

int Vector::GetSize()
{
    return N;
}

int Vector::GetCapacity()
{
    return VectorSize;
}

// cand N e 0 ca int o sa faca conversie in bool la false, altfel o sa returneze true
bool Vector::isEmpty()
{
    return (N == 0 ? true : false);
}

Vector::~Vector()
{
    delete[] v;
}

int Vector::At(int position)
{
    return v[position];
}

int Vector::Front()
{
    return v[0];
}

int Vector::Back()
{
    return v[N - 1];
}

void Vector::Assign(int Start, int End, int val)
{
    for(int i = Start; i < End; ++i)
        v[i] = val;
}

void Vector::Push_Back(int val)
{
    if(N == VectorSize)
        Resize();
    v[N++] = val;
}

void Vector::Pop_Back()
{
    N--;
}

void Vector::Print()
{
    cout << "Afisare Vector cu elemente de la 0 la N - 1:\n";
    for(int i = 0; i < N; ++i)
        cout << v[i] <<  " ";
    cout << '\n';
}

void Vector::PrintToCap()
{
    cout << "Afisare Vector cu elemente de la 0 la VectorSize - 1:\n";
    for(int i = 0; i < VectorSize; ++i)
        cout << v[i] <<  " ";
    cout << '\n';
}

void AfisareTest(Vector& myVectorA, vector<int>& myVectorB)
{
    myVectorA.PrintToCap();

    myVectorA.Push_Back(1);
    myVectorA.Push_Back(2);
    myVectorA.Push_Back(3);
    myVectorA.Push_Back(4);
    myVectorA.Push_Back(5);

    myVectorA.Print();

    myVectorA.Pop_Back();
    myVectorA.Pop_Back();

    myVectorA.Print();

    myVectorB.push_back(11);
    myVectorB.push_back(12);
    myVectorB.push_back(13);
    myVectorB.push_back(14);
    myVectorB.push_back(15);

    //Varianta 1 (Greu de scris si urata)
    cout << "Afisare std::vector cu iterator:\n";
    vector<int>::iterator it; // nu ne place de el. Nu-l folosim in practica
    for(it = myVectorB.begin(); it != myVectorB.end(); ++it) // Mergem din adresa in adresa ca la listele inlantuite
        cout << *it << " ";
    cout << '\n';

    myVectorB.pop_back();
    myVectorB.pop_back();

    //Varianta 2 (The good way)
    cout << "Afisare std::vector cu range-based loop:\n";
    for(int i : myVectorB)
        cout << i << " ";
    cout << '\n';
    /*
        In loc de "int", in general folosim tipul de date al vectorului
        sau
        daca nu vrem sa ne batem capul cu tipuri de date putem scrie direct
        keyword-ul "auto".
    */
}

int main()
{
    int N = 0;
    int VectorSize = 6;
    Vector myVectorA(N, 0, VectorSize);

    vector<int> myVectorB (N, 0); // echivalent cu
                                  // vector<int> myVectorB (N);
                                  // OBS: nu mentionam capacitatea vectorului. E treaba compilatorului

    AfisareTest(myVectorA, myVectorB);

    return 0;
}
