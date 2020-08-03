#include <bits/stdc++.h>
using namespace std;

struct MySegmentTree{

    long long sizeTree;
    vector<long long> tree;

    void init(long long n){
        sizeTree = 1;
        while( sizeTree < n){
            sizeTree *= 2;
        }
        tree.assign(2*sizeTree -1, {0});
    }

    void build(vector<long long> &a, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            if( lx < a.size() ){
                tree[x] = a[lx];
            }
        }
        else{
            long long mid = (lx + rx)/2;
            build(a, 2*x + 1, lx, mid);
            build(a, 2*x + 2, mid, rx);
            tree[x] = tree[2*x + 1] + tree[2*x + 2];
        }
    }

    void build(vector<long long> &a){
        init(a.size());
        build(a, 0, 0, sizeTree);
    }

    void set(long long i, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            tree[x] = tree[x]^1;
            return;
        }
        long long mid = (lx + rx)/2;
        if( i < mid ){
            set(i, 2*x + 1 , lx, mid);
        }
        else{
            set(i, 2*x + 2, mid, rx);
        }
        tree[x] = tree[2*x + 1] + tree[2*x + 2];
    }

    void set(long long idx){
        set(idx, 0, 0, sizeTree);
    }

    long long find(long long idx, long long x, long long lx, long long rx){
        if( rx - lx == 1 ){
            return (lx);
        }
        long long mid = (lx + rx) / 2;
        if( idx < tree[2*x + 1]){
            find(idx, 2*x + 1, lx, mid);
        }
        else{
            find(idx - tree[2*x + 1], 2*x + 2, mid, rx);
        }
    }

    long long find(long long idx){
        cout << find(idx, 0, 0, sizeTree) << "\n";
    }
    
};

// #define _DEBUG

/*
В этой задаче вам нужно добавить в дерево отрезков операцию нахождения k-й единицы.

Входные данные
Первая строка содержит два числа n и m (1≤n,m≤100000) — размер массива и число операций. 
Следующая строка содержит n чисел a[i] — начальное состояние массива (a[i]∈{0,1}). 
Далее следует описание операций. Описание каждой операции имеет следущий вид:
1 i —   изменить элемент с индексом i на противоположный.
2 k —   найти k-ю единицу (единицы нумеруются с 0, гарантируется, 
        что в массиве достаточное количество единиц). 

Выходные данные
Для каждой операции второго типа выведите индекс 
соответствующей единицы (все индексы в этой задаче от 0).
*/

int main() {

	#ifdef _DEBUG
		freopen("input.txt", "r", stdin);
		int tt = clock();
	#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    long long n, m;
    cin >> n >> m;
    vector<long long> nums(n);
    for(long long i = 0; i < n; ++i){
        cin >> nums[i];
    }


    MySegmentTree tree;
    tree.build(nums);

    for(int i = 0; i < m; ++i){
        int operation;
        cin >> operation;
        if( operation == 1){
            long long idx;
            cin >> idx;
            tree.set(idx);
        }
        if( operation == 2){
            long long k;
            cin >> k;
            tree.find(k);
        }
    }




	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}