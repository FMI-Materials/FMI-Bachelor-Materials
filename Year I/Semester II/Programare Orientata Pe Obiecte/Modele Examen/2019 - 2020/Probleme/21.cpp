#include <iostream>
using namespace std;
class A {
public:
    int x;
    A(int i = -13) { x = i; }
};
class B : virtual public A {
public:
    B(int i = -15) { x = i; }
};
class C : virtual public A {
public:
    C(int i = -17) { x = i; }
};
class D : virtual public A {
public:
    D(int i = -29) { x = i; }
};
class E : public B, public D, public C {
public:
    int y;
    E(int i, int j)
        : D(i)
        , B(j)
    {
        y = x + i + j;
    }
    E(E& ob) { y = ob.x - ob.y; }
};
int main()
{
    E e1(5, 10), e2 = e1;
    cout << e2.y;
    return 0;
}