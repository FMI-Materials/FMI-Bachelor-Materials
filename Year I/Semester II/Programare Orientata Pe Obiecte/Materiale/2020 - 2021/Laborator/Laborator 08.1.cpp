#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;
using std::runtime_error;

double Fractie(int numarator, int numitor){

if(numitor==0)
    throw runtime_error("Numitorul este 0");

    return (double)numarator/numitor;

}

class ExceptiaMea: public exception{
public:
    virtual const char* what() const throw(){

        return "Exceptia Mea";

    }


} exceptiaMea;

void functiaMea(int a){

        if(a==1) throw exceptiaMea;
        if(a==10) throw 10;
        if(a==9) throw 9;
        if(a!=0) throw 3.4;
        if(a==0) throw 'a';


}

int main()
{
/*
try{
    throw exceptiaMea;
}
catch(ExceptiaMea &e){

    cout<<"Am prins o exceptie";

}
int k=1;
while(k==1){

    int a, b;
    cout<<"\nIntroduceti numaratorul: ";
    cin>>a;
    cout<<"\nIntroduceti numitorul: ";
    cin>>b;



    try{
        cout<<"\nRezultatul este: "<<Fractie(a,b);
        k=0;

    }
    catch(exception &e){

       cout<<e.what();
       cout<<endl;
        //cout<<"\nAm prins exceptie de runTime\n";

    }

}*/

int a=9; // double
try{
           cout<<"\n Ceva 1 \n";
            try{
                cout<<"\n Ceva 4 \n";
                functiaMea(a);
                cout<<"\n Ceva 5 \n";
            }
            catch(double){
                cout<<"\n S-a prins double \n" ;
            }
            catch(...){

                cout<<"\n Ala bala portocala \n";
            }

        cout<<"\n Ceva 2\n";
}
catch(int a){

    if(a==9)
     cout<<"\n Am prins un 9 \n" ;
    if(a==10)
        cout<<"\n Am prins 10\n ";

}
catch(...){

    cout<<"\n Am prins o exceptie necunoscuta \n" ;

}
cout<<"\n ceva 3 \n";


    return 0;
}
