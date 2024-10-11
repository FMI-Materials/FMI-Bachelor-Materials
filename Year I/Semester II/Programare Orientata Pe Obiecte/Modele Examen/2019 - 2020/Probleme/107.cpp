include <iostream>
using namespace std;
class A
{   protected: int x;
    public: A(int i):x(i){}
            int get_x(){ return x; } };
class B: A
{   protected: int y;
    public: B(int i,int j):y(i),A(j){}
            int get_y(){ return get_x()+y; } };
class C: protected B
{   protected: int z;
    public: C(int i,int j,int k):z(i),B(j,k){}
            int get_z(){ return get_x()+get_y()+z; } };
int main()
{   C c(5,6,7);
    cout<<c.get_z();
    return 0;
}
