#include <bits/stdc++.h>
using namespace std;

struct MySegmentTree{

    struct node{
        long long answer;
        long long pref;
        long long suf;
        long long sumOnAllSegment;
    };

    node combine(node left, node right){
        node tmp;
        tmp.answer = std::max(left.answer, std::max(right.answer, left.suf + right.pref) );
        tmp.pref = std::max(left.pref, left.sumOnAllSegment + right.pref);
        tmp.suf = std::max(right.suf, right.sumOnAllSegment + left.suf);
        tmp.sumOnAllSegment = left.sumOnAllSegment + right.sumOnAllSegment;
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

    void build(vector<long long> &a, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            if( lx < a.size() ){
                tree[x].answer = a[lx];
                tree[x].pref = a[lx];
                tree[x].suf = a[lx];
                tree[x].sumOnAllSegment = a[lx];
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

    void set(long long i, long long v, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            tree[x].answer = v;
            tree[x].pref = v;
            tree[x].suf = v;
            tree[x].sumOnAllSegment = v;
            return;
        }
        long long mid = (lx + rx)/2;
        if( i < mid ){
            set(i, v, 2*x + 1 , lx, mid);
        }
        else{
            set(i, v, 2*x + 2, mid, rx);
        }
        tree[x] = combine(tree[2*x + 1], tree[2*x + 2]);

    }

    void set(long long idx, long long value){
        set(idx, value, 0, 0, sizeTree);
    }
    
};

// #define _DEBUG

/*
В этой задаче вам нужно написать дерево отрезков для нахождения 
подотрезка с максимальной суммой.

Входные данные
Первая строка содержит два числа n и m (1≤n,m≤100000) — размер массива и число операций.
Следующая строка содержит n чисел ai — начальное состояние массива (−10^9≤ai≤10^9).
Далее следует описание операций.
Описание каждой операции имеет следущий вид: 
i v — присвоить элементу с индексом i значения v (0≤i<n, −10^9≤v≤10^9).

Выходные данные
Выведите m+1 строку: максимальную сумму чисел на отрезке до всех операций 
и после каждой операции. Обратите внимание, 
что этот отрезок может быть пустым (при этом сумма на нем будет равна 0)
*/

int main() {

	#ifdef _DEBUG
		freopen("input.txt", "r", stdin);
		int tt = clock();
	#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    long long n, m;
    cin >> n >> m;
    vector<long long> nums(n);
    for(long long i = 0; i < n; ++i){
        cin >> nums[i];
    }


    MySegmentTree tree;
    tree.build(nums);

    cout << std::max(0LL, tree.tree[0].answer) << "\n";
    for(long long i = 0; i < m; ++i){
        //присвоить элементу с индексом i значение v
        long long idx, value;
        cin >> idx >> value;
        tree.set(idx, value);
        cout << std::max(0LL, tree.tree[0].answer) << "\n";
    }





	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}