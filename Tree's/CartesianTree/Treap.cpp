#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e10;

////////////////////////////////
////////////////////////////////
	typedef long long Tkey;/////
////////////////////////////////
////////////////////////////////

struct Node
{
	Tkey key;
	long long pr;
	Node* left;
	Node* right;
	size_t sz;
};

Node * BuildNewNode(Tkey key){
	return new Node{key,(rand() % MOD),nullptr,nullptr,1};
}

int getsz(Node * tree){
	if( !tree ){
		return 0;
	}
	else{
		return tree->sz;
	}
}

void recalc(Node * &tree){
	tree->sz = 1 + getsz(tree->left) + getsz(tree->right);
}

pair<Node *,Node *> split(Node * tree, Tkey x){

	if( !tree ){
		return make_pair( (Node*)nullptr,(Node*)nullptr );
	}
	if( tree->key <= x){
		pair<Node *,Node *> p = split(tree->right,x);
		tree->right = p.first;
		recalc(tree);
		return make_pair(tree,p.second);
	}
	else{
		pair<Node *,Node *> p = split(tree->left,x);
		tree->left = p.second;
		recalc(tree);
		return make_pair(p.first,tree);
	}

}

Node * merge(Node * l,Node * r){
	if( !l ){
		return r;
	}
	if( !r ){
		return l;
	}
	if( l->pr < r->pr ){
		l->right = merge(l->right,r);
		recalc(l);
		return l;
	}
	else{
		r->left = merge(l,r->left);
		recalc(r);
		return r;
	}
}

Node * insert(Node * tree,Tkey x){
	pair<Node *,Node*> p = split(tree,x);
	Node * tmp = BuildNewNode(x);
	return merge(p.first,merge(tmp,p.second));
}

Node * erase(Node * tree,Tkey x){
	pair<Node *,Node *> p = split(tree,x);
	pair<Node *,Node *> p2 = split(p.first,x - 1);
	delete(p2.second);
	return merge(p2.first,p.second);
}

void findKth(Node * &tree,size_t k,Tkey &answer){
	
	if(!tree){
		answer = MOD;
		return;
	}

	if( getsz(tree->left) >= k ){
		return findKth(tree->left,k,answer);
	}
	else if( getsz(tree->left) + 1 == k ){
		answer = tree->key;
		return ;
	}
	return findKth(tree->right, k - getsz(tree->left) - 1, answer);
}

bool findKey(Node * tree,Tkey x){

	if(!tree){
		return false;
	}
	else{
		bool answer;
		if( tree->key > x){
			answer = findKey(tree->left,x);
		}
		if( tree->key == x){
			answer = true;
		}
		if( tree->key < x){
			answer = findKey(tree->right,x);
		}
		return answer;
	}
}


/*

bool findLevel(Node * tree,Tkey x,size_t &level){

	if(!tree){
		return false;
	}
	else{
		bool answer;
		if( tree->key > x){
			answer = findLevel(tree->left,x,level);
		}
		if( tree->key == x){
			++level;
			answer = true;
		}
		if( tree->key < x){
			level = level + getsz(tree->left) + 1;
			answer = findLevel(tree->right,x,level);
		}
		return answer;
	}
}
*/

void findNext(Node * &tree,Tkey x){

	if(!tree){
		cout << "none\n";
		return;
	}

	pair<Node *,Node *> p = split(tree,x);
	Node * tmp = p.second;
	while ( tmp != nullptr && tmp->left != nullptr )
	{
		tmp = tmp->left;
	}
	if(tmp != nullptr){
		cout << tmp->key << "\n";
	}
	else{
		cout << "none\n";
	}
	tree = merge(p.first,p.second);
	return;
	
}

void findPrev(Node * &tree,Tkey x){

	if(!tree){
		cout << "none\n";
		return;
	}

	pair<Node *,Node *> p = split(tree,x - 1);
	Node * tmp = p.first;
	while ( tmp != nullptr && tmp->right != nullptr)
	{
		tmp = tmp->right;
	}
	if(tmp != nullptr){
		cout << tmp->key << "\n";
	}
	else{
		cout << "none\n";
	}
	tree = merge(p.first,p.second);
	return;

}

void print(Node * tree,int depth){

	if( tree == nullptr){
		return;
	}

	print(tree->left,depth + 4);
	for(int i = 0; i < depth; ++i){
		cout << " ";
	}
	cout << "(" << tree->key << ";" << tree->pr << ")\n";
	print(tree->right,depth + 4);

	return;

}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	string input;
	long long value;
	Node * root = nullptr;
	while( cin >> input ){

		cin >> value;
		switch (input[0]){

		case 'i':
			if( !findKey(root,value) ){
				root = insert(root,value);
			}
			break;

		case 'd':
			if( findKey(root,value) ){
				root = erase(root,value);
			}
			break;

		case 'e':
			cout << ( findKey(root,value) ? "true" : "false" ) << "\n";
			break;

		case 'n':
			findNext(root,value);
			break;

		case 'p':
			findPrev(root,value);
			break;

		case 'k':
			Tkey answer;
			findKth(root,value,answer);
			if( answer == MOD ){
				cout << "none\n";
			}
			else{
				cout << answer << "\n";
			}
			break;
		
		}

		//print(root,0);
	}
	
	return 0;	  
	  
}
