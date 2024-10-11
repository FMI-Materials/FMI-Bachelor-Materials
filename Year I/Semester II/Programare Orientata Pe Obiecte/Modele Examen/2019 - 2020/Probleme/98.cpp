#include <iostream>
using namespace std;

class A {
    int x;

public:
    A(int i = 2)
        : x(i)
    {
    }
    int get_x() const { return x; }
};
class B : public A {

    int* y;

public:
    B(int i = 2)
        : A(i)
    {
        y = new int[i];
        for (int j = 0; j < i; j++)
            y[j] = 1;
    }
    B(B& b)
    {
        y = new int[b.get_x()];
        for (int i = 0; i < b.get_x(); i++)
            y[i] = b[i];
    }
    int& operator[](int i) const { return y[i]; }
};
ostream& operator<<(ostream& o, const B b)
{
    for (int i = 0; i < b.get_x(); i++)
        o << b[i];
    return o;
}



int main()
{
    const B b(5);
    cout << b;
    return 0;
}
