#include <iostream>
using namespace std;

class taxe
{
public:
    void afisareLogo(){cout<<"Edi.srl";}
    virtual void calculeazaTaxe()=0;


};
class Produs : public taxe
{
protected:
    string nume;
    float pretBrut;
public:
    string getNume(){return nume;}
    friend istream & operator >>(istream & in, Produs & P);
    friend ostream & operator <<(ostream & out, const Produs & P);
    Produs();
    Produs(string name, float price);
    Produs(const Produs & P);
    Produs & operator =(const Produs & P);
    virtual float calculeazaPret()=0;
    ~Produs();
};
istream & operator >>(istream & in, Produs & P)
{
    cout << "Introduceti numele:";
    in >> P.nume;
    cout << "\n" << "Introduceti pretul brut:";
    in >> P.pretBrut;
    cout << "\n";
    return in;
}
ostream & operator <<(ostream & out, const Produs & P)
{
    out << "Numele produsului este " << P.nume << "\n";
    out << "Pretul brut al produsului este " << P.pretBrut << "\n";
    return out;
}
Produs & Produs :: operator =(const Produs & P)
{
    if(this != &P)
    {
        this -> nume = P.nume;
        this -> pretBrut = P.pretBrut;
    }
    return *this;
}
Produs :: Produs()
{
    this -> nume = "anonim";
    this -> pretBrut = 0;
}
Produs :: Produs(string name, float price)
{
    this -> nume = name;
    this -> pretBrut = price;
}
Produs :: Produs(const Produs & P)
{
    this -> nume = P.nume;
    this -> pretBrut = P.pretBrut;
}
Produs :: ~Produs()
{
    this -> nume = "anonim";
    this -> pretBrut = 0;
}
class ProdusPerisabil : public Produs
{
private:
    string dataExp;
public:
    friend istream & operator >>(istream & in, ProdusPerisabil & Prod);
    friend ostream & operator <<(ostream & out, const ProdusPerisabil & Prod);
    ProdusPerisabil();
    ProdusPerisabil(string name, float price, int date_exp);
    ProdusPerisabil(const ProdusPerisabil & ProdPer);
    ProdusPerisabil & operator =(const ProdusPerisabil & Prod);
    void afisareLogo(){cout<<"ProdusPErisabil";}
    void afisareLogo(int){cout<<" Supraincarcare ProdusPErisabil";}
    float calculeazaPret()
    {
        return this -> pretBrut * 25/100 + this -> pretBrut;
    }
    void calculeazaTaxe()
    {
        cout<<"\nTva-ul este "<<this->pretBrut*25/100;
    }
    ~ProdusPerisabil();
};
istream & operator >>(istream & in, ProdusPerisabil & Prod)
{
    in >> (Produs&)Prod;
    cout << "Introduceti data expirarii:";
    in >> Prod.dataExp;
    return in;
}
ostream & operator <<(ostream & out, const ProdusPerisabil & Prod)
{
    out << (Produs&)Prod;
    out << "Data expirarii este: " << Prod.dataExp << "\n";
    return out;
}
ProdusPerisabil :: ProdusPerisabil() : Produs()
{
    this -> dataExp = "DD/MM/YYYY";
}
ProdusPerisabil :: ProdusPerisabil(string name, float price, int date_exp) : Produs(name, price)
{
    this -> dataExp = date_exp;
}
ProdusPerisabil :: ProdusPerisabil(const ProdusPerisabil & ProdPer) : Produs(ProdPer)
{
    this -> dataExp = ProdPer.dataExp;
}
ProdusPerisabil &  ProdusPerisabil :: operator =(const ProdusPerisabil & Prod)
{
    if(this != &Prod)
    {
        Produs :: operator =(Prod);
        this -> dataExp = Prod.dataExp;
    }
    return *this;
}
ProdusPerisabil :: ~ProdusPerisabil()
{
    this -> dataExp = "0";
}
class ProdusNeperisabil : public Produs
{
private:
int aniGarantie;
public:
    friend istream & operator >>(istream & in, ProdusNeperisabil & Prod);
    friend ostream & operator <<(ostream & out, const ProdusNeperisabil & Prod);
    ProdusNeperisabil();
    ProdusNeperisabil(string name, float price, int date_exp);
    ProdusNeperisabil(const ProdusNeperisabil & ProdPer);
    ProdusNeperisabil & operator =(const ProdusNeperisabil & Prod);
    void afisareLogo(){cout<<"ProdusNeperisabil";}
    float calculeazaPret(){

        return this->pretBrut*10/100+this->pretBrut;

    }
    void calculeazaTaxe(){

        cout<<"\nTva-ul este "<<this->pretBrut*10/100;

    }
    ~ProdusNeperisabil();
};
istream & operator >>(istream & in, ProdusNeperisabil & Prod)
{
    in >> (Produs&)Prod;
    cout << "Introduceti cati ani e garantata:";
    in >> Prod.aniGarantie;
    return in;
}
ostream & operator <<(ostream & out, const ProdusNeperisabil & Prod)
{
    out << (Produs&)Prod;
    out << "Anii garantati sunt in numar de: " << Prod.aniGarantie << "\n";
    return out;
}
ProdusNeperisabil :: ProdusNeperisabil() : Produs()
{
    this -> aniGarantie = 0;
}
ProdusNeperisabil :: ProdusNeperisabil(string name, float price, int date_exp) : Produs(name, price)
{
    this -> aniGarantie = date_exp;
}
ProdusNeperisabil :: ProdusNeperisabil(const ProdusNeperisabil & ProdPer) : Produs(ProdPer)
{
    this -> aniGarantie = ProdPer.aniGarantie;
}
ProdusNeperisabil &  ProdusNeperisabil :: operator =(const ProdusNeperisabil & Prod)
{
    if(this != &Prod)
    {
        Produs :: operator =(Prod);
        this -> aniGarantie = Prod.aniGarantie;
    }
    return *this;
}
ProdusNeperisabil :: ~ProdusNeperisabil()
{
    this -> aniGarantie = 0;
}
int main()
{/*
    ProdusPerisabil A;
    ProdusNeperisabil B;
    cin >> A;
    cin >> B;
    cout << A;
    cout << B;
    Produs* lista[10];
    lista[1]=new ProdusPerisabil;
    lista[2]=new ProdusNeperisabil;


    cout<<endl;

    A.afisareLogo();
    cout<<endl;
    B.afisareLogo();

    cout<<endl;

    lista[1]->afisareLogo();
    cout<<endl;
    lista[2]->afisareLogo();

    cin>>*(lista[1]);
    cout<<*(lista[1]);
    cin>>*(lista[2]);
    cout<<*(lista[2]);

    */

    Produs *listaProduse[100];

    int k=1;
    int i=0;
    while(k==1){

        cout<<"\n1 Perisabil ";
        cout<<"\n2 Neperisabil ";
        cout<<"\n3 Stop ";
        cout<<"\n4 Afiseaza pret ";
        cout<<"\n5 Afisare Produse\n";

        int comanda;
        cin>> comanda;


        switch(comanda){

            case 1:{

                listaProduse[i]=new ProdusPerisabil();
                cin>>static_cast<ProdusPerisabil&>(*(listaProduse[i]));
                i++;
                break;


            }
            case 2:{

                listaProduse[i]=new ProdusNeperisabil();
                cin>>static_cast<ProdusNeperisabil&>(*(listaProduse[i]));
                i++;
                break;


            }
            case 3:{


                k=0;
                break;


            }

            case 4:{

            for(int j=0; j<i;j++)
                cout<<listaProduse[j]->getNume()<<" are pretul "<<listaProduse[j]->calculeazaPret()<<endl;
                break;


            }
            case 5:{
               for(int j=0; j<i;j++)
               {if(typeid(*(listaProduse[j]))==typeid(ProdusPerisabil))
                    cout<<static_cast<ProdusPerisabil&>(*(listaProduse[j]))<<endl;
                else
                   cout<< static_cast<ProdusNeperisabil&>(*(listaProduse[j]))<<endl;

               }
            }








        }


    }



    return 0;
}
