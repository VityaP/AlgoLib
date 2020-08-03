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
            int mid =  (lx + rx)/2;
            build(a, 2*x + 1, lx, mid);
            build(a, 2*x + 2, mid, rx);
            tree[x] = tree[2*x + 1] + tree[2*x + 2];
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
        tree[x] = tree[2*x + 1] + tree[2*x + 2];

    }

    void set(int idx, int value){
        set(idx, value, 0, 0, sizeTree);
    }

    long long sum(int l, int r, int x, int lx, int rx){
        if( l >= rx || lx >= r){
            return 0;
        }
        if( lx >= l && rx <= r){
            return tree[x];
        }
        int mid = (lx + rx)/2;
        long long sum1 = sum(l, r, 2*x + 1, lx, mid);
        long long sum2 = sum(l, r, 2*x + 2, mid, rx);
        return sum1 + sum2;
    }

    long long sum(int l, int r){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        return sum(l, r, 0, 0, sizeTree);
    }
    
};

// #define _DEBUG

/*
Дана перестановка p[i] из n элементов, найдите для каждого i 
число таких j, что j<i и p[j]>p[i].

Входные данные
Первая строка содержит число n (1≤n≤10^5), вторая строка содержит n чисел p[i].
Гарантируется, что p[i] образуют перестановку чисел от 1 до n.

Выходные данные
Выведите n чисел, i-е число равно числу таких j, что j<i и p[j]>p[i].
*/

int main() {

	#ifdef _DEBUG
		freopen("input.txt", "r", stdin);
		int tt = clock();
	#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> nums(n, 0);
    MySegmentTree tree;
    tree.build(nums);

    for(int i = 0; i < n; ++i){
        cin >> nums[i];
    }

    for(int i = 0; i < n; ++i){
        int l = nums[i];
        int r = n;
        long long answer = tree.sum(l, r);
        cout << answer << " ";
        tree.set(nums[i] - 1,1);
    }
    cout << "\n";

	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}