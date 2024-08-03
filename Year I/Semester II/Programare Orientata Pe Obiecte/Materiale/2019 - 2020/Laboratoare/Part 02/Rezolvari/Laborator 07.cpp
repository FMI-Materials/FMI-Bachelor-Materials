#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Animal
{
    int age;
    string name;

public:
    Animal(int a = 0, string n = "") : age(a),name(n){}

    virtual void Zice() = 0;
};

class Caine : public Animal
{
    string rasa;

public:
    Caine(int a, string n = "", string r = "caine") : Animal(a, n),rasa(r){}

    void Zice() override{
        cout << "HAM!\n";
    }
};

class Pisica : public Animal{
    string rasa;

public:
    Pisica(int a, string n = "", string r = "pisica") : Animal(a, n),rasa(r){}

    void Zice() override{
        cout << "Miau!\n";
    }
};

class Hamster : public Animal{
    string rasa;
public:
    Hamster(int a, string n = "", string r = "hamster"): Animal(a, n), rasa(r){}

    void Zice() override{
        cout << "Hatz!\n";
    }
};

class Papagal : public Animal{
    string rasa;
public:
    Papagal(int a, string n = "", string r = "papagal"): Animal(a, n), rasa(r){}

    void Zice() override{
        cout << "Johnule!\n";
    }
};

class C{
    int m;
public:
    C(): m(88){}
    void f() const{
        const_cast<C*>(this)->m = 11;
    }
    int get(){
        return m;
    }
};

int main()
{
    //Animal *a1 = new Caine(5, "rex", "maidanez");
    //Animal *a2 = new Pisica(3, "natasha", "pisica");

    vector<Animal *> animale;

    //a1->Zice();
    //a2->Zice();

    srand(time(nullptr));

    for (int i = 0; i < 10; i++){
        int tip = rand() % 4;
        switch (tip){
            case 0:
                animale.push_back(new Caine(rand() % 12, ""));
                break;
            case 1:
                animale.push_back(new Pisica(rand() % 15, ""));
                break;
            case 2:
                animale.push_back(new Hamster(rand() % 15, ""));
                break;
            case 3:
                animale.push_back(new Papagal(rand() % 15, ""));
                break;
        }
    }

    for(auto &animal : animale)
        if(dynamic_cast<Pisica*>(animal))
            cout<<"Pisica\n";
        else if(dynamic_cast<Caine*>(animal))
            cout<<"Caine\n";
        else if(dynamic_cast<Hamster*>(animal))
            cout<<"Hamster\n";
        else if(dynamic_cast<Papagal*>(animal))
            cout<<"Papagal\n";

    int a = 6;
    const int &b = a;
    a = 8;
    cout<<b<<'\n';
    const_cast<int&>(b) = 4;


    C c;
    c.f();
    cout<<c.get();
    return 0;
}
