#include<iostream>
using namespace std;
class cls
{
    int x;
public: cls(int i=3) {x=i;}
    int &f() const{ return x;}
};
int main()
{
    const cls a(-3);
    int b=a.f();
    cout<<b;
    return 0;
}
