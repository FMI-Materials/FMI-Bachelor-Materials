#include<iostream>
using namespace std;
class cls
{
    int x;
public:
        cls(int i=0) {cout<<" c1 "; x=i;}
        ~cls() {cout<<" d 1 ";}
};
class cls1
{
    int x; cls xx;
public:
        cls1(int i=0){cout<<" c2 ";x=i;}
        ~cls1(){cout<<" d2 ";}
}c;
class cls2
{
    int x;cls1 xx;cls xxx;
public:
    cls2(int i=0) {cout<<" c3 ";x=i;}
    ~cls2(){ cout<<" d3 ";}
};
int main()
{
    cls2 s;
    return 0;
}
//c1 c2 c1 c2 c1 c3 d3 d1 d2 d1 d2 d1
