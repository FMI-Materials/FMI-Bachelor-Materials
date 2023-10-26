#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

ifstream fin("abce.in");
ofstream fout("abce.out");

class Node{
private:
    void splitChild(int, Node*);

    void borrowFromPrev(int);
    void borrowFromNext(int);

    void merge(int);
    void fill(int);

    int getPred(int);
    int getSucc(int);

    void removeFromLeaf(int);
    void removeFromNonLeaf(int);

protected:
    std::vector<int> keys;
    std::vector<Node*> childs;

    const int t;
    int n;
    bool isLeaf;
public:

    explicit Node(int = 3, bool = true);

    void traverse(std::vector<int>&);
    void traverse(std::vector<int>&, int, int);
    int search(int);
    int search_lower(int, int = 0);
    int search_upper(int, int = 0);
    bool contains(int);

    bool isFull();

    void appendChild(int);
    void removeChild(int);

    friend class BTree;
};

class BTree{
    Node *root; // Pointer to root node
    const int t;  // Minimum degree
public:
    BTree(int = 3);

    int search(int, bool);
    int search(int);
    bool contains(int);
    std::vector<int> traverse();
    std::vector<int> traverse(int, int);
    void print(const std::string& = " ");
    void print(int, int, const std::string& = " ");

    void insert(int);
    void insert(std::vector<int>);
    void remove(int);
};

Node::Node(int t, bool isLeaf): t(t), isLeaf(isLeaf), n(0){
    keys.resize(2*t+1);
    childs.resize(2*t);
}

void Node::removeChild(int x){

    int idx=0;
    while (idx<n && keys[idx] < x)
        ++idx;

    if (idx < n && keys[idx] == x){
        if (isLeaf) removeFromLeaf(idx);
        else removeFromNonLeaf(idx);
    }
    else{
        if (isLeaf) return;

        bool flag = (idx==n);
        if (childs[idx]->n < t)
            fill(idx);

        if (flag && idx > n)
            idx--;
        childs[idx]->removeChild(x);
    }
}

bool Node::isFull(){
    return n == t*2-1;
}

void Node::removeFromLeaf (int idx){
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];
    n--;
}

void Node::removeFromNonLeaf(int idx){
    int x = keys[idx];

    if (childs[idx]->n >= t){
        int pred = getPred(idx);
        keys[idx] = pred;
        childs[idx]->removeChild(pred);
    }
    else if  (childs[idx+1]->n >= t){
        int succ = getSucc(idx);
        keys[idx] = succ;
        childs[idx+1]->removeChild(succ);
    }
    else{
        merge(idx);
        childs[idx]->removeChild(x);
    }
}

int Node::getPred(int idx){
    Node *cur=childs[idx];
    while (!cur->isLeaf)
        cur = cur->childs[cur->n];

    return cur->keys[cur->n-1];
}

int Node::getSucc(int idx){
    Node *cur = childs[idx+1];
    while (!cur->isLeaf)
        cur = cur->childs[0];

    return cur->keys[0];
}

void Node::fill(int idx){
    if (idx!=0 && childs[idx-1]->n>=t)
        borrowFromPrev(idx);
    else if (idx!=n && childs[idx+1]->n>=t)
        borrowFromNext(idx);
    else{
        if (idx != n)
            merge(idx);
        else
            merge(idx-1);
    }
}

void Node::borrowFromPrev(int idx){
    Node *child=childs[idx];
    Node *sibling=childs[idx-1];

    for (int i=child->n-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];

    if (!child->isLeaf)
        for(int i=child->n; i>=0; --i)
            child->childs[i+1] = child->childs[i];

    child->keys[0] = keys[idx-1];

    if(!child->isLeaf)
        child->childs[0] = sibling->childs[sibling->n];

    keys[idx-1] = sibling->keys[sibling->n-1];

    child->n++;
    sibling->n--;
}

void Node::borrowFromNext(int idx){
    Node *child=childs[idx];
    Node *sibling=childs[idx+1];

    child->keys[(child->n)] = keys[idx];

    if (!(child->isLeaf))
        child->childs[(child->n)+1] = sibling->childs[0];

    keys[idx] = sibling->keys[0];

    for (int i=1; i<sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];

    if (!sibling->isLeaf)
        for(int i=1; i<=sibling->n; ++i)
            sibling->childs[i-1] = sibling->childs[i];

    child->n++;
    sibling->n--;
}

void Node::merge(int idx){
    Node *child = childs[idx];
    Node *sibling = childs[idx+1];

    child->keys[t-1] = keys[idx];

    for (int i=0; i<sibling->n; ++i)
        child->keys[i+t] = sibling->keys[i];

    if (!child->isLeaf)
        for(int i=0; i<=sibling->n; ++i)
            child->childs[i+t] = sibling->childs[i];

    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];

    for (int i=idx+2; i<=n; ++i)
        childs[i-1] = childs[i];

    child->n += sibling->n+1;
    n--;

    delete(sibling);
}

