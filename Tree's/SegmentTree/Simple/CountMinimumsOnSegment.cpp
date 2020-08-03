#include <bits/stdc++.h>
using namespace std;

struct MySegmentTree{

    struct node{
        int min, cnt;   
    };

    node combine(node a, node b){
        if( a.min < b.min ){
            return a;
        }
        if( b.min < a.min ){
            return b;
        }
        if( a.min == b.min ){
            node tmp;
            tmp.min = a.min;
            tmp.cnt = a.cnt + b.cnt;
            return tmp;
        }
    }

    int sizeTree;
    vector<node> tree;

    void init(int n){
        sizeTree = 1;
        while( sizeTree < n){
            sizeTree *= 2;
        }
        tree.assign(2*sizeTree -1, {0,0});
    }

    void build(vector<int> &a, int x, int lx, int rx){
        if( rx - lx == 1){
            if( lx < a.size() ){
                tree[x].min = a[lx];
                tree[x].cnt = 1;
            }
        }
        else{
            int mid = (lx + rx)/2;
            build(a, 2*x + 1, lx, mid);
            build(a, 2*x + 2, mid, rx);
            tree[x] = combine(tree[2*x + 1], tree[2*x + 2]);
        }
    }

    void build(vector<int> &a){
        init(a.size());
        build(a, 0, 0, sizeTree);
    }

    void set(int i, int v, int x, int lx, int rx){
        if( rx - lx == 1){
            tree[x].min = v;
            tree[x].cnt = 1;
            return;
        }
        int mid = (lx + rx)/2;
        if( i < mid ){
            set(i, v, 2*x + 1 , lx, mid);
        }
        else{
            set(i, v, 2*x + 2, mid, rx);
        }
        tree[x] = combine(tree[2*x + 1], tree[2*x + 2]);

    }

    void set(int idx, int value){
        set(idx, value, 0, 0, sizeTree);
    }

    node CountMin(int l, int r, int x, int lx, int rx){
        if( l >= rx || lx >= r){
            return {INT_MAX, 0};
        }
        if( lx >= l && rx <= r){
            return tree[x];
        }
        int mid = (lx + rx)/2;
        node cntmin1 = CountMin(l, r, 2*x + 1, lx, mid);
        node cntmin2 = CountMin(l, r, 2*x + 2, mid, rx);
        return combine(cntmin1, cntmin2);
    }

    pair<long long, long long> CountMin(int l, int r){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        return {CountMin(l, r, 0, 0, sizeTree).min, CountMin(l, r, 0, 0, sizeTree).cnt};
    }
    
};

// #define _DEBUG

/*
Теперь измените код дерева отрезков, чтобы кроме 
минимума на отрезке считалось также и число элементов, равных минимуму. 

Входные данные
Первая строка содержит два числа n и m (1≤n,m≤100000) — размер массива и число операций. 
Следующая строка содержит n чисел ai — начальное состояние массива (0≤ai≤10^9). 
Далее следует описание операций. Описание каждой операции имеет следущий вид:
1 i v — присвоить элементу с индексом i значение v (0≤i<n, 0≤v≤10^9).
2 l r — найти минимум и число элементов, равных минимуму,
        среди элементов с индексами от l до r−1 (0≤l<r≤n). 

Выходные данные
Для каждой операции второго типа выведите два числа — 
минимум на заданном отрезке и число элементов, равных этому минимуму.
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
            pair<long long, long long> answer = tree.CountMin(l, r);
            cout << answer.first << " " << answer.second << "\n";
        }
    }





	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}