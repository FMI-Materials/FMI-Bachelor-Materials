#include <iostream>
// for vector
#include <vector> //https://www.geeksforgeeks.org/vector-in-cpp-stl/

// for list
#include <list>     //https://www.geeksforgeeks.org/list-cpp-stl/
#include <iterator>

using namespace std;
// interfata
class Taxe{
public:
    virtual float Impozit()=0;
    virtual int ani()=0;

};
// clasa abstracta
class Produs{
protected:
 string nume;
 float pretBrut;
 public:
     void afisareBrand(){

     cout<<"Acest produs apartine EDI>.RL";

     }
  virtual  float calculeazaPret()=0;

   friend ostream& operator<<(ostream& out,const Produs& p){

    out<<p.nume<<" ";
    out<<p.pretBrut;
    return out;


   }
    friend istream& operator >>(istream& in, Produs&p){

        cout<<"Numele este: ";
        in>>p.nume;
        cout<<"Pretul brut este: ";
        in>>p.pretBrut;
        return in;

    }


};

class ProdusPersibail:public Produs{
    string dataExpirare;
public:

       float calculeazaPret(){

        return pretBrut+(40*pretBrut)/100;

    }

    friend ostream& operator<<(ostream& out,const ProdusPersibail& p)
    {
        out<<(Produs&)p;
        out<<" "<<p.dataExpirare;
      return out;

    }
    friend istream& operator >>(istream& in, ProdusPersibail&p){

    in>>(Produs&)p;
    cout<<"Dati data: ";
    in>>p.dataExpirare;
    return in;}


};

class ProdusNePerisbalil:public Produs{
    int garantie;
public:
    void alabalaPortocala(){
        cout<<"ceva";
    }
    float calculeazaPret(){

        return pretBrut+(10*pretBrut)/100;

    }


    friend ostream& operator<<(ostream& out,const ProdusNePerisbalil& p)
    {
        out<<(Produs&)p;
        out<<" "<<p.garantie;
      return out;

    }
    friend istream& operator >>(istream& in, ProdusNePerisbalil&p){

    in>>(Produs&)p;
    cout<<"ani garantie: ";
    in>>p.garantie;
    return in;}






};

int main()
{

    vector <Produs*> listaProduse;
  /*  vector <int> vectorDeInt;
    vector <ProdusNePerisbalil> vectorProduseNePerisabile1;
    vector <ProdusNePerisbalil> vectorProduseNePerisabile2;
    vectorProduseNePerisabile1=vectorProduseNePerisabile2;
*/

    ProdusPersibail pp;
    ProdusNePerisbalil pn;
    cin>>pp>>pn;

    listaProduse.push_back(&pp);
    listaProduse.push_back(&pn);

    vector <Produs*> listaProduse2;

    listaProduse2=listaProduse;
    for(auto ir=listaProduse2.begin(); ir!=listaProduse2.end(); ir++)
        cout<<(*(*ir));

    for(Produs*n : listaProduse)
        cout<<*n;//c++11

    cout<<endl<<"----------------------------\n";
    cout<<*listaProduse2[0];

    list <Produs*> listaProduse3;

    listaProduse3.push_back(&pp);
    listaProduse3.push_front(&pn);

    list <Produs*>::iterator it;

    for(it=listaProduse3.begin(); it!=listaProduse3.end(); it++)
        cout<<"\t"<<(*it)->calculeazaPret();


    return 0;
}





#include <iostream>

using namespace std;
class Singletone{
private:
    static Singletone *obiect;
    string data;

    Singletone(){
        data="dd/mm/yyyy";
    }
public:
    static Singletone* getInstance(){
        if(!obiect)
            obiect=new Singletone();


        return obiect;
    }

    string getData(){return this->data;}
    void setData(string a) {this->data=a;}

};
Singletone* Singletone::obiect=0;
int main()
{
    Singletone *s=s->getInstance();
    cout<<s->getData();
    s->setData("19.04.2021");
    cout<<endl;
    cout<<s->getData();
    cout<<endl;
    Singletone *s2=s2->getInstance();
    cout<<s->getData();


    return 0;
}