void BTree::insert(int x){
    if (root == nullptr){
        root = new Node(t, true);
        root->keys[0] = x;
        root->n = 1;
        return;
    }
    if (root->isFull()){
        Node *s = new Node(t, false);

        s->childs[0] = root;
        s->splitChild(0, root);

        int i = 0;
        if (s->keys[0] < x)
            i++;
        s->childs[i]->appendChild(x);

        root = s;
        return;
    }
    root->appendChild(x);
}

void BTree::insert(vector<int> values){
    for(auto x: values)
        insert(x);
}

void Node::appendChild(int x){
    int i = n-1;

    if (isLeaf){
        while (i >= 0 && keys[i] > x){
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = x;
        n++;
        return;
    }
    while (i >= 0 && keys[i] > x)
        i--;
    i++;
    if (childs[i]->isFull()){
        splitChild(i, childs[i]);
        if (keys[i] < x) i++;
    }
    childs[i]->appendChild(x);
}

void Node::splitChild(int i, Node *y){
    Node *z = new Node(y->t, y->isLeaf);
    z->n = t - 1;

    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];

    if (!y->isLeaf)
        for (int j = 0; j < t; j++)
            z->childs[j] = y->childs[j+t];

    y->n = t - 1;

    for (int j = n; j >= i+1; j--)
        childs[j+1] = childs[j];

    childs[i+1] = z;

    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
    keys[i] = y->keys[t-1];

    n++;
}

void Node::traverse(vector<int> &values){
    int i;
    for (i = 0; i < n; i++){
        if (!isLeaf)
            childs[i]->traverse(values);
        values.push_back(keys[i]);
    }
    if (!isLeaf) childs[i]->traverse(values);
}

void Node::traverse(vector<int> &values, int x, int y){
    int i;
    for (i = 0; i < n; i++){
        if (!isLeaf)
            childs[i]->traverse(values, x, y);
        if(keys[i]>=x && keys[i]<=y)
            values.push_back(keys[i]);
    }
    if (!isLeaf) childs[i]->traverse(values, x, y);
}

int Node::search(int x){
    int i = 0;
    while (i < n && x > keys[i])
        i++;
    if (keys[i] == x)
        return keys[i];
    if (isLeaf)
        return 0;
    return childs[i]->search(x);
}

BTree::BTree(int t): root(nullptr), t(t){}

int BTree::search(int x){
    if(root== nullptr) return 0;
    return root->search(x);
}

bool BTree::contains(int x){
    if(root == nullptr) return false;
    return root->contains(x);
}

int BTree::search(int x, bool lower){
    if(root == nullptr) return 0;
    if(lower) return root->search_lower(x);
    return root->search_upper(x);
}

void BTree::remove(int x){
    root->removeChild(x);

    if (root->n==0){
        Node *tmp = root;
        if (root->isLeaf)
            root = NULL;
        else
            root = root->childs[0];
        delete tmp;
    }
}

vector<int> BTree::traverse() {
    vector<int> values;
    if(root!= nullptr)
        root->traverse(values);
    return values;
}

vector<int> BTree::traverse(int x, int y) {
    vector<int> values;
    if(root!= nullptr)
        root->traverse(values, x, y);
    return values;
}

void BTree::print(const string& sep) {
    vector<int> values = traverse();
    bool alpha = false;
    for(auto x: values){
        if(alpha) fout<<sep;
        alpha = true;
        fout<<x;
    }
    fout<<'\n';
}

void BTree::print(int x, int y, const string& sep) {
    vector<int> values = traverse(x, y);
    bool alpha = false;
    for(auto x: values){
        if(alpha) fout<<sep;
        alpha = true;
        fout<<x;
    }
    fout<<'\n';
}

bool Node::contains(int x) {
    int i=0;
    while(i<n && x>keys[i])
        ++i;
    if(i<n && keys[i]==x)
        return true;
    if(isLeaf)
        return false;
    return childs[i]->contains(x);
}

int Node::search_upper(int x, int last){
    int i = 0;
    while (i < n && x > keys[i])
        i++;
    if (i<n) {
        if (keys[i] == x) return keys[i];
        last = keys[i];
    }
    if (isLeaf)
        return last;

    return childs[i]->search_upper(x, last);
}

int Node::search_lower(int x, int last){
    int i = 0;
    while (i < n && x > keys[i])
        i++;
    if(i<n){
        if (keys[i] == x) return keys[i];
    }
    if(i>0) last = keys[i-1];
    if (isLeaf)
        return last;

    return childs[i]->search_lower(x, last);
}

void execute(BTree *b, int op, int x, int y = 0){
    if(op==1)
        b->insert(x);
    if(op==2)
        b->remove(x);
    if(op==3)
        fout<<(int)b->contains(x)<<'\n';
    if(op==4)
        fout<<b->search(x, true)<<'\n';
    if(op==5)
        fout<<b->search(x, false)<<'\n';
    if(op==6)
        b->print(x, y);
}

int main() {

    int n, op, x, y;
    BTree b(3);

    fin>>n;
    while(n--){
        fin>>op>>x;
        if(op==6) fin>>y;
        execute(&b, op, x, y);
    }

    return 0;
}