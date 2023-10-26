/*Dima Oana-Teodora 141
GNU GCC Compiler
Gusatu Marian*/
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<cmath>
using namespace std;
class masca
{
protected:
    string protectie;
    string culoare;
    int pliuri;
    string logo;
    int tip;//1-daca e chirurgicala 2-policarbonat
    double pret;//in functie de protectie
public:
    masca() {}
    masca(const masca &ob)
    {
        protectie=ob.protectie;
        culoare=ob.culoare;
        pliuri=ob.pliuri;
        logo=ob.logo;
        pret=ob.pret;
    }

    virtual ~masca() {}
   masca & operator =(const masca &ob)
    {
        protectie=ob.protectie;
        culoare=ob.culoare;
        pliuri=ob.pliuri;
        logo=ob.logo;
        pret=ob.pret;
        return *this;
    }

    double getPret() const {
        return pret;
    }

    virtual void citesc(istream &os);
    virtual void afisez(ostream &os);

    friend ostream& operator <<(ostream &os, masca &ob);
    friend istream& operator >>(istream &os, masca &ob);


};
void masca:: citesc(istream &os)
{
    if(tip==1)//masca chirurgicala
    {
        cout << "protectie(ffp1/ffp2/ffp3): ";
        getline(os, protectie);
    }
    cout<<"culoare: ";
    getline(os, culoare);
    cout<<"nr pliuri: ";
    os>>pliuri;
    string rasp;
    if(tip==1) //logo-ul este pt masca chirurgicala
    {
        cout << "doriti si logo?(da/nu): ";
        os.get();
        getline(os, rasp);
        if (rasp == "da") {
                cout<<"logo:";
            getline(os, logo);
        } else
            logo = "nu";
    }
    //calcul pret
    if(protectie=="ffp1")
        pret=5;
    else
    if(protectie=="ffp2")
        pret=10;
    else
    if(protectie=="ffp3")
        pret=15;
}
void masca:: afisez(ostream &os)
{

    os<<"protectie: ";
    os<<protectie;
    os<<endl;
    os<<"culoare: ";
    os<<culoare;
    os<<endl;
    cout<<"nr pliuri: ";
    os<<pliuri;
    os<<endl;
    if(tip==1) {
        os << "logo: ";
        os << logo;
        os << endl;
    }
    os<<"pret: ";
    os<<pret<<" lei";
    os<<endl;
}
ostream& operator << (ostream& os, masca& ob)
{
    ob.afisez(os);
    return os;
}
istream& operator >>(istream& os, masca& ob)
{
    ob.citesc(os);
    return os;
}
class chirurgicala:public masca
{


public:
    chirurgicala() {}
    chirurgicala(const chirurgicala &ob)
    {
        protectie=ob.protectie;
        culoare=ob.culoare;
        pliuri=ob.pliuri;
        logo=ob.logo;
        pret=ob.pret;
    }

    virtual ~chirurgicala() {}
    chirurgicala& operator =(const chirurgicala &ob)
    {
        protectie=ob.protectie;
        culoare=ob.culoare;
        pliuri=ob.pliuri;
        logo=ob.logo;
        pret=ob.pret;
        return *this;
    }

    double getPret() const;
    string get_logo() const
    {
        return logo;
    }

    virtual void citesc(istream &os);
    virtual void afisez(ostream &os);

    friend ostream& operator <<(ostream &os, chirurgicala &ob);
    friend istream& operator >>(istream &os, chirurgicala &ob);


};
 void chirurgicala:: citesc(istream &os)
 {
    cout<<"------masca chirurgicala\n";
    tip=1;
    masca:: citesc(os);
 }
 void chirurgicala:: afisez(ostream &os)
 {
     os<<"------masca chirurgicala\n";
     masca:: afisez(os);
 }
ostream& operator << (ostream& os, chirurgicala& ob)
{
    ob.afisez(os);
    return os;
}
istream& operator >>(istream& os, chirurgicala& ob)
{
    ob.citesc(os);
    return os;
}

double chirurgicala::getPret() const {
    return pret;
}
class policarbonat: public masca
{
    string prindere;
public:
    policarbonat() {}
    policarbonat(const policarbonat &ob)
    {
        protectie=ob.protectie;
        culoare=ob.culoare;
        pliuri=ob.pliuri;
        logo=ob.logo;
        pret=ob.pret;
        prindere=ob.prindere;
    }

    ~policarbonat() {}

