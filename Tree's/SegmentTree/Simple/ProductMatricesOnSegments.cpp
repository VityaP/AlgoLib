#include <bits/stdc++.h>
using namespace std;

long long mod;

struct MySegmentTree{

    struct node{
        long long a,    b;
        long long c,    d;
    };

    node combine(node left, node right){
        node tmp;
        tmp.a = ((left.a * right.a) % mod) + ((left.b * right.c) % mod);
        tmp.b = ((left.a * right.b) % mod) + ((left.b * right.d) % mod);
        tmp.c = ((left.c * right.a) % mod) + ((left.d * right.c) % mod);
        tmp.d = ((left.c * right.b) % mod) + ((left.d * right.d) % mod);
        tmp.a = (mod + tmp.a) % mod;
        tmp.b = (mod + tmp.b) % mod;
        tmp.c = (mod + tmp.c) % mod;
        tmp.d = (mod + tmp.d) % mod;
        return tmp;
    }

    long long sizeTree;
    vector<node> tree;

    void init(long long n){
        sizeTree = 1;
        while( sizeTree < n){
            sizeTree *= 2;
        }
        tree.assign(2*sizeTree -1, {0, 0, 0, 0});
    }

    void build(vector<node> &a, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            if( lx < a.size() ){
                tree[x].a = a[lx].a;
                tree[x].b = a[lx].b;
                tree[x].c = a[lx].c;
                tree[x].d = a[lx].d;
            }
        }
        else{
            long long mid = (lx + rx)/2;
            build(a, 2*x + 1, lx, mid);
            build(a, 2*x + 2, mid, rx);
            tree[x] = combine(tree[2*x + 1], tree[2*x + 2]);
        }
    }

    void build(vector<node> &a){
        init(a.size());
        build(a, 0, 0, sizeTree);
    }

    node solve(long long l, long long r, long long x, long long lx, long long rx){
        if( lx >= r || l >= rx ){
            node tmp;
            tmp.a = 1;
            tmp.b = 0;
            tmp.c = 0;
            tmp.d = 1;
            return tmp;
        }
        if( lx >= l && rx <= r){
            return tree[x];
        }
        int mid = (lx + rx)/2;
        node tmp1 = solve(l, r, 2*x + 1, lx, mid);
        node tmp2 = solve(l, r, 2*x + 2, mid, rx);
        node answer = combine(tmp1, tmp2);
        return answer;
    }

    node solve(long long l, long long r){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        node answer = solve(l, r, 0, 0, sizeTree);
        return answer;
    }
    
};

// #define _DEBUG

/*
Задано n матриц A[1], A[2], ..., A[n] размера 2 × 2. 
Необходимо для нескольких запросов вычислить произведение матриц A[i], A[i + 1], ..., A[j]. 
Все вычисления производятся по модулю r.

Входные данные
Первая строка входного файла содержит числа r (1 ≤ r ≤ 10 000), n (1 ≤ n ≤ 200 000) 
и m (1 ≤ m ≤ 200 000). 
Следующие n блоков по две строки содержащие по два числа в строке — описания матриц. 
Затем следуют m пар целых чисел от 1 до n, запросы на произведение на отрезке.

Выходные данные
Выведите m блоков по две строки,по два числа в каждой — произведения на отрезках.
Разделяйте блоки пустой строкой. Все вычисления производятся по модулю r
*/

int main() {

	#ifdef _DEBUG
		freopen("input.txt", "r", stdin);
		int tt = clock();
	#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    long long n, m;
    cin >> mod >> n >> m;
    vector<MySegmentTree::node> nums(n);
    for(long long i = 0; i < n; ++i){
        cin >> nums[i].a >> nums[i].b;
        cin >> nums[i].c >> nums[i].d;
    }


    MySegmentTree tree;
    tree.build(nums);

    for(long long i = 0; i < m; ++i){
        //присвоить элементу с индексом i значение v
        long long l, r;
        cin >> l >> r;
        --l;
        // --r;
        MySegmentTree::node answer = tree.solve(l, r);
        cout << answer.a << " " << answer.b << "\n";
        cout << answer.c << " " << answer.d << "\n";
        cout << "\n";
    }





	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}