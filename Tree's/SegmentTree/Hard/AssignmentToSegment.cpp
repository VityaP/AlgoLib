#include <bits/stdc++.h>
using namespace std;

struct MySegmentTree{

    long long sizeTree;
    vector<long long> tree;

    long long NO_OPERATION = -3141592;

    void init(long long n){
        sizeTree = 1;
        while( sizeTree < n){
            sizeTree *= 2;
        }
        tree.assign(2*sizeTree - 1, 0);
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
            tree[x] = NO_OPERATION;
        }
    }

    void build(vector<long long> &a){
        init(a.size());
        build(a, 0, 0, sizeTree);
    }

    void push(int x, int lx, int rx){
        if( tree[x] == NO_OPERATION ){
            return;
        }
        if( rx - lx == 1){
            return;
        }
        tree[2*x + 1] = tree[x];
        tree[2*x + 2] = tree[x];
        tree[x] = NO_OPERATION;
        return;
    }

    long long find(long long i, long long x, long long lx, long long rx){

        push(x, lx, rx);

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
        return tmp;
    }

    long long find(long long idx){
        return find(idx, 0, 0, sizeTree);
    }

    void AssignmentToSegment(long long l, long long r, long long value, long long x, long long lx, long long rx){
        if( l >= rx || lx >= r){
            return;
        }
        if( lx >= l && rx <= r){
            tree[x] = value;
            return;
        }
        long long mid = (lx + rx)/2;
        push(x, lx, rx);
        AssignmentToSegment(l, r, value, 2*x + 1, lx, mid);
        AssignmentToSegment(l, r, value, 2*x + 2, mid, rx);
    }

    void AssignmentToSegment(long long l, long long r, long long value){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        AssignmentToSegment(l, r, value, 0, 0, sizeTree);
    }
    
};

// #define _DEBUG

/*
Есть массив из n элементов, изначально заполненный нулями. Вам нужно написать структуру данных, 
которая обрабатывает два вида запросов:

    присвоить всем элементам на отрезке от l до r−1 значение v,
    узнать текущее значение в ячейке i. 

Входные данные
Первая строка содержит два числа n и m (1≤n,m≤100000) — размер массива и число операций. 
Далее следует описание операций. Описание каждой операции имеет следущий вид:

    1 l r v — присвоить всем элементам на отрезке от l до r−1 значение v, (0≤l<r≤n, 0≤v≤109).
    2 i — найти значение в ячейке с индексом i (0≤i<n)

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
            tree.AssignmentToSegment(l, r, value);
        }
        if( operation == 2){
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