    policarbonat & operator =(const policarbonat &ob){
        protectie = ob.protectie;
        culoare = ob.culoare;
        pliuri = ob.pliuri;
        logo = ob.logo;
        pret = ob.pret;
        prindere = ob.prindere;
        return *this;
    }
    void citesc(istream &os);
    void afisez(ostream &os);
};
void policarbonat:: citesc(istream &os)
{
    cout<<"-------masca policarbonat: \n";
    tip=2;
    masca::citesc(os);
    protectie="ffp0";
    pret=20;
    os.get();
    cout<<"prindere: ";
    getline(os,prindere);
}
void policarbonat::afisez(ostream &os)
{
    os<<"-------masca policarbonat: \n";
    masca::afisez(os);
    os<<"prindere: ";
    os<<prindere<<endl;

}
class dezinfectanti
{
protected:

    int specii;
    string ingrediente;
    string suprafata;
public:
    dezinfectanti(){}

    dezinfectanti(const dezinfectanti & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
    }
    virtual ~dezinfectanti(){}

    dezinfectanti & operator =(const dezinfectanti & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
        return *this;
    }
  void reteta(string nou)
    {
        ingrediente=nou;
    }
    virtual void citesc(istream &os)=0;
    virtual void afisez(ostream &os)=0;

    friend ostream& operator <<(ostream &os, dezinfectanti &ob);
    friend istream& operator >>(istream &os, dezinfectanti &ob);
};
ostream& operator << (ostream& os, dezinfectanti& ob)
{
    ob.afisez(os);
    return os;
}
istream& operator >>(istream& os, dezinfectanti& ob)
{
    ob.citesc(os);
    return os;
}
class bacterii: public dezinfectanti
{
private:
    const long double total=10000000000;
    double eficienta;//calculata automat
    double pret;//calculat automat


public:
    bacterii(){}

    bacterii(const bacterii & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
        eficienta=ob.eficienta;
        pret=ob.pret;
    }
    ~bacterii(){}

    double getPret() const {
        return pret;
    }

    bacterii & operator =(const bacterii & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
        eficienta=ob.eficienta;
        pret=ob.pret;
        return *this;
    }
    double getEficienta() const {
        return eficienta;
    }
    void citesc(istream &os);
    void afisez(ostream &os);

};
void bacterii::citesc(istream &os)
{
    cout<<"--dezinfectant bacterii: \n";
    cout<<"nr specii:";
    os>>specii;
    cout<<"ingrediente: ";
    os.get();
    getline(os,ingrediente);
    cout<<"suprafata: ";
    getline(os, suprafata);
   //calcul eficienta
    eficienta=specii/total;
    if(eficienta<0.9)
        pret=10;
    else
        if(eficienta<0.95)
            pret=20;
        else
            if(eficienta<0.975)
                pret=30;
            else
                if(eficienta<0.99)
                    pret=40;
                else
                        pret=50;
}
void  bacterii:: afisez(ostream &os)
{
    os<<"--dezinfectant bacterii: \n";
    os<<"nr specii:";
    os<<specii;
    os<<endl;
    os<<"ingrediente: ";
    os<<ingrediente;
    os<<endl;
    os<<"suprafata: ";
    os<<suprafata;
    os<<endl;
    os<<"eficienta: ";
    os<<eficienta;
    os<<endl;
    os<<"pret: ";
    os<<pret<<" lei";
    os<<endl;
}
class virusuri: public dezinfectanti
{
private:
    const long double total=1500000;
    double eficienta;//calculata automat
    double pret;//calculat automat


public:
    virusuri(){}

    virusuri(const virusuri & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
        eficienta=ob.eficienta;
        pret=ob.pret;
    }
    ~virusuri(){}
    double getPret() const {
        return pret;
    }
double getEficienta() const {
        return eficienta;
    }
    virusuri & operator =(const virusuri & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
        eficienta=ob.eficienta;
        pret=ob.pret;
        return *this;
    }
    void citesc(istream &os);
    void afisez(ostream &os);

};
void virusuri::citesc(istream &os)
{
    cout<<"--dezinfectant virusuri: \n";
    cout<<"nr specii:";
    os>>specii;
    cout<<"ingrediente: ";
    os.get();
    getline(os,ingrediente);
    cout<<"suprafata: ";
    getline(os, suprafata);

    eficienta=specii/total;
    if(eficienta<0.9)
        pret=10;
    else
    if(eficienta<0.95)
        pret=20;
    else
    if(eficienta<0.975)
        pret=30;
    else
    if(eficienta<0.99)
        pret=40;
    else
    if(eficienta<0.9999)
        pret=50;
}
void  virusuri:: afisez(ostream &os)
{
    os<<"--dezinfectant virusuri: \n";
    os<<"nr specii:";
    os<<specii;
    os<<endl;
    os<<"ingrediente: ";
    os<<ingrediente;
    os<<endl;
    os<<"suprafata: ";
    os<<suprafata;
    os<<endl;
    os<<"eficienta: ";
    os<<eficienta;
    os<<endl;
    os<<"pret: ";
    os<<pret<<" lei";
    os<<endl;
}
class fungi: public dezinfectanti
{
private:
    const long double total=100000000;
    double eficienta;//calculata automat
    double pret;//calculat automat


public:
    fungi(){}

