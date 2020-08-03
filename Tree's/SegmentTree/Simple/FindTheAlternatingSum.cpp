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

    void set(long long i, long long v, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            tree[x] = v;
            return;
        }
        long long mid = (lx + rx)/2;
        if( i < mid ){
            set(i, v, 2*x + 1 , lx, mid);
        }
        else{
            set(i, v, 2*x + 2, mid, rx);
        }
        tree[x] = tree[2*x + 1] + tree[2*x + 2];

    }

    void set(long long idx, long long value){
        if( idx % 2 == 1){
            value *= -1;
        }
        set(idx, value, 0, 0, sizeTree);
    }

    long long sum(long long l, long long r, long long x, long long lx, long long rx){
        if( l >= rx || lx >= r){
            return 0;
        }
        if( lx >= l && rx <= r){
            return tree[x];
        }
        long long mid = (lx + rx)/2;
        long long sum1 = sum(l, r, 2*x + 1, lx, mid);
        long long sum2 = sum(l, r, 2*x + 2, mid, rx);
        return sum1 + sum2;
    }

    long long sum(long long l, long long r){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        long long answer =  sum(l, r, 0, 0, sizeTree);
        if( l % 2 == 1){
            answer *= -1;
        }
        return answer;
    }
    
};

// #define _DEBUG

/*
Реализуйте структуру данных из n элементов a[1], a[2] ... a[n], 
поддерживающую следующие операции:
присвоить элементу a[i] значение j;
найти знакочередующуюся сумму на отрезке от l до r включительно

Входные данные
В первой строке входного файла содержится натуральное число n (1 ≤ n ≤ 10^5) — длина массива. 
Во второй строке записаны начальные значения элементов(неотрицательные целые числа,
не превосходящие 104).
В третьей строке находится натуральное число m (1 ≤ m ≤ 10^5) — количество операций.
В последующих m строках записаны операции:
операция первого типа задается тремя числами 0 i j (1 ≤ i ≤ n, 1 ≤ j ≤ 10^4).
операция второго типа задается тремя числами 1 l r (1 ≤ l ≤ r ≤ n). 

Выходные данные
Для каждой операции второго типа выведите на отдельной строке соответствующую знакочередующуюся сумму.
*/

int main() {

	#ifdef _DEBUG
		freopen("input.txt", "r", stdin);
		long long tt = clock();
	#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    long long n;
    cin >> n;
    vector<long long> nums(n);
    for(long long i = 0; i < n; ++i){
        cin >> nums[i];
        if( i % 2 == 1){
            nums[i] *= -1;
        }
    }

    MySegmentTree tree;
    tree.build(nums);

    long long m;
    cin >> m;

    for(long long i = 0; i < m; ++i){
        long long operation;
        cin >> operation;
        if( operation == 0){
            //присвоить элементу с индексом i значение v
            long long idx, value;
            cin >> idx >> value;
            --idx;
            tree.set(idx, value);
        }
        if( operation == 1){
            long long l, r;
            cin >> l >> r;
            --l;
            //вычисляет сумму элементов с индексами от l до r−1
            //поэтому запускаю от от l до r+1, но тут индексация начинается с 1, а не с 0
            //оставляем всё как есть
            long long answer = tree.sum(l, r);
            cout << answer << "\n";
        }
    }

	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}