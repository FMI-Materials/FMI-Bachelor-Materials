#include <iostream>
using namespace std;
class X {   int i;
public:   X(int ii = 5) { i = ii; cout<< i<< " ";};
          const int tipareste(int j) const { cout<<i<< " "; return i+j; }; };
int main()
{ X O (7);
  O.tipareste(5);
  X &O2=O;
  O2.tipareste(6);
  const X* p=&O;
  cout<<p->tipareste(7);
  return 0;
}
