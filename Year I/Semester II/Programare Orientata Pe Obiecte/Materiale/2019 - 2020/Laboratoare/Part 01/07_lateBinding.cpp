#include<iostream>
using namespace std;
class baza
{
public:
    virtual void functie() { cout<<"In baza \n"; }
};

class derivata: public baza
{
public:
    void functie() { cout<<"In derivata \n"; }
};

int main(void)
{
    baza *bp = new derivata;
    bp->functie(); ///Runtime (am discutat si data trecuta)

    return 0;
}
