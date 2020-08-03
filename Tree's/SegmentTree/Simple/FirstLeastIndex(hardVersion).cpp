#include <bits/stdc++.h>
using namespace std;

struct MySegmentTree{

    long long sizeTree;
    vector<long long> tree;

    void init(long long n){
        sizeTree = 1;
        while( n > sizeTree ){
            sizeTree *= 2;
        }
        tree.assign(2*sizeTree - 1, {0});
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
            tree[x] = std::max(tree[2*x + 1], tree[2*x + 2]);
        }
    }

    void build(vector<long long> &a){
        init(a.size());
        build(a, 0, 0, sizeTree);
    }

    void set(long long i, long long value, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            tree[x] = value;
            return;
        }
        long long mid = (rx + lx)/2;
        if( i < mid){
            set(i, value, 2*x + 1, lx, mid);
        }
        else{
            set(i, value, 2*x + 2, mid, rx);
        }
        tree[x] = std::max(tree[2*x + 1], tree[2*x + 2]);
    }

    void set(long long idx, long long value){
        set(idx, value, 0, 0, sizeTree);
    }

    long long find(long long value, long long l, long long x, long long lx, long long rx){
        if( tree[x] < value ){
            return -1;
        }
        if( rx <= l ){
            return -1;
        }
        if( rx - lx == 1){
            return lx;
        }
        long long mid = (rx + lx) / 2;
        long long res = find(value, l, 2*x + 1, lx, mid);
        if( res == -1){
            res = find(value, l, 2*x + 2, mid, rx);
        }
        return res;
    }

    long long find(long long value, long long l){
        cout << find(value, l, 0, 0, sizeTree) << "\n";
    }
    
};

// #define _DEBUG

/*
В этой задаче вам нужно добавить в дерево отрезков операцию нахождения по данным x и l 
минимального индекса j, для которого j≥l и a[j]≥x.

Входные данные
Первая строка содержит два числа n и m (1≤n,m≤100000) — размер массива и число операций.
Следующая строка содержит n чисел a[i] — начальное состояние массива (0≤ai≤10^9). 
Далее следует описание операций. Описание каждой операции имеет следущий вид:
1 i v — изменить элемент с индексом i на v (0≤i<n, 0≤v≤10^9).
2 x l — найти минимальный индекс j, для j≥l и a[j]≥x (0≤x≤10^9, 0≤l<n). 
        Если такого элемента нет, выведите −1. Индексы начинаются с 0. 

Выходные данные
Для каждой операции второго типа выведите ответ на запрос.
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
            long long idx, value;
            cin >> idx >> value;
            tree.set(idx, value);
        }
        if( operation == 2){
            long long x, l;
            cin >> x >> l;
            tree.find(x, l);
        }
    }

	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}