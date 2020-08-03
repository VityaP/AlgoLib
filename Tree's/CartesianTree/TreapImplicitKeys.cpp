#include <bits/stdc++.h>
using namespace std;

//I use it for random generating
const int MOD = 1e9 + 7;
const long long MAX = 1e13;

struct Node{

	int pr;
	long long value;
	long long sum;
	long long min;
	int size;
	bool isRev;
	bool isAssigned;
	long long assigned;
	Node *left;
	Node *right;

	Node(long long v){
		pr = rand() % MOD;
		value = v;
		sum = v;
		min = v;
		size = 1;
		isRev = false;
		isAssigned = false;
		assigned = 0;
		left = nullptr;
		right = nullptr;
	};

};

Node * buildNewNode(long long value){
	return new Node(value);
}

int getSize(Node * tree){
	
	if(!tree){
		return 0;
	}
	return tree->size;
}

void recalcSize(Node * tree){
	//assert(!tree);
	if(!tree){
		return;
	}
	tree->size = getSize(tree->left) + getSize(tree->right) + 1 ;
}

long long getSum(Node * tree){
	if(!tree){
		return 0;
	}
	return tree->sum;
}

void recalcSum(Node * tree){
	//assert(!tree);
	if(!tree){
		return;
	}
	tree->sum = getSum(tree->left) + getSum(tree->right) + tree->value;
}

long long getMin(Node * tree){
	if(!tree){
		return MAX;
	}
	return tree->min;
}

void recalcMin(Node * tree){
	//assert(!tree);
	if(!tree){
		return;
	}
	tree->min = min(tree->value , min(getMin(tree->left) , getMin(tree->right)));
}

void recalcAll(Node * tree){
	
	recalcSize(tree);
	recalcSum(tree);
	recalcMin(tree);
	
}

void assignedONTree(Node * tree,long long v){
	
	if(!tree){
		return;
	}
	tree->isAssigned;
	tree->assigned = v;
	tree->value = v;
	tree->sum = v * tree->size;
	tree->min = v;
	
}

void reverseONTree(Node * tree){
	if(!tree){
		return;
	}
	tree->isRev ^= 1;
	swap(tree->left,tree->right);
	return;
}

void push(Node * tree){
	if(!tree){
		return;
	}
	if(tree->isAssigned){
		assignedONTree(tree->left,tree->assigned);
		assignedONTree(tree->right,tree->assigned);
		tree->isAssigned = false;
	}
	if(tree->isRev){
		reverseONTree(tree->left);
		reverseONTree(tree->right);
		tree->isRev = false;
	}
	return;
}


pair<Node *,Node *> splitBySize(Node * tree,int k){
	if( k == 0){
		return make_pair((Node *)nullptr, tree);
	}
	push(tree);
	if(getSize(tree->left) >= k){
		pair<Node *,Node *> p = splitBySize(tree->left,k);
		tree->left = p.second;
		recalcAll(tree);
		return make_pair(p.first,tree);
	}
	else{
		pair<Node *,Node *> p = splitBySize(tree->right,k - getSize(tree->left) - 1);
		tree->right = p.first;
		recalcAll(tree);
		return make_pair(tree,p.second);
	}
	
}


Node * merge(Node * l,Node * r){
	if(!l){
		return r;
	}
	if(!r){
		return l;
	}
	if(l->pr < r->pr){
		push(l);
		l->right = merge(l->right,r);
		recalcAll(l);
		return l;
	}
	else{
		push(r);
		r->left = merge(l,r->left);
		recalcAll(r);
		return r;
	}
	
}

long long findSum(Node * &tree,int l,int r){
	
	//l < r must be
	pair<Node *,Node *> p = splitBySize(tree,l - 1);
	pair<Node *,Node *> p2 = splitBySize(p.second,r - l + 1);
	long long sum = getSum(p2.first);
	tree = merge(p.first, merge(p2.first,p2.second) );
	return sum;
	
}

long long findMin(Node * &tree,int l,int r){
	
	//l < r must be
	pair<Node *,Node *> p = splitBySize(tree,l - 1);
	pair<Node *,Node *> p2 = splitBySize(p.second,r - l + 1);
	long long min = getMin(p2.first);
	tree = merge(p.first, merge(p2.first,p2.second) );
	return min;
	
}

Node * rotate(Node * tree,int k){
	
	// Check if k < then tree->sz;
	// if no then k = k % tree->sz;
	pair<Node *,Node *> p = splitBySize(tree,k);
	return merge(p.second,p.first);
	
}
	
void print(Node * tree,int depth){

	if( tree == nullptr){
		return;
	}
	print(tree->left,depth + 4);
	for(int i = 0; i < depth; ++i){
		cout << " ";
	}
	cout << "(" << tree->value << "; min = "<< tree->min << ")\n";
	print(tree->right,depth + 4);

	return;

}

void taskA28September(Node * &tree,int l,int r){
	
	//l < r must be
	pair<Node *,Node *> p = splitBySize(tree,l - 1);
	pair<Node *,Node *> p2 = splitBySize(p.second,r - l + 1);
	tree = merge(p2.first, merge(p.first,p2.second) );
	
}

int main( ){
	
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	
	int n;
	cin >> n;
	Node * root = nullptr;
	char comand;
	int f,s;
	for(int i = 0;i < n; ++i){
		cin >> comand;
		switch (comand)
		{
		case '?':
			cin >> f >> s;
			cout << findMin(root,f,s) << "\n";
			break;

		case '+':
			cin >> f >> s;
			if ( f == 0){
				Node * tmp;
				tmp = buildNewNode(s);
				root = merge(tmp,root);
			}
			else{
				pair<Node *, Node *> p = splitBySize(root,f);
				Node * tmp;
				tmp = buildNewNode(s);
				root = merge(p.first,merge(tmp,p.second));
			}
			//print(root,0);
			//cout << "-----------\n";
			break;
		}
	}
	
	return 0;
}