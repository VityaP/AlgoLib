#include <bits/stdc++.h>
using namespace std;

struct MySegmentTree{

    int sizeTree;
    vector<long long> tree;

    void init(int n){
        sizeTree = 1;
        while( sizeTree < n){
            sizeTree *= 2;
        }
        tree.assign(2*sizeTree -1, 0);
    }

    void build(vector<int> &a, int x, int lx, int rx){
        if( rx - lx == 1){
            if( lx < a.size() ){
                tree[x] = a[lx];
            }
        }
        else{
            int mid = (lx + rx)/2;
            build(a, 2*x + 1, lx, mid);
            build(a, 2*x + 2, mid, rx);
            tree[x] = std::min(tree[2*x + 1],tree[2*x + 2]);
        }
    }

    void build(vector<int> &a){
        init(a.size());
        build(a, 0, 0, sizeTree);
    }

    void set(int i, int v, int x, int lx, int rx){
        if( rx - lx == 1){
            tree[x] = v;
            return;
        }
        int mid = (lx + rx)/2;
        if( i < mid ){
            set(i, v, 2*x + 1 , lx, mid);
        }
        else{
            set(i, v, 2*x + 2, mid, rx);
        }
        tree[x] = std::min(tree[2*x + 1],tree[2*x + 2]);

    }

    void set(int idx, int value){
        set(idx, value, 0, 0, sizeTree);
    }

    long long min(int l, int r, int x, int lx, int rx){
        if( l >= rx || lx >= r){
            return INT_MAX;
        }
        if( lx >= l && rx <= r){
            return tree[x];
        }
        int mid = (lx + rx)/2;
        long long min1 = min(l, r, 2*x + 1, lx, mid);
        long long min2 = min(l, r, 2*x + 2, mid, rx);
        return std::min(min1, min2);
    }

    long long min(int l, int r){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        return min(l, r, 0, 0, sizeTree);
    }
    
};

// #define _DEBUG

/*
Теперь измените код дерева отрезков, чтобы вместо суммы считался минимум на отрезке

Входные данные
Первая строка содержит два числа n и m (1≤n,m≤100000) — размер массива и число операций. 
Следующая строка содержит n чисел ai — начальное состояние массива (0≤ai≤10^9). 
Далее следует описание операций. Описание каждой операции имеет следущий вид:
1 i v — присвоить элементу с индексом i значение v (0≤i<n, 0≤v≤10^9).
2 l r — вычислить минимум среди элементов с индексами от l до r−1 (0≤l<r≤n). 

Выходные данные
Для каждой операции второго типа выведите соответствующий минимум.
*/

int main() {

	#ifdef _DEBUG
		freopen("input.txt", "r", stdin);
		int tt = clock();
	#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> nums(n);
    for(int i = 0; i < n; ++i){
        cin >> nums[i];
    }


    MySegmentTree tree;
    tree.build(nums);


    for(int i = 0; i < m; ++i){
        int operation;
        cin >> operation;
        if( operation == 1){
            //присвоить элементу с индексом i значение v
            int idx, value;
            cin >> idx >> value;
            tree.set(idx, value);
        }
        if( operation == 2){
            //вычислить сумму элементов с индексами от l до r−1
            int l, r;
            cin >> l >> r;
            long long answer = tree.min(l, r);
            cout << answer << "\n";
        }
    }





	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}