    fungi(const fungi & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
        eficienta=ob.eficienta;
        pret=ob.pret;
    }
    ~fungi(){}
    double getPret() const {
        return pret;
    }
    double getEficienta() const {
        return eficienta;
    }

    fungi & operator =(const fungi & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
        eficienta=ob.eficienta;
        pret=ob.pret;
        return *this;
    }
    void citesc(istream &os);
    void afisez(ostream &os);

};
void fungi::citesc(istream &os)
{
    cout<<"--dezinfectant fungi: \n";
    cout<<"nr specii:";
    os>>specii;
    cout<<"ingrediente: ";
    os.get();
    getline(os,ingrediente);
    cout<<"suprafata: ";
    getline(os, suprafata);

    eficienta=specii/total;
    if(eficienta<0.9)
        pret=10;
    else
    if(eficienta<0.95)
        pret=20;
    else
    if(eficienta<0.975)
        pret=30;
    else
    if(eficienta<0.99)
        pret=40;
    else
    if(eficienta<0.9999)
        pret=50;
}
void  fungi:: afisez(ostream &os)
{
    os<<"--dezinfectant fungi: \n";
    os<<"nr specii:";
    os<<specii;
    os<<endl;
    os<<"ingrediente: ";
    os<<ingrediente;
    os<<endl;
    os<<"suprafata: ";
    os<<suprafata;
    os<<endl;
    os<<"eficienta: ";
    os<<eficienta;
    os<<endl;
    os<<"pret: ";
    os<<pret<<" lei";
    os<<endl;
}
class achizitie
{
    string data;
    string client;
    vector<dezinfectanti*> d;
   vector<masca *>m;

    double pret_total;//calculat automat
public:
    achizitie(){}
    achizitie( achizitie & ob)
    {
        data=ob.data;
        client=ob.client;
        for (vector<dezinfectanti*>::iterator it = ob.d.begin(); it != ob.d.end(); it++)
            d.push_back(*it);

        for (vector<masca*>::iterator it = ob.m.begin(); it != ob.m.end(); it++)
            m.push_back(*it);

        pret_total=ob.pret_total;

    }
    ~achizitie(){}
    achizitie & operator=( achizitie & ob)
    {
        data=ob.data;
        client=ob.client;
        for (vector<dezinfectanti*>::iterator it = ob.d.begin(); it != ob.d.end(); it++)
            d.push_back(*it);

        for (vector<masca*>::iterator it = ob.m.begin(); it != ob.m.end(); it++)
            m.push_back(*it);
        pret_total=ob.pret_total;
        return *this;
    }

    friend ostream &operator<<(ostream &os,  achizitie &ob);
    friend istream &operator>>(istream &os,  achizitie &ob);
};

