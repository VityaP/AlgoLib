#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

struct MySegmentTree{

    long long sizeTree;

    struct node{
        long long sum;
        long long mult;
    };

    vector<node> tree;

    long long NO_OPERATION = 1;
    long long NEUTRAL_ELEMENT = 0;

    long long op_modify(long long &a, long long &b){
        return (a * b) % MOD;
    }

    long long op_sum(long long &a, long long &b){
        return (a + b) % MOD;
    }

    void init(long long n){
        sizeTree = 1;
        while( sizeTree < n){
            sizeTree *= 2;
        }
        tree.assign(2*sizeTree - 1, {0, NO_OPERATION});
        // or
        // tree.resize(2*sizeTree - 1);
    }

    void build(vector<long long> &a, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            if( lx < a.size() ){
                tree[x] = {a[lx], NO_OPERATION};
            }
            // tree[x] = {1, 1};
        }
        else{
            long long mid = (lx + rx)/2;
            build(a, 2*x + 1, lx, mid);
            build(a, 2*x + 2, mid, rx);
            tree[x] = {op_sum(tree[2*x + 1].sum, tree[2*x + 2].sum), NO_OPERATION};
        }
    }

    void build(vector<long long> &a){
        init(a.size());
        build(a, 0, 0, sizeTree);
    }

    // void push(int x, int lx, int rx){
    //     if( rx - lx == 1){
    //         tree[x].sum = (tree[x].sum * tree[x].multiply) % MOD;
    //         tree[x].multiply = NO_OPERATION;
    //         return;
    //     }
    //     tree[2*x + 1].multiply = (tree[2*x + 1].multiply * tree[x].multiply) % MOD;
    //     tree[2*x + 2].multiply = (tree[2*x + 2].multiply * tree[x].multiply) % MOD;
    //     tree[x].sum = (tree[x].sum * tree[x].multiply) % MOD;
    //     tree[x].multiply = NO_OPERATION;
    //     return;
    // }

    long long findSum(long long l, long long r, long long x, long long lx, long long rx){

        // push(x, lx, rx);

        if( l >= rx || lx >= r){
            return NEUTRAL_ELEMENT;
        }
        if( lx >= l && rx <= r){
            return tree[x].sum;
        }

        long long mid = (lx + rx)/2;
        long long s1 = findSum(l, r, 2*x + 1, lx, mid);
        long long s2 = findSum(l, r, 2*x + 2, mid, rx);
        long long answer = op_sum(s1, s2);
        answer = op_modify(answer, tree[x].mult);
        return answer;
    }

    long long findSum(long long l, long long r){
        return findSum(l, r, 0, 0, sizeTree);
    }

    void MultiplicateOnSegment(long long l, long long r, long long value, long long x, long long lx, long long rx){
        if( l >= rx || lx >= r){
            return;
        }
        if( lx >= l && rx <= r){
            tree[x].mult = op_modify(tree[x].mult, value);
            tree[x].sum = op_modify(tree[x].sum, value);
            return;
        }

        long long mid = (lx + rx)/2;
        MultiplicateOnSegment(l, r, value, 2*x + 1, lx, mid);
        MultiplicateOnSegment(l, r, value, 2*x + 2, mid, rx);
        tree[x].sum = op_sum(tree[2*x + 1].sum, tree[2*x + 2].sum);
        tree[x].sum = op_modify(tree[x].sum, tree[x].mult);
    }

    void MultiplicateOnSegment(long long l, long long r, long long value){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        MultiplicateOnSegment(l, r, value, 0, 0, sizeTree);
    }
    
};

// #define _DEBUG

/*
Есть массив из n элементов, изначально заполненный eдиницами. Вам нужно написать структуру данных, 
которая обрабатывает два вида запросов:
    умножить все элементы от l до r−1 на число v,
    найти сумму на отрезке от l до r−1. 
Обе операции выполняются по модулю 109+7.

Входные данные
Первая строка содержит два числа n и m (1≤n,m≤100000) — размер массива и число операций. 
Далее следует описание операций. Описание каждой операции имеет следущий вид:

    1 l r v — умножить все элементы от l до r−1 на число v (0≤l<r≤n, 1≤v<109+7).
    2 l r — найти сумму на отрезке от l до r−1 (0≤l<r≤n). 

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
    vector<long long> nums(n, 1);

    MySegmentTree tree;
    tree.build(nums);


    for(long long i = 0; i < m; ++i){
        long long operation;
        cin >> operation;
        if( operation == 1){
            long long l, r, value;
            cin >> l >> r >> value;
            tree.MultiplicateOnSegment(l, r, value);
        }
        if( operation == 2){
            long long l, r;
            cin >> l >> r;
            long long answer = tree.findSum(l, r);
            cout << answer << "\n";
        }
    }

	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}