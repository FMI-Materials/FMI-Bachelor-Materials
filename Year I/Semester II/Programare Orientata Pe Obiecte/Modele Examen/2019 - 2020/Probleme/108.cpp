#include <iostream>
using namespace std;
class cls
{	int x;
public: cls(int i=2) { x=i; }
int set_x(int i) { int y=x; x=i; return y; }
int get_x(){ return x; } };
int main()
{ cls *p=new cls[15];
      for(int i=2;i<8;i++) p[i].set_x(i);
	  for(int i=1;i<6;i++) cout<<p[i].get_x();
  return 0;
}