ostream &operator<<(ostream &os, achizitie &ob)
{
    os<<"----achizitie:\n";
    os << "data: " << ob.data <<endl;
    os<< " client: " << ob.client<<endl;
    int i;
    os<<"dezinfectantii achizitionati: \n";
    for (vector<dezinfectanti*>::iterator it = ob.d.begin(); it != ob.d.end(); it++)
        os<<**it;

    os<<"mastile achizitionate: \n";

    for (vector<masca*>::iterator it = ob.m.begin(); it != ob.m.end(); it++)
        os<<**it;
  os<< " achzitie in valoare de: "<< ob.pret_total<<" lei"<<endl;
    return os;
}
istream &operator>>(istream &os,  achizitie &ob)
{
    cout<<"---dati o achizitie: \n";
    cout<<"data: ";
    getline(os,ob.data);
    cout<<"numele dvs: ";
    getline(os, ob.client);
    int i, dim1, dim2;
    cout<<"cati dezinfectanti vreti sa cumparati: ";
    os>>dim1;
    cout<<"introduceti dezinfectantii: \n";
    ob.pret_total=0;
    for(i=0;i<dim1;i++)
    {
        cout<<"dezinfectantul nr "<<i<<": ";
        cout<<"ce tip de dezinfectant doriti?: (1-bacterii/2-virusuri/3-fungi): ";
        int optiune;
        os>>optiune;
        os.get();
        dezinfectanti *p;
        if(optiune==1)
        {
            p=new bacterii;
            os>>(*p);
            bacterii *b= dynamic_cast<bacterii*>(p);
            ob.pret_total+=(*b).getPret();//calculez si pret total


        } else
            if(optiune==2)
            {
                p=new virusuri;
                os>>(*p);
                virusuri *b= dynamic_cast<virusuri*>(p);
                ob.pret_total+=(*b).getPret();
            }
            else
                if(optiune==3)
                {
                    p=new fungi;
                    os>>(*p);
                    fungi *b= dynamic_cast<fungi*>(p);
                    ob.pret_total+=(*b).getPret();
                }

       ob.d.push_back(p);

    }
    cout<<"cate masti vreti sa cumparati: ";
    os>>dim2;
    cout<<"introduceti mastile: \n";
    for(i=0;i<dim2;i++)
    {
        cout<<"masca nr "<<i<<": ";
        cout<<"ce tip de masca doriti?: (1-masca chirurgicala/2-masca policarbonat: ";
        int optiune;
        os>>optiune;
        os.get();
        masca *p;
        if(optiune==2)
        {
            p=new policarbonat;
            os>>(*p);
            policarbonat *b= dynamic_cast<policarbonat*>(p);
            ob.pret_total+=(*b).getPret();
        }
        else

        {
            p=new chirurgicala;
            os>>(*p);
            ob.pret_total+=(*p).getPret();
        }
       ob.m.push_back(p);

    }

    return os;


}
class singleton
{
    static singleton *instanta;

    vector<masca*>m;
    vector<dezinfectanti*>d;
    vector<achizitie*>a;

