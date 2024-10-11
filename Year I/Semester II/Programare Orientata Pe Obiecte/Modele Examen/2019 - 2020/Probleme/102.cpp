#include<iostream>
using namespace std;
template<class X>
int functie(X x, X y)
{ return x+y;
}
int functie(int & x, int *y)
{ return x-*y;
}
int main()
{ int a=7, *b=new int(4);
  cout<<functie(a,b);
  return 0;
}
