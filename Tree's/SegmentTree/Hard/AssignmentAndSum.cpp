#include <bits/stdc++.h>
using namespace std;

// const long long MOD = 1e9 + 7;

struct MySegmentTree{

    long long sizeTree;

    struct node{
        long long sum;
        long long set;
    };

    vector<node> tree;

    long long NO_OPERATION = LLONG_MIN;
    long long NEUTRAL_ELEMENT = 0;

    long long op_modify(long long &a, long long &b, long long len){
        if( b == NO_OPERATION){
            return a;
        }
        else{
            return b * len;
        }
    }

    long long op_sum(long long &a, long long &b){
        return a + b;
    }

    void init(long long n){
        sizeTree = 1;
        while( sizeTree < n){
            sizeTree *= 2;
        }
        tree.assign(2*sizeTree - 1, {0, 0});
        // or
        // tree.resize(2*sizeTree - 1);
    }

    // void build(vector<long long> &a, long long x, long long lx, long long rx){
    //     if( rx - lx == 1){
    //         if( lx < a.size() ){
    //             tree[x] = {a[lx], NO_OPERATION};
    //         }
    //     }
    //     else{
    //         long long mid = (lx + rx)/2;
    //         build(a, 2*x + 1, lx, mid);
    //         build(a, 2*x + 2, mid, rx);
    //         tree[x] = {op_sum(tree[2*x + 1].sum, tree[2*x + 2].sum), NO_OPERATION};
    //     }
    // }

    void build(vector<long long> &a){
        init(a.size());
        // build(a, 0, 0, sizeTree);
    }

    void push(int x, int lx, int rx){
        if( (tree[x].set == NO_OPERATION) || (rx - lx == 1) ){
            return;
        }
        int mid = (lx + rx) / 2;
        tree[2*x + 1].set = op_modify(tree[2*x + 1].set, tree[x].set, 1);
        tree[2*x + 1].sum = op_modify(tree[2*x + 1].sum, tree[x].set, mid - lx);
        tree[2*x + 2].set = op_modify(tree[2*x + 2].set, tree[x].set, 1);
        tree[2*x + 2].sum = op_modify(tree[2*x + 2].sum, tree[x].set, rx - mid);
        tree[x].set = NO_OPERATION;
        return;
    }

    long long findMin(long long l, long long r, long long x, long long lx, long long rx){

        push(x, lx, rx);

        if( l >= rx || lx >= r){
            return NEUTRAL_ELEMENT;
        }
        if( lx >= l && rx <= r){
            return tree[x].sum;
        }

        long long mid = (lx + rx)/2;
        long long s1 = findMin(l, r, 2*x + 1, lx, mid);
        long long s2 = findMin(l, r, 2*x + 2, mid, rx);
        return op_sum(s1, s2);
    }

    long long findMin(long long l, long long r){
        return findMin(l, r, 0, 0, sizeTree);
    }

    void AssignOnSegment(long long l, long long r, long long value, long long x, long long lx, long long rx){
        
        push(x, lx, rx);

        if( l >= rx || lx >= r){
            return;
        }
        if( lx >= l && rx <= r){
            tree[x].set = op_modify(tree[x].set, value, 1);
            tree[x].sum = op_modify(tree[x].sum, value, rx - lx);
            return;
        }

        long long mid = (lx + rx)/2;
        AssignOnSegment(l, r, value, 2*x + 1, lx, mid);
        AssignOnSegment(l, r, value, 2*x + 2, mid, rx);
        tree[x].sum = op_sum(tree[2*x + 1].sum, tree[2*x + 2].sum);
    }

    void AssignOnSegment(long long l, long long r, long long value){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        AssignOnSegment(l, r, value, 0, 0, sizeTree);
    }
    
};

// #define _DEBUG

/*
Есть массив из n элементов, изначально заполненный нулями. Вам нужно написать структуру данных, 
которая обрабатывает два вида запросов:

    присвоить всем элементам на отрезке от l до r−1 значение v,
    узнать минимум на отрезке от l до r−1. 

Входные данные
Первая строка содержит два числа n и m (1≤n,m≤100000) — размер массива и число операций. 
Далее следует описание операций. Описание каждой операции имеет следущий вид:

    1 l r v — присвоить всем элементам на отрезке от l до r−1 значение v (0≤l<r≤n, 0≤v≤109).
    2 l r — узнать минимум на отрезке от l до r−1 (0≤l<r≤n). 

Выходные данные
Для каждой операции второго типа выведите соответствующее значение.
*/

int main() {

	#ifdef _DEBUG
		freopen("input.txt", "r", stdin);
		long long tt = clock();
	#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    long long n, m;
    cin >> n >> m;
    vector<long long> nums(n, 0);

    MySegmentTree tree;
    tree.build(nums);


    for(long long i = 0; i < m; ++i){
        long long operation;
        cin >> operation;
        if( operation == 1){
            long long l, r, value;
            cin >> l >> r >> value;
            tree.AssignOnSegment(l, r, value);
        }
        if( operation == 2){
            long long l, r;
            cin >> l >> r;
            long long answer = tree.findMin(l, r);
            cout << answer << "\n";
        }
    }

	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}