    singleton()
    {
        cout<<"Operatiuni: \n";

        cout<<"1->Adaugă un nou dezinfectant în stoc \n";
        cout<<"2-> Adaugă o nouă mască în stoc \n";
        cout<<"3-> Adaugă o nouă achiziție\n";
        cout<<"4-> Afișează dezinfectantul cel mai eficient \n";
        cout<<"5->Calculează venitul dintr-o anumită lună \n";
        cout<<"6->Calculează venitul obținut din măștile chirurgicale cu model.\n";
        cout<<"7->Modifică rețeta unui dezinfectant\n";
        cout<<"8->Afișează cel mai fidel client (clienții NU au nume unic)\n";
        cout<<"9->Afișează ziua cu cele mai slabe venituri, de la deschidere până în prezent.\n";
        cout<<"10->Calculeaza TVA-ul (19% din venituri) care trebuie returnat la ANAF \n";
    }
public:
    static singleton * getInstanta()
    {
        if(instanta==NULL)
            instanta=new singleton;
        return instanta;
    }
    void op1()
    {
        cout<<"Ati ales optiunea1 \n";
        cout<<"ce tip de dezinfectant doriti?: (1-bacterii/2-virusuri/3-fungi): ";
        int optiune;
        cin>>optiune;
        cin.get();
        dezinfectanti *p;
        if(optiune==1)
        {
            p=new bacterii;
            cin>>(*p);

        } else
        if(optiune==2)
        {
            p=new virusuri;
            cin>>(*p);

        }
        else
        if(optiune==3)
        {
            p=new fungi;
            cin>>(*p);

        }

        d.push_back(p);
        cout<<"doresti sa si afisezi dezinfectantii din stoc?(da/nu):";
        string op;
        getline(cin, op);
        if(op=="da")
        {
            for(vector<dezinfectanti*>:: iterator it=d.begin(); it!=d.end(); ++it)
                cout<<**it;

        }

    }
    void op2()
    {
        cout<<"Ati ales optiunea2 \n";
        cout<<"ce tip de masca  doriti?: (1-chirurgicala/2-policarbonat): ";
        int optiune;
        cin>>optiune;
        cin.get();
        masca *p;
        if(optiune==2)
        {
            p=new policarbonat;
            cin>>(*p);

        }
        else

        {
            p=new chirurgicala;
            cin>>(*p);

        }
        m.push_back(p);


        cout<<"doresti sa si afisezi mastile din stoc?(da/nu):";
        string op;
        getline(cin, op);
        if(op=="da")
        {
            for(vector<masca*>:: iterator it=m.begin(); it!=m.end(); ++it)
                cout<<**it;

        }

    }
    void op3()
    {
        cout<<"Ati ales optiunea3 \n";
        achizitie *p=new achizitie;
        cin>>(*p);
        a.push_back(p);
        cout<<"doresti sa si afisezi achzitiile facute din stoc?(da/nu):";
        string op;
        getline(cin, op);
        if(op=="da")
        {
            for(vector<achizitie*>:: iterator it=a.begin(); it!=a.end(); ++it)
                cout<<**it;

        }

    }
    void op4()
    {
        cout<<"Ati ales optiunea4  \n";
        cout<<"Ati ales optiunea4  \n";
        //dezinfectantul cel mai eficient
        int poz=0,i=0;
        int max=0;
        for(vector<dezinfectanti*>:: iterator it=d.begin(); it!=d.end(); ++it, i++)
        if(virusuri *p= dynamic_cast<virusuri*>(*it))
        {
            if(p->getEficienta()>max) {
                max = p->getEficienta();
                poz = i;
            }


        }
        else
            if(bacterii *p= dynamic_cast<bacterii*>(*it))
            {
                if(p->getEficienta()>max)
                {
                    max = p->getEficienta();
                    poz = i;
                }
            } else
                if(fungi *p= dynamic_cast<fungi*>(*it))
                {
                    if(p->getEficienta()>max)
                        max=p->getEficienta();
                    {
                        max = p->getEficienta();
                        poz = i;
                    }
                }
                int j=0;
        for(vector<dezinfectanti*>:: iterator it=d.begin(); it!=d.end(); ++it, j++)
            if(j==poz)
            {
                cout<<"->dezinfectantul cel mai eficient este: \n";
                cout<<**it;
                break;
            }
    }
    void op5()
    {
        cout<<"Ati ales optiunea5  \n";

    }
    void op6()
    {
        cout<<"Ati ales optiunea6  \n";
        //calculez venit din masti chirurgicale cu model
        double total=0;
        for(vector<masca*>:: iterator it=m.begin(); it!=m.end(); ++it)
            if(chirurgicala *p= dynamic_cast<chirurgicala*>(*it))
                if(p->get_logo()!="nu")
                    total+=p->getPret();
        cout<<"venitul total de pe mastile chirurgicale cu model este: ";
        cout<<total<<" lei"<<endl;
    }
    void op7()
    {
        cout<<"Ati ales optiunea7  \n";

        //modific reteta unui dezinfectant

        cout<<"ce tip de dezinfectant doriti sa modificati?: (1-bacterii/2-virusuri/3-fungi): ";
        int optiune;
        cin>>optiune;
        cin.get();
        dezinfectanti *p;
        if(optiune==1)
        {
            p=new bacterii;
            cin>>(*p);

        } else
        if(optiune==2)
        {
            p=new virusuri;
            cin>>(*p);

        }
        else
        if(optiune==3)
        {
            p=new fungi;
            cin>>(*p);

        }
         cout<<"dati noua reteta: ";
        string reteta;
        getline(cin, reteta);
        p->reteta(reteta);
        d.push_back(p);
        cout<<"doresti sa si afisezi dezinfectantii din stoc?(da/nu):";
        string op;
        getline(cin, op);
        if(op=="da")
        {
            for(vector<dezinfectanti*>:: iterator it=d.begin(); it!=d.end(); ++it)
                cout<<**it;

        }
    }
    void op8()
    {
        cout<<"Ati ales optiunea8  \n";
    }
    void op9()
    {
        cout<<"Ati ales optiunea9  \n";
    }
    void op10()
    {
        cout<<"Ati ales optiunea10  \n";
    }

};
singleton * singleton :: instanta;
int main()
{
    singleton *s;
    s=singleton::getInstanta();

    while (true)
    {

        try {
            int optiune;
            cout << "Dati numarul optiunii: ";
            cin >> optiune;
            cin.get();
            if (optiune <= 0 || optiune > 10)
                throw
                        "Nu ai ales corect!! mai alege o data!! \n";

            if(optiune==1)
            {
                s->op1();
            }
            else

            if(optiune==2)
            {
                s->op2();
            }
            else

            if(optiune==3)
            {

                s->op3();
            }
            else
            if(optiune==4)
            {
                s->op4();

            }
            else
            if(optiune==5)
            {
                s->op5();

            }
            else
            if(optiune==6)
            {
                s->op6();

            }
            else
            if(optiune==7)
            {
                s->op7();

            }
            else
            if(optiune==8)
            {
                s->op8();

            }
            else
            if(optiune==9)
            {
                s->op9();

            }
            else
            if(optiune==10)
            {
                s->op10();

            }
        }
        catch (const char *s)
        {
            cout << s<<endl;

        }
        cout<<"doriti sa continuati? (da/nu): ";
        string rasp;
        //cin.get();
        getline(cin,rasp);
        if(rasp=="nu")
            break;
    }

    return 0;
}
