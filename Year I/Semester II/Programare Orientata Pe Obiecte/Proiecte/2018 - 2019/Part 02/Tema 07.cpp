#include <iostream>
#include<string>
#include<map>
#include<vector> //folosit sa retin cele n obiecte
using namespace std;
//          !!!IMPORTANT VEZI COMENTARIILE DE LA LINIA 76+ !!!!!

/*             ierarhia :
      MOSTENIRE:
                PLATA(CB)-abstracta
                -data(string)
                -suma(double)
                -id(int)
                -idd(static int)
                  |
    NUMERAR(CD), CEC(CD),      CARD(CD)
                -nume(string)  -nume(string)
                -cnp(string)   -nr_card(string)//poate sa aiba 0-uri in fata ex: 007..

    GESTIUNE+SPECIALIZARE CLASE TEMPLATE SEPARATE DE IERARHIE
    in GESTIUNE gasim procedeul de compunere prin instantierea unui obiect
        de tipul numerar, cec, card ca membru al clasei gestiune
    aici utilizez map-ul (*unordered_map/unordered_set nu sunt acceptate de versiunea mea de codeblocks..)
*/
class plata
{
protected:
    string data;
    double suma;
    int id;
    static int idd;//contorizez numarul de obiecte de tipul clasei

public:
    plata()
    {
        data="";
        suma = 0;
        increment();
        id=idd;

    }
    plata(string d, double s)
    {
        data=d;
        suma = s;
        increment();
        id=idd;

    }
    plata(const plata & ob)
    {
        data=ob.data;
        suma = ob.suma;
        id=ob.id;
    }
    virtual ~plata()
    {
        data="";
        suma = 0;
        id=0;
    }
    static void increment()
    {
        idd++;
       // cout<<"da"<<idd<<endl;

    }
    static void decrement()
    {
        idd--;
        //cout<<"dad"<<idd<<endl;

    }
    virtual void citesc(istream &os)=0;
    virtual void afisez(ostream &os)=0;

    friend ostream& operator <<(ostream& os, plata& ob);
    friend istream& operator >>(istream& os, plata& ob);
};
int plata:: idd=0;//este posibil sa mai apara decalaje ale valorilor pe parcurs deoarece
                    //cand este creat un nou obiect de tipul numerar, cec sau card este incrementat id-ul
                   //pentru citirea a n obiecte am avut grija sa mearga consecutiv
                   //problema poate aparea la alte operatii pe care le-ati putea face in afara citirii si memorarii a ne obuecte
                   //oricum ideea e sa fie un id de plata diferit, nu a specificat ca trebuie sa fie neaparat consecutiv
                   //sper sa nu fie o problema :)
ostream& operator << (ostream& os, plata& ob)
{

    ob.afisez(os);
    return os;
}
istream& operator >>(istream& os, plata& ob)
{

    ob.citesc(os);
    return os;
}
class numerar: public plata
{


public:
    numerar(): plata(){}
    numerar(string d, double s): plata( d, s){}
    numerar(const numerar &ob)
    {
        plata:: decrement();
        data=ob.data;
        suma=ob.suma;
        id=ob.id;
    }
    ~numerar(){}
    int gett_id() const
    {
        return id;
    }

    numerar & operator = (const numerar &ob);
    void citesc(istream &os);
    void afisez(ostream &os);

};

numerar & numerar:: operator=(const numerar &ob)
{

    data=ob.data;
    suma=ob.suma;
    id=ob.id;
    return *this;
}
void numerar:: afisez(ostream &os)
{

    os<<"Forma de plata :Numerar:"<<endl;
    os<<"id-ul de plata este: ";
    os<<id;
    os<<endl;
    os << "ati platit la data de: ";
    os << data;
    os << endl;
    os << "suma de: ";
    os << suma;
    os << endl;

}
void numerar:: citesc(istream &os)
{
    cout<<"Forma de plata :Numerar:"<<endl;
    cout << "dati data platii: ";
    getline(os,data);
    cout << "dati suma platita: ";
    os >> suma;
    os.get();

}
class cec: public plata
{
private:
    string nume;
    string cnp;


public:
    cec(): plata()
    {
        nume="";
        cnp="";
    }
    cec(string c,string n, string d, double s): plata( d, s)
    {
        nume=n;
        cnp=c;
    }
    cec(const cec &ob)
    {
        plata:: decrement();

        data=ob.data;
        suma=ob.suma;
        nume=ob.nume;
        cnp=ob.cnp;
        id=ob.id;
    }
    ~cec()
    {
        nume="";
        cnp="";

    }

