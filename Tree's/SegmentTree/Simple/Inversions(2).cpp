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

    void setZero(long long i, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            tree[x] = 0;
            return;
        }
        long long mid = (lx + rx)/2;
        if( i < mid ){
            setZero(i, 2*x + 1 , lx, mid);
        }
        else{
            setZero(i, 2*x + 2, mid, rx);
        }
        tree[x] = tree[2*x + 1] + tree[2*x + 2];
    }

    void setZero(long long idx){
        setZero(idx, 0, 0, sizeTree);
    }

    long long find(long long idx, long long x, long long lx, long long rx){
        if( rx - lx == 1 ){
            return (lx);
        }
        long long mid = (lx + rx) / 2;
        if( idx < tree[2*x + 2]){
            find(idx, 2*x + 2, mid, rx);
        }
        else{
            find(idx - tree[2*x + 2], 2*x + 1, lx, mid);
        }
    }

    long long find(long long idx){
        return find(idx, 0, 0, sizeTree);
    }
    
};

// #define _DEBUG

/*
Это задача, обратная предыдущей. Была перестановка p[i] из n элементов, 
для каждого i записали число a[i] — число таких j, что j<i и pj>pi.
Восстановите по заданным ai исходную перестановку.

Входные данные
Первая строка содержит число n (1≤n≤10^5), вторая строка содержит n чисел a[i]. 
Гарантируется, что a[i] были получены из какой-то перестановки с помощью процедуры, 
описанной в условии.

Выходные данные
Выведите n чисел, исходную перестановку.
*/

int main() {

	#ifdef _DEBUG
		freopen("input.txt", "r", stdin);
		int tt = clock();
	#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    long long n;
    cin >> n;
    vector<long long> nums(n, 1);
    MySegmentTree tree;
    tree.build(nums);

    for(long long i = 0; i < n; ++i){
        cin >> nums[i];
    }

    vector<long long> answer(n);
    for(int i = n - 1; i >= 0; --i){
        int value = tree.find(nums[i]);
        answer[i] = value + 1;
        tree.setZero(value);
    }

    for(int i = 0; i < n; ++i){
        cout << answer[i] << " ";
    }
    cout << "\n";


	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}