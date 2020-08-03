#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node{
    long long key;
    node* l;
    node* r;
    node* p;
    bool color;
};

#define BLACK_RBTREE_COLOR false
#define RED_RBTREE_COLOR true

node* NIL;

void InitializeNil(){
    NIL = new node;
    NIL->l = NIL;
    NIL->r = NIL;
    NIL->p = NIL;
    NIL->color = BLACK_RBTREE_COLOR;
    return;
}


node* TreeSearh(node* x, long long k){
    if( x == NIL || x->key == k){
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
    while( (x != NIL) || (x->key != k)){
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
    while( x->l != NIL ){
        x = x->l;
    }
    return x;
}

node* TreeMax(node* T){
    node* x = T;
    while( x->r != NIL ){
        x = x->r;
    }
    return x;
}

node* TreeSuccessor(node* T){
    node* x = T;
    if( x->r != NIL){
        return TreeMin(x->r);
    }
    node* y = x->p;
    while( y != NIL && x == y->r){
        x = y;
        y = y->p;
    }
    return y;
}

node* TreePredecessor(node* T){
    node* x = T;
    if(x->l != NIL){
        return TreeMax(x->l);
    }
    node* y = x->p;
    while( y != NIL && x == y->l){
        x = y;
        y = y->p;
    }
    return y;
}

void TreePrint(node* T, int shift = 0){
    if(T == NIL){
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

//RBTREE

node* LeftRotate(node* T, node* up){
    if( (up == NIL) || (up->r == NIL) || (T->p != NIL) ){
        cout << "SHIT!\n";
        return T;
    }
    node* down = up->r;
    up->r = down->l;
    if( down->l != NIL ){
        down->l->p = up;
    }
    down->p = up->p;
    if( up->p == NIL ){
        T = down;
        //new root
    }
    else{
        if( up == up->p->l ){
            up->p->l = down;
        }
        else{
            up->p->r = down;
        }
    }
    down->l = up;
    up->p = down;
    return T;
}

node* RightRotate(node* T, node* up){
    if( (up == NIL) || (up->l == NIL) || (T->p != NIL) ){
        cout << "SHIT!\n";
        return T;
    }
    node* down = up->l;
    up->l = down->r;
    if( down->r != NIL ){
        down->r->p = up;
    }
    down->p = up->p;
    if( up->p == NIL ){
        T = down;
        //new root
    }
    else{
        if( up == up->p->l ){
            up->p->l = down;
        }
        else{
            up->p->r = down;
        }
    }
    down->r = up;
    up->p = down;
    return T;
}

node* RBTreeInsertFixup(node* T, node* z){
    if( T == NIL || z == NIL ){
        cout << "SHIT!\n";
        return T;
    }
    while( z->p->color == RED_RBTREE_COLOR ){
        if( z->p == z->p->p->l ){
            node* y = z->p->p->r;
            if( y->color == RED_RBTREE_COLOR ){
                //uncle RED
                z->p->color = BLACK_RBTREE_COLOR;
                y->color = BLACK_RBTREE_COLOR;
                z->p->p->color = RED_RBTREE_COLOR;
                z = z->p->p;
            }
            else{
                if( z == z->p->r ){
                    z = z->p;
                    T = LeftRotate(T, z);
                }
                z->p->color = BLACK_RBTREE_COLOR;
                z->p->p->color = RED_RBTREE_COLOR;
                T = RightRotate(T, z->p->p);
            }
        }
        else{
            node* y = z->p->p->l;
            if( y->color == RED_RBTREE_COLOR ){
                //uncle RED
                z->p->color = BLACK_RBTREE_COLOR;
                y->color = BLACK_RBTREE_COLOR;
                z->p->p->color = RED_RBTREE_COLOR;
                z = z->p->p;
            }
            else{
                if( z == z->p->l ){
                    z = z->p;
                    T = RightRotate(T, z);
                }
                z->p->color = BLACK_RBTREE_COLOR;
                z->p->p->color = RED_RBTREE_COLOR;
                T = LeftRotate(T, z->p->p);
            }
        }
    }
    T->color = BLACK_RBTREE_COLOR;
    return T;
}

node* RBTreeInsert(node* T, node* z){
    if( T == NIL ){
        T = z;
        T->color = BLACK_RBTREE_COLOR;
        return T;
    }
    node* y = NIL;
    node* x = T;
    while( x != NIL){
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
    T = RBTreeInsertFixup(T, z);
    return T;
}

node* RBTransplant(node* T, node* oldElement, node* newElement){

    node* parent = oldElement->p;
    if( parent == NIL){
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
    newElement->p = parent;
    return T;
}

node* RBTreeDeleteFixup(node* T, node* x){

    while( x != T && x->color == BLACK_RBTREE_COLOR ){
        if( x == x->p->l ){
            node* w = x->p->r;
            if( w->color == RED_RBTREE_COLOR ){
                w->color = BLACK_RBTREE_COLOR;
                x->p->color = RED_RBTREE_COLOR;
                T = LeftRotate(T, x->p);
                w = x->p->r;
            }
            if( w->l->color == BLACK_RBTREE_COLOR && w->r->color == BLACK_RBTREE_COLOR ){
                w->color = RED_RBTREE_COLOR;
                x = x->p;
            }
            else{
                if( w->r->color == BLACK_RBTREE_COLOR ){
                    w->l->color = BLACK_RBTREE_COLOR;
                    w->color = RED_RBTREE_COLOR;
                    T = RightRotate(T, w);
                    w = x->p->r;
                }
                w->color = x->p->color;
                x->p->color = BLACK_RBTREE_COLOR;
                w->r->color = BLACK_RBTREE_COLOR;
                T = LeftRotate(T, x->p);
                x = T;
            }
        }
        else{
            //
            node* w = x->p->l;
            if( w->color == RED_RBTREE_COLOR ){
                w->color = BLACK_RBTREE_COLOR;
                x->p->color = RED_RBTREE_COLOR;
                T = RightRotate(T, x->p);
                w = x->p->l;
            }
            if( w->r->color == BLACK_RBTREE_COLOR && w->l->color == BLACK_RBTREE_COLOR ){
                w->color = RED_RBTREE_COLOR;
                x = x->p;
            }
            else{
                if( w->l->color == BLACK_RBTREE_COLOR ){
                    w->r->color = BLACK_RBTREE_COLOR;
                    w->color = RED_RBTREE_COLOR;
                    T = LeftRotate(T, w);
                    w = x->p->l;
                }
                w->color = x->p->color;
                x->p->color = BLACK_RBTREE_COLOR;
                w->l->color = BLACK_RBTREE_COLOR;
                T = RightRotate(T, x->p);
                x = T;
            }
            //
        }
    }

    x->color = BLACK_RBTREE_COLOR;
    return T;
}

node* RBTreeDelete(node* T, node* z){
    node* y = z;
    node* x;
    bool yOriginalColor = y->color;
    if( z->l == NIL){
        x = z->r;
        T = RBTransplant(T, z, z->r);
    }
    else{
        if( z->r == NIL){
            x = z->l;
            T = RBTransplant(T, z, z->l);
        }
        else{
            node* y = TreeMin(z->r);
            yOriginalColor = y->color;
            x = y->r;
            if( y->p == z){
                x->p = y;
            }
            else{
                T = RBTransplant(T, y, y->r);
                y->r = z->r;
                y->r->p = y;
            }
            T = RBTransplant(T, z, y);
            y->l = z->l;
            y->l->p = y;
            y->color = z->color;
        }
    }
    if( yOriginalColor == BLACK_RBTREE_COLOR ){
        T = RBTreeDeleteFixup(T, x);
    }
    return T;
}



//RBTREE





int main(){

    // std::ios_base::sync_with_stdio(false);
	// std::cin.tie(NULL);

    
    InitializeNil();
    node* root = NIL;

    string s;
    while(std::cin >> s){
        
        if(s[0] == 'i'){
            long long value;
            cin >> value;
            node* tmp = TreeSearh(root, value);
            if( tmp == NIL){
                node* newNode = new node;
                newNode->key = value;
                newNode->l = NIL;
                newNode->r = NIL;
                newNode->p = NIL;
                newNode->color = RED_RBTREE_COLOR;
                root = RBTreeInsert(root, newNode);
            }
            //insert value
        }
        if(s[0] == 'd'){
            long long value;
            cin >> value;
            node* tmp = TreeSearh(root, value);
            if( tmp != NIL){
                root = RBTreeDelete(root, tmp);
            }
            //delete value
        }
        if(s[0] == 'e'){
            long long value;
            cin >> value;
            node* tmp = TreeSearh(root, value);
            if( tmp == NIL){
                cout << "false\n";
            }
            else{
                cout << "true\n";
            }
            //search value
        }
        if(s[0] == 'p'){
            TreePrint(root);
        }
        if(s[0] == 'l'){
            long long value;
            cin >> value;
            node* tmp = TreeSearh(root, value);
            if( tmp != NIL ){
                root = LeftRotate(root, tmp);
                TreePrint(root);
            }
        }
        if(s[0] == 'r'){
            long long value;
            cin >> value;
            node* tmp = TreeSearh(root, value);
            if( tmp != NIL ){
                root = RightRotate(root, tmp);
                TreePrint(root);
            }
        }

    }



    return 0;
}