    int gett_id() const
    {
        return id;
    }
    cec & operator = (const cec &ob);
    void citesc(istream &os);
    void afisez(ostream &os);

};
;
cec & cec:: operator=(const cec &ob)
{

    data=ob.data;
   suma=ob.suma;
    nume=ob.nume;
    cnp=ob.cnp;
    id=ob.id;
    return *this;

}
void cec:: afisez(ostream &os)
{
    os<<"Forma de plata :CEC:"<<endl;
    os<<"id-ul de plata este: ";
    os<<id;
    os<<endl;
    os << "ati platit la data de: ";
    os << data;
    os << endl;
    os << "suma de: ";
    os << suma;
    os << endl;
    os<<"cec pe numele: ";
    os<<nume;
    os<<endl;
    os<<"Cnp-ul dumneavoastra:";
    os<<cnp;
    os<<endl;

}
void cec:: citesc(istream &os)
{

    cout<<"Forma de plata :CEC:"<<endl;
    cout << "dati data platii: ";
    getline(os,data);
    cout << "dati suma platita: ";
    os >> suma;
    os.get();
    cout<<"cec pe numele: ";
    getline(os,nume);
    cout<<"Cnp-ul dumneavoastra:";
    getline(os,cnp);


}
class card: public plata
{
private:

    string nume;
    string nr_card;//m-am gandit ca poate sa aiba si 0 la inceput si de aceea l-am facut string
public:
    card(): plata()
    {
        nume="";
        nr_card="";
    }
    card(string x,string n, string d, double s): plata(d, s)
    {
        nume=n;
        nr_card=x;
    }
    card(const card &ob)
    {
        plata:: decrement();

        data=ob.data;
        suma=ob.suma;
        nume=ob.nume;
        id=ob.id;
        nr_card=ob.nr_card;

    }
    ~card()
    {
        nume="";
        nr_card="";

    }
    int gett_id() const
    {
        return id;
    }
    string getter_nume() const
    {
        return nume;
    }
    string getter_card() const
    {
        return nr_card;
    }

    card & operator = (const card &ob);
    void citesc(istream &os);
    void afisez(ostream &os);

};

card & card:: operator=(const card &ob)
{

    data=ob.data;
    suma=ob.suma;
    nume=ob.nume;
    nr_card=ob.nr_card;
    id=ob.id;
    return *this;

}
void card:: afisez(ostream &os)
{
    os<<"Forma de plata :Card:"<<endl;
    os<<"id-ul de plata este: ";
    os<<id;
    os<<endl;
    os<<"Numarul de card este:";
    os<<nr_card;
    os<<endl;
    os << "ati platit la data de: ";
    os << data;
    os << endl;
    os << "suma de: ";
    os << suma;
    os << endl;
    os<<"card pe numele: ";
    os<<nume;
    os<<endl;



}
void card:: citesc(istream &os)
{
    cout<<"Forma de plata :Card:"<<endl;

    cout<<"dati numarul de card:";
    getline(os,nr_card);
    cout << "dati data platii: ";
    getline(os,data);
    cout << "dati suma platita: ";
    os >> suma;
    os.get();
    cout<<"card pe numele: ";
    getline(os,nume);

}

template< typename T>
class gestiune
{
    T x;
    static int nr_plati;
    static map<int,T> mymap;
public:
    gestiune()
    {
        plata::decrement();
    }

    gestiune(T ob)
    {
        x=ob;
        mymap[ob.gett_id()]=ob;
        nr_plati++;
    }
    gestiune(const gestiune & ob)
    {

        x=ob.x;
    }
    ~gestiune()
    {
        nr_plati=0;
        mymap={};
    }

