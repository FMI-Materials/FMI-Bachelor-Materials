/*Patranjel David-George 151*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <stack>

using namespace std;
///We use thin -infinity value for the preorder function
const int mininf = -99999999;
///Here we have declared our structure that will store a sorted vector v and an integer s
struct Structura{
    vector<int> v;
    int s;
}structura;

bool empty(){
    ///This function returns false if the structura was not initialized, otherwise it returns true
    if(structura.v.empty()) return true;
    return false;
}

void init(const vector<int>& v, int s){
    ///We initialiaz the structure and sort the vector in O(nlogn) for future queries
    structura.v = v;
    structura.s = s;
    make_heap(structura.v.begin(), structura.v.end());
    sort_heap(structura.v.begin(), structura.v.end());
}

int set(int i){
    if(empty()) throw(0);
    if(i < 0) return 0;
    ///We save a copy of the initial number to check in the end if we passed the MSB
    int copy = structura.s;
    ///By using bit shifting, we save in b the value of the i-th bit
    int b = (structura.s & (1 << i)) >> i;
    ///We prepare the change of the value of the i-th bit by changing b (from 0 to 1 and vice versa)
    if(b==1) b = 0;
    else b = 1;
    ///Since we need to change the i-th bit, we first need to delete the i-th bit.
    ///Therefore, we create a mask with a 1 on the i-th position
    int mask = 1 << i;
    ///By negating the mask ,we obtain 11...101...11, with 0 on the i-th position. By making an AND operation, we make the i-th bit = 0
    structura.s = structura.s & ~mask;
    ///Now, we can use our b to make another mask, by placing the new value of the i-th bit on the coresponding position. By making an OR operation we have modified the i-th bit
    structura.s = structura.s | (b<<(i));
    ///Here, we check to see if we didnt pass over the MSB
    if(structura.s/2 >=  copy){
        structura.s = copy;
        return 0;
    }
    return 1;
}

int count(){
    ///Since our array v is sorted, we can do a BinarySearch(O(nlogn)) to find the first last element that is smaller than s
    if(empty()) throw(0);
    int left = 0, right = structura.v.size()-1, mid;
    if(structura.s <= structura.v[0]) return 0;
    else if(structura.s > structura.v[structura.v.size()-1]) return structura.v.size();
    while(left<=right){
        ///We find the midpoint
        mid = left + (right-left)/2;
        if(structura.v[mid] < structura.s && structura.v[mid+1] >= structura.s) return mid+1;
        else if(structura.v[mid+1] >= structura.s) right = mid-1;
        else left = mid + 1;
    }
    return mid+1;
    return 0;
}

void Exercitiu1(){
    try{
        vector<int> v{9,7,7,3,1,2,7,3,6,1};
        int s = 5;
        init(v,s);
        for(auto i:structura.v){
            cout<<i<<" ";
        }
        cout<<endl;
        cout<<count()<<endl;
        if(set(1))
            cout<<structura.s<<endl;
    }catch(int){
        cout<<"Error. Please initialize the structure\n";
    }
}

bool isUVector(const vector<int>& v){
    ///To be able to find if the elements are all pairwise different we can use a hash table.
    ///We go from left to right through the vector v.
    ///If we find the element in the hash table in O(1), then we have a duplicate (return false)
    ///If we dont find the element in the hash table, than we add it to the hash table
    unordered_map<int,bool> h;
    for(auto i:v){
        if(h.find(i) == h.end())
            h[i] = true;
        else return false;
    }
    return true;
}

bool isInOrder(const vector<int>& v){
    ///For a vector to be inorder for a BBST it means that it is ordered ascending.
    if(!isUVector) return false;
    for(int i = 1; i < v.size(); i++){
        if(v[i] < v[i-1])
            return false;
    }
    return true;
}

bool isPreOrder(const vector<int>& v){
    ///To check if a vector is in preorder, we have to simulate the DFS backwards with a stack.
    if(!isUVector) return false;
    stack<int> s;
    int radacina = mininf;
    for(auto i:v){
        ///If we meet an element that is smaller than our root, it means that we dont have a PreOrder vector
        if(i < radacina) return false;
        while(!s.empty() && s.top()<i){
            radacina = s.top();
            s.pop();
        }
        s.push(i);
    }
    return true;
}

bool isPreOrderSecond(const vector<int>& v){
    if(!isUVector) return false;
    vector<int> aux;
    stack<int> s;
    int radacina = mininf;
    for(auto i:v){
        if(i < radacina) return false;
        while(!s.empty() && s.top()<i){
            radacina = s.top();
            aux.push_back(radacina);
            ///I've added the line from above because when we pop elements from the stack we actually obtain the sorted vector
            s.pop();
        }
        s.push(i);
    }
    ///If we still have elements on the stack, they are ordered and we can insert them in the vector
    while(!s.empty()){
        radacina = s.top();
        aux.push_back(radacina);
        s.pop();
    }
    ///Printing the sorted array
    for(auto i:aux)
        cout<<i<<" ";
    cout<<endl;
    return true;
}

void Exercitiu2(){
    vector<int> v{25, 15, 10, 4, 12, 22, 18, 24, 50, 35, 31, 41, 70, 66, 90};
    cout<<isUVector(v)<<endl<<isPreOrderSecond(v);
}

int main()
{
    cout<<"---Exercitiu1---"<<endl;
    Exercitiu1();
    cout<<"---Exercitiu2---"<<endl;
    Exercitiu2();
    return 0;
}
