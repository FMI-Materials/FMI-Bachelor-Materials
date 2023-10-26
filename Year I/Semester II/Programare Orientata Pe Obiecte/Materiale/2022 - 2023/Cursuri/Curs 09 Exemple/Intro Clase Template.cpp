#include <iostream>

using namespace std;

template<class T> class Test;

template<class T>
ostream& operator<<(ostream& out, const Test<T>& ob)
{out<<ob.x; return out;}

template<class T>
class Test
{
    T x;
public:
    void citire();
    void afisare(){cout<<x;}
    friend ostream& operator<< <>(ostream&, const Test<T>&);
};

template<class T>
void Test<T>::citire(){cin>>x;}


/*
template<class T>
class Test
{
    T x;
public:
    void citire();
    void afisare(){cout<<x;}
    template<class T1> friend ostream& operator<<(ostream&, const Test<T1>&);
};

template<class T>
void Test<T>::citire(){cin>>x;}

template<class T>
ostream& operator<<(ostream& out, const Test<T>& ob)
{out<<ob.x; return out;}
*/

int main()
{
    Test<int> ob;
    ob.citire();
    cout<<ob;

///    ob.afisare();
///    Test<float> ob2;
///    ob2.citire();
    return 0;
}
