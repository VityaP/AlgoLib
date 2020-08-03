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
        return sum(l, r, 0, 0, sizeTree);
    }
    
};

// #define _DEBUG

/*
Дан массив из 2n чисел, каждое число от 1 до n в нем встречается ровно два раза. 
Будем говорить, что отрезок y пересекается с отрезком x, 
если ровно одно вхождение числа y находятся между вхождениями числа x. 
Найдите для каждого отрезка i, сколько есть отрезков, которые с ним пересекаются.

Входные данные
Первая строка содержит число n (1≤n≤10^5), вторая строка содержит 2n чисел. 
Гарантируется, что каждое число от 1 до n встречается ровно два раза.

Выходные данные
Выведите n чисел, i-е число равно числу отрезков, которые пересекаются с отрезком i.
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
    vector<long long> nums1(2*n, 0);
    vector<long long> pos1(n, -1);
    vector<long long> answer1(n);

    MySegmentTree tree;
    tree.build(nums1);

    for(long long i = 0; i < 2*n; ++i){
        cin >> nums1[i];
    }

    for(long long i = 0; i < 2*n; ++i){
        if( pos1[nums1[i] - 1] == -1){
            pos1[nums1[i] - 1] = i;
            tree.set(i,1);
        }
        else{
            answer1[nums1[i] - 1] = tree.sum(pos1[nums1[i] - 1],i) - 1;
            tree.set(pos1[nums1[i] - 1],0);
        }
    }

    vector<long long> nums2(2*n, 0);
    vector<long long> pos2(n, -1);
    vector<long long> answer2(n);
    
    for(int i = 0; i < 2*n; ++i){
        nums2[i] = nums1[2*n - 1 - i];
    }
    for(int i = 0; i < 2*n; ++i){
        if( pos2[nums2[i] - 1] == -1){
            pos2[nums2[i] - 1] = i;
            tree.set(i,1);
        }
        else{
            answer2[nums2[i] - 1] = tree.sum(pos2[nums2[i] - 1],i) - 1;
            tree.set(pos2[nums2[i] - 1],0);
        }
    }


    for(long long i = 0; i < n; ++i){
        cout << answer1[i] + answer2[i] << " ";
    }
    cout << "\n";

	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}