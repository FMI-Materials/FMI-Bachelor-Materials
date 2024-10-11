#include<iostream>
using namespace std;
class A
{
    int valoare;
    public: A(int param1=3):valoare(param1){}
    int getValoare(){return this->valoare;}
};
int main()
{
    A vector[]={*(new A(3)),*(new A(4)),*(new A(5)),*(new A(6)) };
    cout<<vector[2].getValoare();
    return 0;
}
