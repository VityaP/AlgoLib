#include <bits/stdc++.h>
using namespace std;

struct MySegmentTree{

    long long sizeTree;

    struct node{
        long long add;
        long long min;
    };

    vector<node> tree;

    // long long NO_OPERATION = -3141592;

    void init(long long n){
        sizeTree = 1;
        while( sizeTree < n){
            sizeTree *= 2;
        }
        tree.assign(2*sizeTree - 1, {0, 0});
    }

    void build(vector<long long> &a, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            if( lx < a.size() ){
                tree[x] = {0, a[lx]};
            }
        }
        else{
            long long mid = (lx + rx)/2;
            build(a, 2*x + 1, lx, mid);
            build(a, 2*x + 2, mid, rx);
            tree[x] = {0, min(tree[2*x + 1].min, tree[2*x + 2].min)};
        }
    }

    void build(vector<long long> &a){
        init(a.size());
        // build(a, 0, 0, sizeTree);
    }

    long long findMin(long long l, long long r, long long x, long long lx, long long rx){
        if( l >= rx || lx >= r){
            return LLONG_MAX;
        }
        if( lx >= l && rx <= r){
            return tree[x].min;
        }
        int mid = (lx + rx) / 2;
        long long s1 = findMin(l, r, 2*x + 1, lx, mid);
        long long s2 = findMin(l, r, 2*x + 2, mid, rx);
        long long res = min(s1 ,s2);
        res += tree[x].add;
        return res;
    }

    long long findMin(long long l, long long r){
        return findMin(l, r, 0, 0, sizeTree);
    }

    void AddToSegment(long long l, long long r, long long value, long long x, long long lx, long long rx){
        if( l >= rx || lx >= r){
            return;
        }
        if( lx >= l && rx <= r){
            tree[x].add += value;
            tree[x].min += value;
            return;
        }
        int mid = (lx + rx) / 2;
        AddToSegment(l, r, value, 2*x + 1, lx, mid);
        AddToSegment(l, r, value, 2*x + 2, mid, rx);
        tree[x].min = min(tree[2*x + 1].min, tree[2*x + 2].min) + tree[x].add;
        return;
    }

    void AddToSegment(long long l, long long r, long long value){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        AddToSegment(l, r, value, 0, 0, sizeTree);
    }
    
};

// #define _DEBUG

/*
Есть массив из n элементов, изначально заполненный нулями. Вам нужно написать структуру данных, 
которая обрабатывает два вида запросов:

    прибавить к отрезку от l до r−1 число v,
    узнать минимум на отрезке от l до r−1. 

Входные данные
Первая строка содержит два числа n и m (1≤n,m≤100000) — размер массива и число операций. 
Далее следует описание операций. Описание каждой операции имеет следущий вид:

    1 l r v — прибавить значение v к отрезку от l до r−1 (0≤l<r≤n, 0≤v≤109).
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
            tree.AddToSegment(l, r, value);
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