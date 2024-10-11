#include <iostream.h>
class problema {
    int i;

public:
    problema(int j = 5) { i = j; }
    void schimba() { i++; }
    void afiseaza() { cout << "starea curenta " << i << "\n"; }
};
problema mister1() { return problema(6); }
void mister2(problema& o)
{
    o.afiseaza();
    o.schimba();
    o.afiseaza();
}
int main()
{
    mister2(mister1()); //(1)
    return 0;
}
