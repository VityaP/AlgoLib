#include <bits/stdc++.h>
using namespace std;

struct MySegmentTree{

    long long sizeTree;

    struct node{
        long long sum;
        long long weightedSum;
        long long length;
        long long add;
    };

    vector<node> tree;

    node NEUTRAL_ELEMENT = {0, 0, 0, 0};

    void combine(node &root, node &l, node &r){
        root.length = l.length + r.length;
        root.sum = l.sum + r.sum + root.length * root.add;
        root.weightedSum = l.weightedSum + r.weightedSum + r.sum * l.length + root.length * (root.length + 1) * root.add / 2;
    }

    void init(long long n){
        sizeTree = 1;
        while( sizeTree < n){
            sizeTree *= 2;
        }
        tree.assign(2*sizeTree - 1, {0, 0, 0, 0});
        // or
        // tree.resize(2*sizeTree - 1);
    }

    void build(vector<long long> &a, long long x, long long lx, long long rx){
        if( rx - lx == 1){
            if( lx < a.size() ){
                tree[x] = {a[lx], a[lx], 1, 0};
            }
        }
        else{
            long long mid = (lx + rx)/2;
            build(a, 2*x + 1, lx, mid);
            build(a, 2*x + 2, mid, rx);

            tree[x] = NEUTRAL_ELEMENT;
            combine(tree[x], tree[2*x + 1], tree[2*x + 2]);
        }
    }

    void build(vector<long long> &a){
        init(a.size());
        build(a, 0, 0, sizeTree);
    }

    node findWeightedSum(long long l, long long r, long long x, long long lx, long long rx){

        // push(x, lx, rx);

        if( l >= rx || lx >= r){
            return NEUTRAL_ELEMENT;
        }
        if( lx >= l && rx <= r){
            return tree[x];
        }

        long long mid = (lx + rx)/2;
        node s1 = findWeightedSum(l, r, 2*x + 1, lx, mid);
        node s2 = findWeightedSum(l, r, 2*x + 2, mid, rx);
        
        node answer = {0, 0, 0, tree[x].add};
        combine(answer, s1, s2);
        return answer;
    }

    long long findWeightedSum(long long l, long long r){
        return findWeightedSum(l, r, 0, 0, sizeTree).weightedSum;
    }

    void AddOnSegment(long long l, long long r, long long value, long long x, long long lx, long long rx){
        if( l >= rx || lx >= r){
            return;
        }
        if( lx >= l && rx <= r){
            tree[x].sum += tree[x].length * value;
            tree[x].weightedSum += tree[x].length * (tree[x].length + 1) * value / 2;
            tree[x].add += value;
            return;
        }

        long long mid = (lx + rx)/2;
        AddOnSegment(l, r, value, 2*x + 1, lx, mid);
        AddOnSegment(l, r, value, 2*x + 2, mid, rx);
        combine(tree[x], tree[2*x + 1], tree[2*x + 2]);
    }

    void AddOnSegment(long long l, long long r, long long value){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        AddOnSegment(l, r, value, 0, 0, sizeTree);
    }
    
};

// #define _DEBUG

/*
Есть массив из n элементов, изначально заполненный нулями. Вам нужно написать структуру данных, 
которая обрабатывает два вида запросов:

    применить ко всем элементам от l до r−1 операцию ai=ai|v (битовый OR),
    найти битовый AND элементов на отрезке от l до r−1. 

Входные данные
Первая строка содержит два числа n и m (1≤n,m≤100000) — размер массива и число операций. 
Далее следует описание операций. Описание каждой операции имеет следущий вид:

    1 применить ко всем элементам от l до r−1 операцию ai=ai|v (0≤l<r≤n, 0≤v<2^30).
    2 l r — найти битовый AND элементов на отрезке от l до r−1 (0≤l<r≤n). 

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
            long long l, r, value;
            cin >> l >> r >> value;
            --l;
            tree.AddOnSegment(l, r, value);
        }
        if( operation == 2){
            long long l, r;
            cin >> l >> r;
            --l;
            long long answer = tree.findWeightedSum(l, r);
            cout << answer << "\n";
        }
    }

	#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
	#endif

	return 0;  

}