    gestiune & operator =(const gestiune &ob)
    {

        x=ob.x;
        return *this;
    }
    gestiune & operator +=(T & ob)
    {
        plata::decrement();
        x=ob;
        mymap[ob.gett_id()]=ob;
        nr_plati++;
        return *this;
    }


    template<typename U>
    friend ostream & operator  <<(ostream &os, gestiune<U> &ob);
    template<typename U>
    friend istream & operator  >>(istream &os, gestiune<U> &ob);

};
template <typename T>
int gestiune<T>:: nr_plati=0;
template<typename T>
map <int, T> gestiune<T>:: mymap;


template<typename U>
 ostream & operator  <<(ostream &os, gestiune<U> &ob)
{

    os<<"Gestiune pentru : ";

    U *obiect=new U(ob.x);
    plata:: decrement();

    if(cec *c=dynamic_cast<cec*>(obiect))
        os<<"cecuri:"<<endl;
    else
    if(numerar *c=dynamic_cast<numerar*>(obiect))
        os<<"numerar :"<<endl;


    if (gestiune<U>::nr_plati==0)
        os<<"Nu s-au facut plati de acest fel."<<endl;
    else
        {

        os << "Numarul de plati de acest fel este: ";
        os << gestiune<U>::nr_plati;
        os << endl << "Platile de acest fel sunt: " << endl;
        int i = 0;


        for (typename map<int, U>::iterator it=gestiune<U>::mymap.begin(); it!=gestiune<U>::mymap.end(); ++it)
        {
            os << "---------------Plata " << i << " -----------" << endl;
            os << it->second<< endl;
            i++;

        }

        }

    return os;
}
template<typename U>
istream & operator  >>(istream &os,gestiune<U> &ob)
{
    U obiect;
    os>>obiect;
    ob+=obiect;
    return os;
}


//-------------Specializata aferent card---------------------------------

template<>
class gestiune<card>
{
    static int nr_plati;
    static int nr_clienti;//poate sa difere de numarul de plati pentru ca
                            // un client poate sa efectueze cate plati cu cardul vrea
    static string *v_nume;
    static map<int,card> mymap;
    card x;
public:
    gestiune()
    {
        plata::decrement();
    }

    gestiune(card ob)
    {

        x=ob;
        mymap[ob.gett_id()]=ob;
        nr_plati++;

        string name;//caut sa vad daca clientul este deja inregistrat
        int gasit=0,i;
        name = ob.getter_nume();
        if(nr_clienti==0)
        {
            v_nume[nr_clienti]=name;
            nr_clienti++;
        } else
            {
            for (i = 0; i < nr_clienti; i++)
                if (v_nume[i] == name) {
                    gasit = 1;
                    break;
                }

            if (gasit == 0)//daca nu e inseamna ca am un client nou si il adaug corespunzator
            {
                v_nume[nr_clienti] = name;
                nr_clienti++;
            }
        }

    }
    gestiune(const gestiune<card> & ob)
    {
        x=ob.x;
    }
    ~gestiune()
    {
        nr_plati=0;
        nr_clienti=0;
        delete v_nume;
        mymap={};
    }
    gestiune<card>& operator += (card &ob)
    {
        plata::decrement();
        x=ob;
        mymap[ob.gett_id()]=ob;
        nr_plati++;

        string name;//caut sa vad daca clientul este deja inregistrat
        int gasit=0,i;
        name = ob.getter_nume();
        if(nr_clienti==0)
        {
            v_nume[nr_clienti]=name;
            nr_clienti++;
        } else
        {
            for (i = 0; i < nr_clienti; i++)
                if (v_nume[i] == name) {
                    gasit = 1;
                    break;
                }

            if (gasit == 0)//daca nu e inseamna ca am un client nou si il adaug corespunzator
            {
                v_nume[nr_clienti] = name;
                nr_clienti++;
            }
        }
        return *this;
    }
    gestiune<card> & operator =(const gestiune &ob)
    {
        x=ob.x;
        return *this;
    }


    friend ostream & operator  <<(ostream &os, gestiune<card> &ob);

