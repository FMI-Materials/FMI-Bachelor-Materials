#include <iostream>
#include "punct.h"
#include "patrat.h"
#include "dreptunghi.h"
#include "romb.h"
#include "paralelogram.h"
#include "trapez.h"
#include<vector>
#include<string>
using namespace std;
void menu()
{
    cout<<"ce vreti sa cititi?"<<endl;
    cout<<"1->patrat"<<endl;
    cout<<"2->romb"<<endl;
    cout<<"3->dreptunghi"<<endl;
    cout<<"4->paralelogram"<<endl;
    cout<<"5->trapez"<<endl;
}
void citire(vector <patrat*>&v)
{
    int n;
    cout<<"n=";
    cin>>n;
    int i=0;
    menu();
    while(i<n)
{
        int optiune;
        cin>>optiune;
        if(optiune==1)
        {
             patrat *p=new patrat;
             cin>>*p;
             v.push_back(p);
            //patrat
        }
        if(optiune==2)
        {
            //romb
            romb *p=new romb;
            cin>>*p;
            v.push_back(p);
        }
        if(optiune==3)
        {
            //dreptunghi
            dreptunghi *p=new dreptunghi;
            cin>>*p;
            v.push_back(p);
        }
        if(optiune==4)
        {
            //paralelogram
            paralelogram *p=new paralelogram;
            cin>>*p;
            v.push_back(p);
        }
        if(optiune==5)
        {
            //trapez
            trapez *p=new trapez;
            cin>>*p;
            v.push_back(p);
        }
        string s;
        cout<<"continuati?(da/nu)";
        cin>>s;
        if(s=="nu")
            break;
        if(s=="da" && i+1==n)
            cout<<"Vreti sa continuati dar ati citit cele n obiecte=> ne oprim aici :(";
        i++;

}
}
void afisare(vector<patrat*>v)
{
    cout<<"-----------------------------"<<endl;
    cout << "cele n forme date sunt:" << endl;

    for (vector<patrat*>::iterator it = v.begin(); it != v.end(); it++)
        cout << **it;

}
int main()
{

vector <patrat*>v;
citire(v);
afisare(v);

}

