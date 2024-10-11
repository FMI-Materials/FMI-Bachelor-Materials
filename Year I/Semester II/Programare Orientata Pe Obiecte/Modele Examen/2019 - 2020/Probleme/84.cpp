#include <iostream.h>
class B {
    static int x;
    int i;

public:
    B()
    {
        x++;
        i = 1;
    }
    ~B() { x--; }
    static int get_x() { return x; }
    int get_i() { return i; }
};
int B::x;
class D : public B {
public:
    D() { x++; }
    ~D() { x--; }
};
int f(B* q)
{
    return (q->get_i()) + 1;
}
int main()
{
    B* p = new B;
    cout << f(p);
    delete p;
    p = new D;
    cout << f(p);
    delete p;
    cout << D::get_x();
    return 0;
}