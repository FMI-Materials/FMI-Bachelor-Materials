#include <iostream>
using namespace std;
class A {
    static int x;

public:
    A(int i = 0) { x = i; }
    int get_x() { return x; }
    int& set_x(int i) { x = i; }
    A operator=(A a1)
    {
        set_x(a1.get_x());
        return a1;
    }
};
int main()
{
    A a(212), b;
    cout << (b = a).get_x();
    return 0;
}
