#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//TREE

struct node{
    long long key;
    node* l;
    node* r;
    node* p;
};



node* TreeSearh(node* x, long long k){
    if( x == nullptr || x->key == k){
        return x;
    }
    if( x->key > k){
        return TreeSearh(x->l, k);
    }
    else{
        return TreeSearh(x->r, k);
    }
}

node* IterativeTreeSearh(node* T, long long k){
    node* x = T;
    while( (x != nullptr) || (x->key != k)){
        if( x->key > k){
            x = x->l;
        }
        else{
            x = x->r;
        }
    }
    return x;
}

node* TreeMin(node* T){
    node* x = T;
    while( x->l != nullptr ){
        x = x->l;
    }
    return x;
}

node* TreeMax(node* T){
    node* x = T;
    while( x->r != nullptr ){
        x = x->r;
    }
    return x;
}

node* TreeSuccessor(node* T){
    node* x = T;
    if( x->r != nullptr){
        return TreeMin(x->r);
    }
    node* y = x->p;
    while( y != nullptr && x == y->r){
        x = y;
        y = y->p;
    }
    return y;
}

node* TreePredecessor(node* T){
    node* x = T;
    if(x->l != nullptr){
        return TreeMax(x->l);
    }
    node* y = x->p;
    while( y != nullptr && x == y->l){
        x = y;
        y = y->p;
    }
    return y;
}

node* TreeInsert(node* T, node* z){
    if( T == nullptr ){
        T = z;
        return T;
    }
    node* y = nullptr;
    node* x = T;
    while( x != nullptr){
        y = x;
        if( z->key < x->key){
            x = x->l;
        }
        else{
            x = x->r;
        }
    }
    z->p = y;

    if(z->key < y->key){
        y->l = z;
    }
    else{
        y->r = z;
    }
    return T;
    
}

node* Transplant(node* T, node* oldElement, node* newElement){

    node* parent = oldElement->p;
    if( parent == nullptr){
        T = newElement;
    }
    else{
        if( parent->l == oldElement ){
            parent->l = newElement;
        }
        else{
            parent->r = newElement;
        }
    }
    if( newElement != nullptr ){
        newElement->p = parent;
    }
    return T;
}

node* TreeDelete(node* T, node* z){
    if( z->l == nullptr){
        T = Transplant(T, z, z->r);
    }
    else{
        if( z->r == nullptr){
            T = Transplant(T, z, z->l);
        }
        else{
            node* y = TreeMin(z->r);
            if( y->p != z){
                T = Transplant(T, y, y->r);
                y->r = z->r;
                y->r->p = y;
            }
            T = Transplant(T, z, y);
            y->l = z->l;
            y->l->p = y;
        }
    }
    return T;
}

void TreePrint(node* T, int shift = 0){
    if(T == nullptr){
        return;
    }
    TreePrint(T->l, shift + 3);
    for(int i = 0; i < shift; ++i){
        cout << " ";
    }
    cout << T->key << "\n";
    TreePrint(T->r, shift + 3);
}


//TREE





int main(){

    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    node* BST = nullptr;

    string s;
    while(std::cin >> s){
        
        if(s[0] == 'i'){
            long long value;
            cin >> value;
            node* tmp = TreeSearh(BST, value);
            if( tmp == nullptr){
                node* newNode = new node;
                newNode->key = value;
                newNode->l = nullptr;
                newNode->r = nullptr;
                newNode->p = nullptr;
                BST = TreeInsert(BST, newNode);
            }
            //insert value
        }
        if(s[0] == 'd'){
            long long value;
            cin >> value;
            node* tmp = TreeSearh(BST, value);
            if( tmp != nullptr){
                BST = TreeDelete(BST, tmp);
            }
            //delete value
        }
        if(s[0] == 'e'){
            long long value;
            cin >> value;
            node* tmp = TreeSearh(BST, value);
            if( tmp == nullptr){
                cout << "false\n";
            }
            else{
                cout << "true\n";
            }
            //search value
        }
        if(s[0] == 'p'){
            TreePrint(BST);
        }

    }



    return 0;
}