#include<iostream>
using namespace std;
class baza
{
public:
    void functie() { cout<<"In baza \n"; }
};

class derivata: public baza
{
public:
    void functie() { cout<<"In derivata \n"; }
};

int main(void)
{
    baza *bp = new derivata;
    ///Apelarea functiei este decisa la momentul compilarii
    ///Compilatorul vede tipul pointerului si apeleaza functia
    ///din clasa de baza
    bp->functie();

    return 0;
}
