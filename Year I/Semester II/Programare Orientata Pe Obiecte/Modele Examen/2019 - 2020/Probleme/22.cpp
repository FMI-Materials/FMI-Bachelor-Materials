#include <iostream>
#include <typeinfo>
using namespace std;
class B {
    int i;

public:
    B(int x) { i = x + 1; }
    int get_i() { return i; }
};
class D : public B {
    int j;

public:
    D()
        : B(1)
    {
        j = i + 2;
    }
    int get_j() { return j; }
};
int main()
{
    B* p = new D[10];
    cout << p->get_i();
    if (typeid((B*)p).name() == "D*")
        cout << ((D*)p)->get_j();
    return 0;
}