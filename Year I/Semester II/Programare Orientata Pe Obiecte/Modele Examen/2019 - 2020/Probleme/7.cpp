#include <iostream.h>
#include <typeinfo>
class B {
    int i;

public:
    B() { i = 1; }
    int get_i() { return i; }
};
class D : B {
    int j;

public:
    D() { j = 2; }
    int get_j() { return j; }
};
int main()
{
    B* p = new D;
    cout << p->get_i();
    if (typeid((B*)p).name() == "D*")
        cout << ((D*)p)->get_j();
    return 0;
}
