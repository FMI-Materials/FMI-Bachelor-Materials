#include <iostream>

using namespace std;
//interfata
class taxe{
public:
    void afisareLogo(){cout<<"EDI.SRL";}
    virtual void calculeazaTaxe()=0;

};
class Produs:public taxe{
protected:
    string nume;
    float pretBrut;
public:
    Produs();
    Produs(string nume,float pretBrut);
    Produs& operator=(const Produs& prod);
    Produs(const Produs& prod);
    virtual float calculeazaPretCuTV()=0;

    virtual ostream& AfisareVirtuala(ostream& out) const;
    virtual istream& CitireVirtuala (istream& in);

    friend istream& operator>>(istream & in,Produs& pr);
    friend ostream& operator<<(ostream & out,const Produs& pr);
    
    string getNume(){return this->nume;}

};

ostream& Produs::AfisareVirtuala(ostream& out) const {

    out<<"\nNumele produsului este: "<<this->nume;
    out<<"\nPretul brut este: "<<this->pretBrut;
    return out;


}
istream& Produs::CitireVirtuala(istream& in){

    cout<<"\nNumele produsului este: ";
    in>>this->nume;
    cout<<"\nPretul brut este: ";
    in>>this->pretBrut;
    return in;


}

istream& operator>>(istream & in,Produs& pr)
{
    return pr.CitireVirtuala(in);
}
 ostream& operator<<(ostream & out,const Produs& pr)
{
    return pr.AfisareVirtuala(out);
}
Produs::Produs()
{
    this->nume="Necunoscut";
    this->pretBrut=0.0;
}
Produs::Produs(string nume,float pretBrut)
{
    this->nume=nume;
    this->pretBrut=pretBrut;
}
Produs& Produs::operator=(const Produs& prod)
{
    if(this!=&prod)
    {
        this->nume=prod.nume;
        this->pretBrut=prod.pretBrut;
    }

    return *this;
}
Produs::Produs(const Produs& prod)
{
    this->nume=prod.nume;
    this->pretBrut=prod.pretBrut;
}
class ProdusPerisabil:public Produs{
private:
    string dataExp;
public:
    ProdusPerisabil();
    ProdusPerisabil(string nume,float pretBrut, string dataExp);
    ProdusPerisabil(const ProdusPerisabil& perisab);
    ProdusPerisabil&operator =(const ProdusPerisabil& perisab);

    virtual ostream& AfisareVirtuala(ostream& out) const;
    virtual istream& CitireVirtuala (istream& in);


    void afisareLogo(){cout<<"\nProdusPersiabbil\n";}
    virtual float calculeazaPretCuTV(){

        return this->pretBrut*25/100+this->pretBrut;

    }
    void calculeazaTaxe(){
        cout<<"TVA-ul este: "<< this->pretBrut*25/100;

    }
};

ostream& ProdusPerisabil::AfisareVirtuala(ostream& out) const {

        Produs::AfisareVirtuala(out);
        out<<"\nData expirare: "<<this->dataExp;
        return out;



}
istream& ProdusPerisabil::CitireVirtuala(istream& in){

    Produs::CitireVirtuala(in);
    cout<<"\nData expirare: ";
    in>>this->dataExp;
    return in;

}
ProdusPerisabil::ProdusPerisabil():Produs()
{
    this->dataExp="DD/MM/YYYY";
}
ProdusPerisabil::ProdusPerisabil(string nume,float pretBrut, string dataExp):Produs(nume,pretBrut)
{
    this->dataExp=dataExp;
}
ProdusPerisabil::ProdusPerisabil(const ProdusPerisabil& perisab):Produs(perisab)
{
    this->dataExp=perisab.dataExp;

}
ProdusPerisabil&ProdusPerisabil:: operator =(const ProdusPerisabil& perisab)
{
    if(this!=&perisab)
    {
        Produs::operator=(perisab);
        this->dataExp=perisab.dataExp;

    }
    return *this;
}


class ProdusNeperisabil:public Produs{
private:
    int aniGarantie;
public:
    ProdusNeperisabil();
    ProdusNeperisabil(string nume,float pretBrut, int aniGarantie);
    ProdusNeperisabil(const ProdusNeperisabil& neperisab);
    ProdusNeperisabil&operator =(const ProdusNeperisabil& neperisab);

    virtual ostream& AfisareVirtuala(ostream& out) const;
    virtual istream& CitireVirtuala (istream& in);


    void afisareLogo(){cout<<"\nProdusNepersiabbil\n";}
    virtual float calculeazaPretCuTV(){

        return this->pretBrut*10/100+this->pretBrut;


    }
    void calculeazaTaxe(){
        cout<<"TVA-ul este: "<< this->pretBrut*10/100;

    }
};

ostream& ProdusNeperisabil::AfisareVirtuala(ostream& out) const {

        Produs::AfisareVirtuala(out);
        out<<"\nAni garantie: "<<this->aniGarantie;
        return out;


}
istream& ProdusNeperisabil::CitireVirtuala(istream& in){

    Produs::CitireVirtuala(in);
    cout<<"\nAni garantie: ";
    in>>this->aniGarantie;
    return in;

}

ProdusNeperisabil::ProdusNeperisabil():Produs()
{
    this->aniGarantie=0;
}
ProdusNeperisabil::ProdusNeperisabil(string nume,float pretBrut, int aniGarantie):Produs(nume,pretBrut)
{
    this->aniGarantie=aniGarantie;
}
ProdusNeperisabil::ProdusNeperisabil(const ProdusNeperisabil& neperisab):Produs(neperisab)
{
    this->aniGarantie=neperisab.aniGarantie;

}
ProdusNeperisabil& ProdusNeperisabil::operator =(const ProdusNeperisabil& neperisab)
{
    if(this!=&neperisab)
    {
        Produs::operator=(neperisab);
        this->aniGarantie=neperisab.aniGarantie;

    }
    return *this;
}



int main()
{

    Produs *produse[10];
    produse[0]=new ProdusNeperisabil();
    produse[1]=new ProdusPerisabil();


    ProdusNeperisabil a;
    ProdusPerisabil b;

    cin>>b;
    cin>>a;

    cout<<a;
    cout<<b;
    //citesc si afisez produse Neperisabile
  /*  cin>>a;
    cout<<a;
    cin>>*produse[0];
    cout<<*produse[0];

    //citesc si afisez produse Perisabile
    cin>>b;
    cout<<b;
    cin>>*produse[1];
    cout<<*produse[1];
    cout<<endl;

*/

    b.afisareLogo();
    cout<<endl;
    a.afisareLogo();
    cout<<endl;
    produse[0]->afisareLogo();
    cout<<endl;
    produse[1]->afisareLogo();
    cout<<endl;


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
                cin>>*listaProduse[i];
                i++;
                break;


            }
            case 2:{

                listaProduse[i]=new ProdusNeperisabil();
                 cin>>*listaProduse[i];
                i++;
                break;


            }
            case 3:{


                k=0;
                break;


            }

            case 4:{

            for(int j=0; j<i;j++)
                cout<<listaProduse[j]->getNume()<<" are pretul "<<listaProduse[j]->calculeazaPretCuTV()<<endl;
                break;


            }
            case 5:{
               for(int j=0; j<i;j++)
                    cout<<*listaProduse[j];
            }








        }


    }

    return 0;
}
