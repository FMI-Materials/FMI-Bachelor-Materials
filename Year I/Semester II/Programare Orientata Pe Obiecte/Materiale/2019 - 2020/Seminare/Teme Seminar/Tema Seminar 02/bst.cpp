#include "bst.hpp"

BST::BST() : root(NULL), size(0) { }

std::vector<int> BST::inordine(const BST& arb)
{
    std::stack <Node*> stk;
    std::vector <int> sol;

    Node* nod = arb.root;

    while (!stk.empty() || nod != NULL)
    {
        if (nod != NULL) {
            std::cout << nod->info << '\n';
            stk.push(nod);
            nod = nod->left;
        }
        else {
            Node* tt = stk.top();
            stk.pop();
            sol.push_back(tt->info);
            nod = tt->right;
        }
    }

    return sol;
}

void BST::insert(int val)
{
    if (root == NULL) {
        root = new Node(val);
        return;
    }

    Node* act = root;

    while (true) {
        if (act->info > val) {
            if (act->left == NULL) {
                act->left = new Node(val);
                size++;
                return;
            }
            act = act->left;
        }
        else {
            if (act->right == NULL) {
                act->right = new Node(val);
                size++;
                return;
            }
            act = act->right;
        }
    }
}

void BST::afisare()
{
    if(root == NULL)
        return;
    std::queue<Node*> q;
    q.push(root);
    while(q.empty() == false)
    {
        Node * f = q.front();
        q.pop();
        std::cout << f->info << "\n";

        if(f->left != NULL)
            q.push(f->left);
        if(f->right != NULL)
            q.push(f->right);
    }
}
bool BST::is_in(int val){
    if(root==NULL){
        return false;
    }
    Node* act = root;
    while(act!=NULL){
        if(act->info>val)
            act = act->left;
        else if(act->info<val)
            act = act->right;
        else
            return true;
    }
    return false;
}

BST BST :: operator + (const BST& tree)
{
    BST newtree;
    auto v1 = inordine(tree);
    auto v2 = inordine(*this);
    for (auto x : v1)
        newtree.insert(x);
    for (auto x : v2)
    {
        newtree.insert(x);
    }
    return newtree;
}



void BST::free_memory(){
    std::stack<Node> c;
    if(root==NULL) return;
    c.push(root);
    while(!c.empty()){
        Node* td = c.top();
        c.pop();
        if(td->left!=NULL)
            c.push(td.left)
        if(td->right!=NULL)
            c.push(td->right)
        delete td;
    }
    size = 0;
}

BST::~BST(){
    free_memory();
}

BST& BST::operator=(const BST& other){
    if(this==other) return *this;
    free_memory();

    std::vector<Node*> el = inordine(other);
    for(auto x: el)
        insert(x);

    size = other.size;

    return *this;
}
