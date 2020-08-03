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
        tree.assign(2*sizeTree -1, 0);
    }

    void build(vector<long long> &a, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            if( lx < a.size() ){
                tree[x] = a[lx];
            }
        }
        else{
            long long mid =  (lx + rx)/2;
            build(a, 2*x + 1, lx, mid);
            build(a, 2*x + 2, mid, rx);
            tree[x] = tree[2*x + 1] + tree[2*x + 2];
        }
    }

    void build(vector<long long> &a){
        init(a.size());
        build(a, 0, 0, sizeTree);
    }

    long long find(long long i, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            return tree[x];
        }
        long long mid = (lx + rx)/2;
        long long tmp;
        if( i < mid ){
            tmp = find(i, 2*x + 1 , lx, mid);
        }
        else{
            tmp = find(i, 2*x + 2, mid, rx);
        }
        long long answer = tree[x] + tmp;
        return answer;
    }

    long long find(long long idx){
        return find(idx, 0, 0, sizeTree);
    }

    void addToSegment(long long l, long long r, long long value, long long x, long long lx, long long rx){
        if( l >= rx || lx >= r){
            return;
        }
        if( lx >= l && rx <= r){
            tree[x] += value;
            return;
        }
        long long mid = (lx + rx)/2;
        addToSegment(l, r, value, 2*x + 1, lx, mid);
        addToSegment(l, r, value, 2*x + 2, mid, rx);
        return;
    }

    void addToSegment(long long l, long long r, long long value){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        addToSegment(l, r, value, 0, 0, sizeTree);
    }
    
};

// #define _DEBUG

/*
Есть массив из n элементов, изначально заполненный нулями. Вам нужно написать структуру данных, 
которая обрабатывает два вида запросов:

    прибавить к отрезку от l до r−1 число v,
    узнать текущее значение в ячейке i. 

Входные данные
Первая строка содержит два числа n и m (1≤n,m≤100000) — размер массива и число операций. 
Далее следует описание операций. Описание каждой операции имеет следущий вид:

    1 l r v — прибавить значение v к отрезку от l до r−1 (0≤l<r≤n, 0≤v≤109).
    2 i — найти значение в ячейке с индексом i (0≤i<n). 

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
            //прибавить значение v к отрезку от l до r−1
            long long l, r, value;
            cin >> l >> r >> value;
            tree.addToSegment(l, r, value);
        }
        if( operation == 2){
            //найти значение в ячейке с индексом i
            long long idx;
            cin >> idx;
            long long answer = tree.find(idx);
            cout << answer << "\n";
        }
    }

	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}