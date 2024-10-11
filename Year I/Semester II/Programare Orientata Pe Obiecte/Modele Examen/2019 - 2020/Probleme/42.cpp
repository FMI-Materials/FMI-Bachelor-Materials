#include<iostream>
using namespace std;
class A
{
    int i;
    public: A() {i=1;}
    virtual int get_i() {return i;}
};
class B: public A
{
    int j;
    public: B() {j=2;}
    int get_i() { return A::get_i()+j;}
};
int main()
{
    const int i=cin.get();
    if(i%3) {A o;}
    else {B o;}
    cout<<o.get_i();
    return 0;
}
