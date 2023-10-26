#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <math.h>

#define LMAX 10
#define PI 3.14

using namespace std;

struct Circle{
    int r;
    int h;
    Circle(int r, int h){
        this->r = r;
        this->h = h;
    }
};
struct Rectangle{
    int L, l;
    int h;
    Rectangle(int L, int l, int h){
        this->L = L;
        this->l = l;
        this->h = h;
    }
};
struct Square{
    int l;
    int h;
    Square(int l, int h){
        this->l = l;
        this->h = h;
    }
};
struct Triangle{
    int C, c;
    int h;
    Triangle(int C, int c, int h){
        this->C = C;
        this->c = c;
        this->h = h;
    }
};

struct Form{
    Circle *circle;
    Rectangle *rectangle;
    Square *square;
    Triangle *triangle;
    int type;

    Form(int b, int x, int y, int h){
        if(b==1)
            this->circle = new Circle(x, h);
        if(b==2)
            this->rectangle = new Rectangle(x, y, h);
        if(b==3)
            this->square = new Square(x, h);
        if(b==4)
            this->triangle = new Triangle(x, y, h);
        this->type = b;
    }
};

class Objects{
public:

    vector<Form> forms;

    void remove_form(int n){
        this->forms.erase(this->forms.begin()+(n-1));
    }

    void add_form(int b, int x, int y, int h){
        this->forms.push_back(Form(b, x, y, h));
    }

    pair<double, double> calc_form(int i = -1){
        double g = 0, f = 0;
        if(i==-1)
            i = this->forms.size()-1;
        int b = this->forms[i].type;
        if(b==1){
            int r = this->forms[i].circle->r;
            int h = this->forms[i].circle->h;
            f = PI*r*r;
            g = f*h*2;
            f += (2*PI*r)*h;
        }
        if(b==2){
            int L = this->forms[i].rectangle->L;
            int l = this->forms[i].rectangle->l;
            int h = this->forms[i].rectangle->h;
            f = l*L;
            g = f*h*2;
            f += 2*l*h;
            f += 2*L*h;
        }
        if(b==3){
            int l = this->forms[i].square->l;
            int h = this->forms[i].square->h;
            f = l*l;
            g = f*h*2;
            f += 4*l*h;
        }
        if(b==4){
            int C = this->forms[i].triangle->C;
            int c = this->forms[i].triangle->c;
            int h = this->forms[i].triangle->h;
            f = (c*C)/2;
            g = f*h*2;
            double i = sqrt(c*c + C*C);
            f += c*h;
            f += C*h;
            f += i*h;
        }
        return {g, f};
    }

    pair<double, double> calc_all_forms(){
        pair<double, double> c = {0, 0};
        for(int i=0;i<this->forms.size();i++){
            c.first += calc_form(i).first;
            c.second += calc_form(i).second;
        }
        return c;
    }

    void read_b(int b){
        int x, y = 0, h;
        if(b==1){
            cout<<"Raza R = ";
            cin>>x;
        }
        if(b==2){
            cout<<"Latura l = ";
            cin>>x;
            cout<<"Latura L = ";
            cin>>y;
        }
        if(b==3){
            cout<<"Latura l = ";
            cin>>x;
        }
        if(b==4){
            cout<<"Cateta c = ";
            cin>>x;
            cout<<"Cateta C = ";
            cin>>y;
        }
        cout<<"Inaltimea h = ";
        cin>>h;
        cout<<'\n';
        add_form(b, x, y, h);
        pair<double, double> c = calc_form();
        cout<<"Necesatul de gem este "<<c.first<<" grame\n";
        cout<<"Necesatul de frisca este "<<c.second<<" grame\n\n";
    }

};

string add(string x, string y){
    if(x.size()<y.size())
        return add(y, x);
    string final;
    int left = 0;
    for(int i=x.size()-1, j = y.size()-1;i>=0 && j>=0;i--, j--){
        int c = (x[i]-'0')+(y[i]-'0');
        c+=left;
        if(c>9) {
            left=1;
            c = c % 10;
        }
        final.push_back(c+'0');
    }
    if(left!=0)
        final.push_back(left+'0');
    reverse(final.begin(), final.end());
    return final;
}

void P1(){
    string x, y;
    cout<<"A = ";
    cin>>x;
    cout<<"B = ";
    cin>>y;
    cout<<"A + B = "<<add(x, y)<<'\n';
}

int s_div(int x){
    int s = 1;
    for(int d = 2; d*d<=x;d++)
        if(x%d==0)
            s+=d;
    return s;
}

void P2(){
    /// Stiu ca trebuie cu numere mari, n am avut timp
    int x, y, sum = 0;
    cout<<"a = ";
    cin>>x;
    cout<<"b = ";
    cin>>y;
    for(;x<=y;x++)
        if(s_div(x)==x)
            sum+=x;
    cout<<"Suma numerelor perfecte este: "<<sum;
}

void P3(){
    Objects *objects = new Objects();
    string op;
    int b;
    while(true){
        cout<<"Introduceti optiunea: ";
        cin>>op;
        if(op=="ADD"){
            cout<<"\nForma bazei: ";
            cin>>b;
            objects->read_b(b);
        }
        if(op.substr(0, 6)=="REMOVE"){
            b = op[6]-'0';
            objects->remove_form(b);
            cout<<'\n';
        }
        if(op=="TOTAL"){
            pair<double, double> c = objects->calc_all_forms();
            cout<<"Necesatul de gem este "<<c.first<<" grame\n";
            cout<<"Necesatul de frisca este "<<c.second<<" grame\n\n";
        }
        if(op=="STOP")
            break;
    }
}

int main() {
    //P1();
    //P2();
    P3();
    return 0;
}
