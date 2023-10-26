#include <iostream>
#include <typeinfo>
using namespace std;
class animal{
public:
    virtual void vorbeste(){};

};

class caine:public animal{
public:
    void vorbeste(){

        cout<<"ham ham";
    }

};
class pisica:public animal{
public:
    void vorbeste(){

        cout<<"miau miau";
    }

};
class gaina:public animal{
public:
    void vorbeste(){

        cout<<"piu piu";
    }

};

class lup:public caine{
public:
    int ani=20;
    void vorbeste(){

        cout<<"Auuu";
    }

    void mananca(){

        cout<<"carne";

    }
};

int main()
{
    //upcasting copil->parinte

    animal *a=new caine;
    // a->vorbeste();

    caine c1;
    pisica p1;
    gaina g1;
    lup l1;

    animal* a2=&c1; // upcasting implicit

    animal* a3=static_cast<caine*> (&c1);// upcasting explicit

    a3->vorbeste();
    cout<<endl;
    animal* *list_animal=new animal*[4];// animal *lista_animal[4];
    list_animal[0]=&c1;
    list_animal[1]=&p1;
    list_animal[2]=&g1;
    list_animal[3]=&l1;
    for(int i=0; i<4;i++)
    {list_animal[i]->vorbeste();
        cout<<endl;
    }



    cout<<"\n----------------\n";
    caine* c2=new lup;
    lup *lup2;



   lup2=dynamic_cast<lup*> (c2);

   cout<<c2<<endl;
   cout<<lup2<<endl;
   cout<<lup2->ani<<endl;
   lup2->mananca();
   cout<<"\n--------------\n";
   cout<<typeid(*c2).name();

   cout<<"\n--------------\n";
   for(int i=0;i<4;i++)
   {
       if(typeid(*list_animal[i])==typeid(lup))
       {
            lup *lup1;
            lup1=static_cast<lup*> (list_animal[i]);
            lup1->vorbeste();
            lup1->mananca();
       }
       cout<<endl;
       cout<<typeid(*list_animal[i]).name()<<endl;


   }
    return 0;
}