    friend istream & operator  >>(istream &os, gestiune<card> &ob);


};
//template<>
int gestiune<card>:: nr_clienti=0;
//template <>
int gestiune<card>:: nr_plati=0;
//template<>
string* gestiune <card>:: v_nume=new string[1000];
//template<>
map <int, card> gestiune<card>:: mymap;

ostream & operator  <<(ostream &os, gestiune<card> &ob)
{

    os<<"Gestiune pentru : ";
        os<<"card :"<<endl;
        //vreau sa afisez lista de nume:
        if(gestiune<card>::nr_clienti==0)
            os<<"Nu avem clienti"<<endl;
        else {
            os << "Lista cu cei " << gestiune<card>::nr_clienti << " clienti este: " << endl;
            int j;
            for (j = 0; j < gestiune<card>::nr_clienti; j++)
                os << gestiune<card>::v_nume[j]<<endl;
        }

    if (gestiune<card>::nr_plati==0)
        os<<"Nu s-au facut plati de acest fel."<<endl;
    else
    {

        os << "Numarul de plati de acest fel este: ";
        os << gestiune<card>::nr_plati;
        os << endl << "Platile de acest fel sunt: " << endl;
        int i = 0;


        for (typename map<int, card>::iterator it=gestiune<card>::mymap.begin(); it!=gestiune<card>::mymap.end(); ++it)
        {
            os << "---------------Plata " << i << " -----------" << endl;
            os << it->second<< endl;
            i++;

        }

    }

    return os;
}

istream & operator  >>(istream &os,gestiune<card> &ob)
{
    card obiect;
    os>>obiect;
    ob+=obiect;
    return os;
}



void menu()
{
    cout<<"Cum alegeti sa efectuati cele plata? : "<<endl;
    cout<<"1->plata numerar"<<endl;
    cout<<"2->plata cec"<<endl;
    cout<<"3->plata card de credit"<<endl;
    //dupa afisez pentru fiecare gestiunea

}
void citire(int &n, vector<plata*>& v, gestiune<numerar> & nr, gestiune<cec>& ce, gestiune<card> & c)
{
    int  i=0,ok=0;
    do {
        try {
            cout << "Dati n= ";
            cin >> n;
            if (n == 0)
                throw "Ai ales sa NU platesti!";
            else if (n < 0)
                throw "NU ai dat un numar valid de plati !";
            ok = 1;
        }
        catch (const char *s)
        {
            cout << s << endl;

        }
    }
    while(ok==0);

    menu();

 while (i<n)
 {


     try {
         int optiune;
         cout << "Dati numarul optiunii: ";
         cin >> optiune;
         cin.get();
         if (optiune <= 0 || optiune >= 4)
             throw
                     "Nu ai ales corect!! mai alege o data ";
         i++;

         if(optiune==1)
         {//numerar
             numerar *nrr=new numerar;
             cin>>*nrr;
             v.push_back(nrr);
             nr+=*nrr;

         } else
             if(optiune==2)
             {
                 //cec
                 cec *cee=new cec;
                 cin>>*cee;
                 v.push_back(cee);
                 ce+=*cee;

             } else
                 if(optiune==3)
                 { //card
                    card *cc=new card;
                    cin>>*cc;
                    v.push_back(cc);
                    c+=*cc;
                 }

     }
     catch (const char *s) {
         cout << s<<endl;
     }
 }

}
void afisare(vector<plata*>v,gestiune<numerar>nr, gestiune<cec> ce, gestiune<card>c)
{
    cout<<"-----------------------------"<<endl;
    cout << "cele n plati efectuate sunt:" << endl;
 int i=0;
    for (vector<plata*>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout<<"~~~~~~~~~~Plata"<<i<<"~~~~~~~~~~"<<endl;
        cout << **it;
        i++;
    }
    cout<<"---------Statistica pe gestiuni---------"<<endl;
    cout<<nr;
    cout<<ce;
    cout<<c;

}

int main()
{
    vector<plata*>v;//upcasting
    int n;
    gestiune<numerar>nr;
    gestiune<cec> ce;
    gestiune<card>c;
    citire(n,v,nr,ce,c);
    afisare(v,nr,ce,c);

    return 0;
}
