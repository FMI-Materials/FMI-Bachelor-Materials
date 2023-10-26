#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;



int main()
{
const int ic=1;
int i=1, j=1;

int *pi;
const int *cp; // pointer spre o zona considerata constanta
int * const pc=&i; //pointer constant

 cp=&i;
 i=2;   // pot modifica zona
//*cp=2; // nu pot modifica zona prin pointer

//pi=&ic;// nu - pot modifica constanta prin pointer
cp=&ic; // pot - nu pot modifica const prin pointer
//pi=cp; nu -pot modifica zona prin pi prin intermediul lui cp

 *pc=2; // pot modifica zona adresata
//pc=&j; //nu pot modifica pointerul


int & ri=i;
const int &cri=i;// referinta spre o zona considerata constanta- referinta e prin definitie constanta
//int  & const rc=i; // nu  -referinta e prin definitie constanta

 i=2;// pot modifica zona
// cri=2; // nu pot modifica zona prin ri
//int &ri1=&ic;// nu - pot modifica constanta prin referinta ri1



}

