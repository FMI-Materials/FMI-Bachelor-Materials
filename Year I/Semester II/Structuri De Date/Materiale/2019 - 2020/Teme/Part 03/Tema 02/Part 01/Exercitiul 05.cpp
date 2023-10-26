#include <iostream>
#include<fstream>
using namespace std;
// numarul de incrementari este mai mare decat numarul de decrementari pt ca elem maj apare de cel putin n/2 +1 ori

int main()
{
    ifstream f("p5.txt");
    int n ,v[100],i, x=-1,nr=0;
    f>>n;
    for(i=0;i<n;i++)
    {
        f>>v[i];

        if(x!=v[i])
        {
            if(!nr)//daca e 0 schimb elemnetul ca nu e bun
               {
                x=v[i];
                nr=1;
               }
            else
                nr--;//daca nu e egal clar decrementez
        }
        else nr++;//element egal cu elementul ales
    }

    nr=0;
    //necesita verficare pentru ca e posibil sa fi gasit alt numar care nu e majoritar
    for(i=0;i<n;i++)
        if(v[i]==x)
            nr++;

    if(nr>n/2)
        cout<<"elementul majoritar este: "<<x<<" si apare de "<<nr<<" ori in v";
    else
        cout << "nu exista element majoritar";

    return 0;
}
