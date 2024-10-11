#include <iostream>
using namespace std;
class A
{   static int *x;
    public: A() {}
            int get_x() { return (++(*x))++; } };
int *A::x(new int(19));
int main()
{   A *p=new A,b;
    cout<<b.get_x()<<" ";
    cout<<p->get_x();
    return 0;
}
