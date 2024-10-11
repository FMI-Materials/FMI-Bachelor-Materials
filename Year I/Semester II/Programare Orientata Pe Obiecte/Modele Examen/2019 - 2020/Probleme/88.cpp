#include <iostream.h>
class B {
    int i;

public:
    B() { i = 1; }
    int get_i() { return i; }
};
class D : public B {
    int j;

public:
    D() { j = 2; }
    int get_j() { return j; }
};
int main()
{
    B* p;
    int x = 0;
    if (x)
        p = new B;
    else
        p = new D;
    if (typeid(p).name() == "D*")
        cout << ((D*)p)->get_j();
    return 0;
}