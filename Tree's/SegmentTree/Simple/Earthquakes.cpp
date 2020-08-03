#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct MySegmentTree{

    long long sizeTree;

    vector<long long> tree;

    long long NO_OPERATION = -3141592;

    void init(long long n){
        sizeTree = 1;
        while( sizeTree < n){
            sizeTree *= 2;
        }
        tree.assign(2*sizeTree - 1, LLONG_MAX);
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
        // build(a, 0, 0, sizeTree);
    }

    // void push(int x, int lx, int rx){
    //     if( tree[x] == NO_OPERATION ){
    //         return;
    //     }
    //     if( rx - lx == 1){
    //         return;
    //     }
    //     tree[2*x + 1] = tree[x];
    //     tree[2*x + 2] = tree[x];
    //     tree[x] = NO_OPERATION;
    //     return;
    // }

    void CreateHome(long long i, ll health, long long x, long long lx, long long rx){

        // push(x, lx, rx);

        if( rx - lx == 1){
            tree[x] = health;
            return;
        }
        long long mid = (lx + rx)/2;
        long long tmp;
        if( i < mid ){
            CreateHome(i, health, 2*x + 1 , lx, mid);
        }
        else{
            CreateHome(i, health, 2*x + 2, mid, rx);
        }
        tree[x] = min(tree[2*x + 1], tree[2*x + 2]);
    }

    void CreateHome(long long idx, ll health){
        return CreateHome(idx, health, 0, 0, sizeTree);
    }

    long long Earthquake(long long l, long long r, long long value, long long x, long long lx, long long rx){
        if( l >= rx || lx >= r){
            return 0;
        }
        if( lx >= l && rx <= r){
            if( tree[x] > value ){
                return 0;
            }
        }
        if( rx - lx == 1){
            if( tree[x] > value ){
                return 0;
            }
            else{
                tree[x] = LLONG_MAX;
                return 1;
            }
        }
        long long mid = (lx + rx)/2;
        // push(x, lx, rx);
        ll s1 = Earthquake(l, r, value, 2*x + 1, lx, mid);
        ll s2 = Earthquake(l, r, value, 2*x + 2, mid, rx);
        return (s1 + s2);
    }

    long long Earthquake(long long l, long long r, long long value){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        return Earthquake(l, r, value, 0, 0, sizeTree);
    }
    
};

// #define _DEBUG

/*
Город представляет собой последовательность из n клеток, занумерованных числами от 0 до n−1. 
Изначально все клетки пустые. Далее последовательно происходят m событий одного из двух типов:
    в клетке i строится здание с прочностью h (если в этой клетке уже было здание, оно сносится и заменяется на новое),
    
    на отрезке от l до r−1 случается землятресение мощностью p, оно разрушает все здания, прочность которых не больше p.
Ваша задача — для каждого землятресения сказать, сколько зданий оно разрушит.

Входные данные
Первая строка содержит числа n и m — число клеток и число событий (1≤n,m≤105). Следующие m строк содержат 
описание событий. Описание каждого события имеет следующий вид:

    1 i h — в клетке i строится здание с прочностью h (0≤i<n, 1≤h≤109).
    2 l r p — на отрезке от l до r−1 происходит землятресение с мощностью p (0≤l<r≤n, 1≤p≤109). 

Выходные данные
Для каждого события второго типа выведите, сколько зданий было разрушено.
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
            long long idx, health;
            cin >> idx >> health;
            tree.CreateHome(idx, health);
        }
        if( operation == 2){
            long long l, r, value;
            cin >> l >> r >> value;
            cout << tree.Earthquake(l, r, value) << "\n";
        }
    }

	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}