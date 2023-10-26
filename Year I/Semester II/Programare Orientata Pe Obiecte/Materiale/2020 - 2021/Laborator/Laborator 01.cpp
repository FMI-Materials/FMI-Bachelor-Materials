#include <iostream>

using namespace std;
void add3(int& v){

    v=v+3;
    cout<<"\nV-ul din fiunctie: "<<v<<endl;

}


class forma{
protected:
    int h;
public:
   virtual void citesteForma()=0;
   virtual float cantitateFrisaca()=0;
   virtual float cantitateGem()=0;

};
class cerc:public forma{
private:
    int r;
public:
    void citesteForma(){

        cout<<"Inaltime ";cin>>this->h;
        cout<<"Raza ";cin>>this->r;

    }
    float cantitateFrisaca(){

    return (3.14*this->r*this->r)+(2*3.14*this->r*this->h);

    }

    float cantitateGem(){

        return (3.14*this->r*this->r)*this->h;


    }

};

class dreptunghi: public forma{
private:
    int lungime;
    int latime;
public:

    void citesteForma(){

        cout<<"Inaltime ";cin>>this->h;
        cout<<"Lungime ";cin>>this->lungime;
        cout<<"Latime ";cin>>this->latime;


    }
    float cantitateFrisaca(){

    return this->latime*this->lungime+2*(this->latime*h+this->lungime*h);

    }

    float cantitateGem(){

        return (this->latime*this->lungime)*this->h;


    }


};

int main()
{

    /*int v;
    v=3;
    add3(v);
    cout<<"\n V-ul din main() "<<v<<endl;
    */

  /*  int* a;
    int i=5;

    a=&i;
    *a=10;

    cout<<"Adresa a "<<&a;   //ff2
    cout<<"\nAdresa i "<<&i; //ff4
    cout<< "\nLa adresa lui a "<<a; //ff4
    cout<< "\nValoarea de la adresa lui a "<<*a;//10
    cout<< "\nValoarea  lui i  "<<i;//10*/

   /* int* a=NULL;
    a=new int;
    *a=3;
     cout<<"Adresa a "<<&a;
     cout<< "\nLa adresa lui a "<<a;
     cout<< "\nValoarea de la adresa lui a "<<*a;
*/
   /* int* a=NULL;
    int n;
    cout<<"n= "; cin>>n;
    a=new int[n];

    for(int i=0; i<n;i++)
        cin>>a[i];

    for(int i=0; i<n;i++)
        cout<<*(a+i)<<" ";

    delete[] a;

*/


    forma* p[10];
    int i=0;

   int k=1;
   while(k==1){

    cout<<"\nApasa 1 pentru a adauga un cerc\n";
    cout<<"\nApasa 2 pentru a adauga un dreptunghi\n";
    cout<<"\nApasa 3 pentru cantitatea totala de gem\n";
    cout<<"\nApasa 4 pentru cantitatea toatala de frisca\n";
    cout<<"\nApasa 10 pentru....STOP\n";

    int comanda;
    cin>>comanda;

    switch(comanda){

    case 1:{
        p[i]=new cerc;
        p[i]->citesteForma();
        i++;
        break;
    }
    case 2:
        p[i]=new dreptunghi;
        p[i]->citesteForma();
        i++;
        break;
    case 3:{
        float cantTot=0;
        for(int j=0; j<i;j++)
            cantTot=cantTot+ p[j]->cantitateGem();
        cout<< cantTot;
    break;}
     case 4:{
        float cantTot1=0;
        for(int j=0; j<i;j++)
            cantTot1=cantTot1+ p[j]->cantitateFrisaca();
        cout<< cantTot1;
    break;
     }
     case 10:
        k=0;
        break;
    default:{

        cout<<"\n\t\t COMADNA INCORECTA\t\t\n";
        break;

    }


    }



   }



    return 0;
}
