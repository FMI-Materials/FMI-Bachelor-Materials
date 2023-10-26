#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

ifstream in("test8.in");
ofstream out("test8.out");

struct nodTreap{
    int cheie, prioritate;
    nodTreap *stang, *drept;
};

struct Treap{
    nodTreap* radacina;
    int cardinal;
    Treap(){
        radacina = NULL;
        cardinal = 0;
    }
    nodTreap* rotatieDreapta(nodTreap *y){
        nodTreap *x = y->stang;
        nodTreap *T = x->drept;

        x->drept = y;
        y->stang = T;

        return x;
    }

    nodTreap* rotatieStanga(nodTreap *x){
        nodTreap *y = x->drept;
        nodTreap *T = y->stang;

        y->stang = x;
        x->drept = T;

        return y;
    }

    nodTreap*  nodNou(int cheie){
        nodTreap* nod = new nodTreap;
        nod->cheie = cheie;
        nod->prioritate = rand()%100000;
        nod->stang = nod->drept = NULL;

        return nod;
    }

    nodTreap*  cautare(nodTreap* radacina, int cheie){
        if( radacina == NULL || radacina->cheie == cheie)
            return radacina;

        if(radacina->cheie < cheie)
            return cautare(radacina->drept,cheie);

        return cautare(radacina->stang,cheie);
    }

    nodTreap* inserare(nodTreap* radacina, int cheie){

        if(!radacina){
            cardinal++;
            return nodNou(cheie);
        }
        if (radacina->cheie == cheie) {
            out << "Nodul "<<cheie<<" exista deja in arbore.\n";
            return radacina;
        }
        if(cheie <= radacina->cheie){
            radacina->stang = inserare(radacina->stang, cheie);

            if(radacina->stang->prioritate > radacina->prioritate)
                radacina = rotatieDreapta(radacina);
        }
        else{
            radacina->drept = inserare(radacina->drept,cheie);

            if(radacina->drept->prioritate > radacina->prioritate)
                radacina = rotatieStanga(radacina);
        }
        return radacina;
    }
    nodTreap* stergere(nodTreap* radacina, int cheie, bool &fl){
        if(radacina == NULL)
            return radacina;
        if(cheie < radacina->cheie)
            radacina->stang = stergere(radacina->stang,cheie, fl);
        else if(cheie > radacina->cheie)
            radacina->drept = stergere(radacina->drept,cheie, fl);

        //daca am ajuns aici inseamna ca radacina e cheia
        // vedem daca unul din fii e null
        else if(radacina->stang == NULL){
            nodTreap* nod= radacina->drept;
            delete(radacina);
            radacina = nod;
            fl = true;
        }
        else if(radacina->drept == NULL){
            nodTreap* nod= radacina->stang;
            delete(radacina);
            radacina = nod;
            fl = true;
        }
        //daca nu e niciunul null
        else if(radacina->stang->prioritate < radacina->drept->prioritate){
            radacina = rotatieStanga(radacina);
            radacina->stang = stergere(radacina->stang,cheie, fl);
        }
        else{
            radacina = rotatieDreapta(radacina);
            radacina->drept = stergere(radacina->drept,cheie, fl);
        }
        return radacina;
    }
    void afis(nodTreap* radacina,ostream &out){
        if(radacina != NULL){
            afis(radacina->stang,out);
            out << "cheie: "<< radacina->cheie << " | prioritate: "<< radacina->prioritate;

            if(radacina->stang)
                out << "| fiu stang: " << radacina->stang->cheie;
            if(radacina->drept)
                out <<"| fiu drept: " << radacina->drept->cheie;
            out << '\n';
            afis(radacina->drept,out);
        }
    }
    nodTreap *maxim(nodTreap* radacina)
    {
        nodTreap* nod = radacina;
        while (nod->drept != NULL)
            nod = nod->drept;

        return (nod);
    }
    nodTreap *minim(nodTreap* radacina)
    {
        if(radacina==NULL) return NULL;
        nodTreap* nod = radacina;
        while (nod->stang != NULL)
            nod = nod->stang;

        return (nod);
    }

    int este_in(nodTreap* radacina, int x)
    {
        if(radacina == NULL)
            return 0;
        if(x == radacina->cheie)
            return 1;
        if(x > radacina->cheie)
            return este_in(radacina->drept,x);
        return este_in(radacina->stang,x);
    }


