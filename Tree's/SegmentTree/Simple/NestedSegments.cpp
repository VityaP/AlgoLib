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
Будем говорить, что отрезок y вложен в отрезок x, если оба вхождения числа y находятся между 
вхождениями числа x. Найдите для каждого отрезка i, сколько есть отрезков, которые в него вложены.

Входные данные
Первая строка содержит число n (1≤n≤10^5), вторая строка содержит 2n чисел. 
Гарантируется, что каждое число от 1 до n встречается ровно два раза.

Выходные данные
Выведите n чисел, i-е число равно числу отрезков, вложенных в отрезок i.
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
    vector<long long> nums(2*n, 0);
    vector<long long> pos(n, -1);
    vector<long long> answer(n);

    MySegmentTree tree;
    tree.build(nums);

    for(long long i = 0; i < 2*n; ++i){
        cin >> nums[i];
    }

    for(long long i = 0; i < 2*n; ++i){
        if( pos[nums[i] - 1] == -1){
            pos[nums[i] - 1] = i;
        }
        else{
            answer[nums[i] - 1] = tree.sum(pos[nums[i] - 1],i);
            tree.set(pos[nums[i] - 1],1);
        }
    }
    for(long long i = 0; i < n; ++i){
        cout << answer[i] << " ";
    }
    cout << "\n";

	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}