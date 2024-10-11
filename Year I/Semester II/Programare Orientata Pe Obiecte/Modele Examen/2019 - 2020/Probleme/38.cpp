#include<iostream>
using namespace std;
template<class X, class Y>
X f(X x, Y y)
{
    //aici o sa ajunga niste pointer si nu-i poti aduna!!!
    return x+y;
}
int *f(int *x,int y)
{
    return x-y;
}
int main()
{
    int *a=new int(200), *b=a;
    //cout<<a+b<<"\n"; nu poti aduna pointeri
    cout<<*f(a,b);
    return 0;
}
