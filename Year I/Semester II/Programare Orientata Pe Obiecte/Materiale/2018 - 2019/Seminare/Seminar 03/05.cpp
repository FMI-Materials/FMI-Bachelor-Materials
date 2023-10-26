#include <cstdlib>
#include <iostream>
using namespace std;
// exemplu pentru compunere

class Complex
{
      float re,im;
public:
     Complex operator+(Complex p2);
friend istream& operator >> (istream & is, Complex & op);
friend ostream& operator <<(ostream & os, Complex  op);
};

class MatriceC
{ Complex m[10][10];
  int l,c;
public : MatriceC operator +(MatriceC p);
friend istream& operator >> (istream & is, MatriceC & op);
friend ostream& operator <<(ostream & os, MatriceC  op);
};

Complex Complex :: operator + (Complex p2)
{Complex ot;
 ot.re=re+p2.re;
 ot.im=im+p2.im;
 return ot;
}
 istream& operator >> (istream & is, Complex & op)
 { is>>op.re>>op.im;
  return is;
  }
  ostream& operator <<(ostream & os, Complex  op)
{ os<<op.re<<op.im;
 return os;
}
istream& operator >> (istream & is, MatriceC& op)
{ is>>op.l>>op.c;
  for(int i=0;i<op.l;i++)
  for(int j=0;j<op.c;j++)
   is>>op.m[i][j];
   return is;
}

ostream& operator <<(ostream & os, MatriceC op)
{for(int i=0;i<op.l;i++)
  for(int j=0;j<op.c;j++)
   os<<op.m[i][j];
   return os;
}

 MatriceC MatriceC:: operator + (MatriceC p2)
{  if ((p2.l!= l)||(p2.c!=c) )return *this;
    MatriceC ot;
    ot.l=l; ot.c=c;
    for(int i=0;i<l;i++)
    for(int j=0;j<c;j++)
     ot.m[i][j]=m[i][j]+p2.m[i][j];
   return ot;
 }

int main()
{ MatriceC A,B;
   cin>>A>>B;
   cout<<A+B;
  system("PAUSE");
   return 0;
}