    nodTreap* succesor(nodTreap* radacina,nodTreap* nod){
        nodTreap*  succ = NULL;
        int x = nod->cheie;
        while(radacina != NULL){
            if (radacina->cheie == x+1) {
                succ = radacina;
            }
            if(x < radacina->cheie-1){
                succ = radacina;
                radacina = radacina->stang;
            }
            else if(x >= radacina->cheie)
                radacina = radacina->drept;
            else
                break;
        }

        return succ;
    }
    nodTreap* predecesor(nodTreap* radacina,nodTreap* nod){
        nodTreap* pred = NULL;
        int x = nod->cheie;
        while(1){
            if(x < radacina->cheie)
                radacina = radacina->stang;
            else if(x > radacina->cheie){
                pred = radacina;
                radacina = radacina->drept;
            }
            else{
                if(radacina->stang){
                    pred = maxim(radacina->stang);
                }
                break;
            }

            if(!radacina)
                return NULL;
        }
        return pred;
    }
    nodTreap* kMinim(nodTreap* radacina, int &k){
        if(radacina == NULL)
            return NULL;

        nodTreap* stanga = kMinim(radacina->stang,k);

        if(stanga != NULL)
            return stanga;

        --k;
        if(k==0)
            return radacina;
        else
            return kMinim(radacina->drept,k);
    }

};

//Functii de implementat:
void insereaza(Treap &treap, int x){
    treap.radacina = treap.inserare(treap.radacina,x);
}
void stergere(Treap &treap, int x){
    bool fl = false;
    treap.radacina = treap.stergere(treap.radacina,x, fl);
    if (fl) {
        treap.cardinal--;
        out << "Numarul " << x << " s-a sters din arbore.\n";
    }
    else {
        out << "Numarul " << x << " nu exista in arbore.\n";
    }
}
int min(Treap treap){
    nodTreap *nod = treap.minim(treap.radacina);
    return nod->cheie;
}
int max(Treap treap){
    nodTreap *nod = treap.maxim(treap.radacina);
    return nod->cheie;
}
int succesor(Treap treap, int x){
    nodTreap *nodx = treap.cautare(treap.radacina,x);
    if (nodx == NULL)
        return -2;
    nodTreap *nod = treap.succesor(treap.radacina, nodx);
    if(nod!=NULL)
        return nod->cheie;
    else
        return -1;
}
int predecesor(Treap treap, int x){
    nodTreap *nodx = treap.cautare(treap.radacina,x);
    if (nodx == NULL)
        return -2;
    nodTreap *nod = treap.predecesor(treap.radacina, nodx);
    if(nod != NULL)
        return nod->cheie;

    return -1;
}
int k_element(Treap treap, int k){
    nodTreap *nod = treap.kMinim(treap.radacina,k);
    if(nod != NULL)
        return nod->cheie;
    else
        return -1;
}
int cardinal(Treap treap){
    return treap.cardinal;
}
bool este_in(Treap treap, int x){
    return treap.este_in(treap.radacina,x);
}


int main() {
    srand(time(NULL));
    Treap treap;
    int x,y;
    while(in>>x)
    {
            /*
             0 - insereaza
             1 - sterge
             2 - min
             3 - max
             4 - succesor
             5 - predecesor
             6 - k_element
             7 - cardinal
             8 - este_in
             */
        switch(x)
        {
            case 0:{
                    in >> y;
                    insereaza(treap,y);
                    break;}
            case 1:{
                    in >> y;
                    stergere(treap,y);
                    break;}
            case 2:
                    out << "Minimul din treap este " << min(treap) << ".\n";
                    break;
            case 3:
                    out << "Maximul din treap este " << max(treap) << ".\n";
                    break;
            case 4:{
                    in >> y;
                    int nr = succesor(treap,y);
                    if(nr == -1)
                        out << "Numarul " << y << " nu are succesor.\n";
                    else if (nr == -2)
                        out << "Numarul " << y << " nu exista in arbore.\n";
                    else
                        out << "Succesorul lui " << y << " este " << nr <<".\n";
                    break;}
            case 5:{
                    in >> y;
                    int nr = predecesor(treap,y);
                    if(nr == -1)
                        out << "Numarul " << y << " nu are predecesor.\n";
                    else if (nr == -2)
                        out << "Numarul " << y << " nu exista in arbore.\n";
                    else
                        out << "Predecesorul lui " << y << " este " << nr << ".\n";
                    break;}
            case 6:{
                    in >> y;
                    int z = k_element(treap,y);
                    if(z == -1)
                        out << "Nu exista!\n";
                    else
                        out << "Elementul cu numarul de ordine " << y << " este " << z << ".\n";
                    break;}
            case 7:
                    out << "Cardinalul este " << cardinal(treap) << ".\n";
                    break;
            case 8:{
                    in >> y;
                    int z = este_in(treap,y);
                    if(z == 0)
                        out << "Elementul " << y << " nu este in treap.\n";
                    else
                        out << "Elementul " << y << " este in treap.\n";
                    break;}
            default:{
            break;}

             }
        }
    return 0;
}
