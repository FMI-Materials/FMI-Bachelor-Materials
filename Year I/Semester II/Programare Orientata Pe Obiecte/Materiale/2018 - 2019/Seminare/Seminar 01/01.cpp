#include <cstdlib>
#include <iostream>
using namespace std;
//Diferente C C++
 //***Tipul referinta
/*
int i;
int *pi,j;  //pi este adresa a unui intreg   !! j este doar intreg
int & ri=i; //ri este alt nume pentru variabila i

int main()
{pi=&i;  // pi este adresa variabilei i
 *pi=3;   //in zona adresata de pi se pune valoarea 3
} */

//***Transmmiterea parametrilor
/*
void f(int ii, int *pii, int &rii)   //pentru  variabilele : int x,y,z;- vom apela:   f(x,&y,z)   ;
{ ii++;    //pentru i se rezerva zona de memorie si valoarea parametrului actual x se copiaza  in i
             // modificarile facute asupra variabilei i nu modifica parametrul actual x
(*pii)++;  // se modifica variabila adresata de pi deci parametrul actual y
 rii++;       // ri este alt nume pentru parametrul actual z -orice modificare a referintei modifica parametrul actual
}

 int main()
 {int x,y,z;
  x=y=z=0;
  f(x,&y,z) ;
 } */

//***Alocare dinamica
/*
int main()
{ int *pi;
 pi=new int;// aloca zona pentru un int si intoarce  in pi adresa zonei de memorie sau NULL
 delete pi; // elibereaza  zona adresata de pi -o considera neocupata
   pi=new int(2);// aloca zona si initializeaza zona cu valoarea 2
   pi=new int[2]; // aloca un vector de 2 elemente  de tip intreg
   delete [] pi; //elibereaza intreg vectorul
     //-pentru new se foloseste delete
     //- pentru new [] se foloseste delete []
} */


//*** Intoarcerea valorilor din functie
/*
int  g0(int ii, int *pii,int &rii)    // functie care intoarce  un intreg
{int vl;
 return  vl; //intoarce o valoare -pe stiva
 return ii; //intoarce o valoare
 return *pii; // intoarce o valoare
 return rii;// intoarce o valoare
 int *pl=new int;
 return *pl; // intoarce o valoare
}
int main()
{int x,y,z;
// g0(x,&y,z)=2;   // eroare nu pot pune valori intr-o zona temporala constanta
} //*/

/*
int & g1(int ii, int *pii,int &rii)    // functie care intoarce un alt nume pentru un intreg
{int vl;
 return  vl; //warning-intoarce un alt nume catre o zona care va fi eliberata -valida sintactic dar va genera erori ulterior
 return ii; //warning-intoarce un alt nume spre o zona care va fi eliberata-valida sintactic dar va genera  erori ulterior
 return *pii; // intoarce un alt nume pt zona adresata de pointerul pii (adreseaza zona prin adresa data de parametrul actual)
 return rii;// intoarce alt nume pentru zona variabilei rii (variabila ri este un alt nume pentru paramtrul actual corespunzator)
  int *pl=new int;
 return *pl; // intoarce alt nume pentru zona nou creata -ramane alocata pana se apeleaza delete
}
//putem  avea apelul:
int main()
{ int x,y,z;
   g1(x,&y,z)=2; //intorcand un alt nume catre o zona de memorie - in zona respectiva pot atribui valoarea 2
} */

/*
int * g2(int ii,int *pii, int & rii) // functie care intoarce adresa unui intreg
{int vl;
 return &vl; //warning-intorc adresa unei zone care va fi eliberata
 return &ii;  //warning-intorc adresa unei zone care va fi eliberata
   return pii;
   int *pl=new int;
   return pl; //intoarce o adresa  a unei zone care ramine alocata pina la stegerea cu delete
   return &rii;  //intoarce adresa zonei corespunzatoare referintei respectiv a parametrului actual
// nu exista tipul de date adresa a unei referinte adica : int & *p;
}
//pot avea apelul:
  int main()
 { int x,y,z;
   *g2(x,&y,z)=2;
 }// in zona adresata de adresa  intoarsa de functie se pune valoarea 2
*/

//***Putem avea functii cu parametru implicit
/*
void f1(int i, int j=0){}
int main()
{ f1(1,2);   //avem j = 2
  f1(1);      //  avem j=0 (valoarea implicita)
} */

//Parametrii impliciti pot apare dupa specificarea celor ne-impliciti :
// void f2(int i=0,int j){} //gresit
// Putem avea mai multi parametrii cu valori implicite
/*void f3(int i,int j=0,int k=1){}
int main()
{ f3(2,3);// considera j=3  si k=1 valoarea implicita
}*/

//*** Polimorfism de compilare
// Pot exista mai multe functii cu acelasi nume dar numar  sau tip diferit de parametrii
//-trebuie ca la apel sa se poata alege o singura functie
//-se incearca intai potrivirea exacta,
//-daca nu se poate -se incearca prin conversie pas1.predefinite fara pierderi,
                                             // pas2. apoi predefinite cu pierderi,
                                              //pas3. apoi definite de utilizator
/*
void f3(int i,int j=0){}
void f3(int i){}
int main(){ f3(1);}// gresit- ambiguu -poate alege ambele variante
*/
/*
void f4(double d){cout<<"double";}
void f4(float f){cout <<"float";}
int main()
{f4 (3.5);//alege double -pt constante in virgula  mobila
 f4(3);   //gresit - ambigua -alege ambele variante
}
*/
/*
void f5(double d){cout<<"double";}
void f5(int d){cout<<"int";}
int main()
{float f;
 f5 ((float) 3.5);//face conversie intai fara pierderi spre double -nu e ambiguitate
 f5(f);
 char c;
 f5(c); // ar trebui sa dea ambiguitate dar este o conversie automata
}
*/
/*
void f6(int a){}
void f6(int& a){}
int main()
{ int b;
 f6(2);// nu da ambiguitate
 f6(b); //da ambiguitate
}
*/
//*** citire si scriere
/*
int main()
{int x,y,z;
   cin >>x; // citire(extragere) din fluxul cin in variabila x -sensul sagetii
            // este de fapt operatorul  >>(cin,x) care  intoarce fluxul (prin referinta ) cin din care s-a extras data x
   cin>>y>>z; //este de fapt  >>(>>(cin,y), z) -citeste y si z

cout<<x; // x este afisata(inserata) in fluxul cout     -sensul sagetii
	    //este de fapt operatorul  <<(cout, x ) -intoarce fluxul cout (prin referinta) in care s-a inserat x
cout<<y<<z; // este de fapt <<(<<(cout,y),z) -afiseaza y si z
} */

/*
int i,j;
int *pi;
int &ri=i;
//int & & rr=ri; // nu este permis ca tip de date
//int & *pr;    // nu este permis ca tip de date desi pot avea pi=&ri;
  int main(){cout<<&i<<"*"<<&ri<<endl;} //de fapt da adresa variabilei referite
//int & v[2] ;// nu este permis ca tip nici daca se initializeaza int &v1[2]={i,j};
int * &rp=pi;// alt nume pt pi
int v[2]; // echivalent cu int * const p;
//int * & rp=v; //nu este referinta spre const
int * const & rcp=v; //corect prin rcp nu pot modifica pointerul const
//const int * & rpc=v; // nu e corect prin referinta pot modifica pointerul care nu va modifica zona
*/
