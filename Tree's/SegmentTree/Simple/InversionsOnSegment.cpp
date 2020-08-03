#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct MySegmentTree{

    long long sizeTree;

    struct node{
        long long inversions;
        vector<long long> amount;
    };

    node combine(node &l, node &r){
        vector<long long> tmp(41, 0);
        long long leftSum = 0;
        long long rightSum = 0;
        for(int i = 1; i <= 40; ++i){
            tmp[i] = l.amount[i] + r.amount[i];
            leftSum += l.amount[i];
            // rightSum += r.amount[i];
        }
        long long inv = l.inversions + r.inversions;

        for(int i = 1; i <= 40; ++i){
            if(l.amount[i] > 0){
                // for(int j = i - 1; j >= 1; --j){
                //     inv += r.amount[j] * l.amount[i];
                // }
                inv += rightSum * l.amount[i];
            }
            rightSum += r.amount[i];
        }

        long long leftShift = 0;
        for(int i = 1; i <= 40; ++i){
            leftShift += l.amount[i];
            if( r.amount[i] > 0){
                // for(int j = i + 1; j <= 40; ++j){
                //     inv += l.amount[j] * r.amount[i];
                // }
                inv += (leftSum - leftShift) * r.amount[i];
            }
        }
        return {inv, tmp};
    }

    vector<node> tree;

    // long long NO_OPERATION = -3141592;

    void init(long long n){
        sizeTree = 1;
        while( sizeTree < n){
            sizeTree *= 2;
        }
        tree.assign(2*sizeTree - 1, {0, vector<long long>(41, 0)});
    }

    void build(vector<long long> &a, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            if( lx < a.size() ){
                vector<long long> tmp(41, 0);
                tmp[a[lx]] = 1;
                tree[x] = {0, tmp};
            }
        }
        else{
            long long mid = (lx + rx)/2;
            build(a, 2*x + 1, lx, mid);
            build(a, 2*x + 2, mid, rx);
            tree[x] = combine(tree[2*x + 1], tree[2*x + 2]);
        }
    }

    void build(vector<long long> &a){
        init(a.size());
        build(a, 0, 0, sizeTree);
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

    void set(long long i, ll value, long long x, long long lx, long long rx){

        // push(x, lx, rx);

        if( rx - lx == 1){
            for(int i = 1; i <= 40; ++i){
                tree[x].amount[i] = 0;
            }
            tree[x].amount[value] = 1;
            return;
        }
        long long mid = (lx + rx)/2;
        long long tmp;
        if( i < mid ){
            set(i, value, 2*x + 1 , lx, mid);
        }
        else{
            set(i, value, 2*x + 2, mid, rx);
        }
        tree[x] = combine(tree[2*x + 1], tree[2*x + 2]);
    }

    void set(long long idx, ll value){
        return set(idx, value, 0, 0, sizeTree);
    }

    node CountInversions(long long l, long long r, long long x, long long lx, long long rx){
        if( l >= rx || lx >= r){
            vector<long long> tmp(41, 0);
            return {0, tmp};
        }
        if( lx >= l && rx <= r){
            return tree[x];
        }
        long long mid = (lx + rx)/2;
        // push(x, lx, rx);
        node s1 = CountInversions(l, r, 2*x + 1, lx, mid);
        node s2 = CountInversions(l, r, 2*x + 2, mid, rx);
        return combine(s1, s2);
    }

    long long CountInversions(long long l, long long r){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        return CountInversions(l, r, 0, 0, sizeTree).inversions / 2;
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
    vector<long long> nums(n);
    for(int i = 0; i < n; ++i){
        cin >> nums[i];
    }

    MySegmentTree tree;
    tree.build(nums);


    for(long long i = 0; i < m; ++i){
        long long operation;
        cin >> operation;
        if( operation == 1){
            long long l, r;
            cin >> l >> r;
            --l;
            cout << tree.CountInversions(l, r) << "\n";
        }
        if( operation == 2){
            long long idx, value;
            cin >> idx >> value;
            --idx;
            tree.set(idx, value);
        }
    }

	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}