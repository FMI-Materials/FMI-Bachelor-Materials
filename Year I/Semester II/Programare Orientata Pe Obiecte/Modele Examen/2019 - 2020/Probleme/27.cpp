#include <iostream.h>
class B {
    int i;

public:
    B() { i = 1; }
    virtual int get_i() { return i; }
};
class D : public B {
    int j;

public:
    D() { j = 2; }
    int get_i() { return B::get_i() + j; }
};
int main()
{
    const int i = cin.get();
    if (i % 3) {
        D o;
    }
    else {
        B o;
    }
    cout << o.get_i(); //(1)
    return 0;
}
