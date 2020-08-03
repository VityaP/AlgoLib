#include <bits/stdc++.h>
using namespace std;

struct MySegmentTree{

    int sizeTree;
    vector<unsigned long long> tree;

    void init(int n){
        sizeTree = 1;
        while( sizeTree < n){
            sizeTree *= 2;
        }
        tree.assign(2*sizeTree -1, 0ULL);
    }

    void build(vector<int> &a, int x, int lx, int rx){
        if( rx - lx == 1){
            if( lx < a.size() ){
                tree[x] = (unsigned long long) (1ULL << (a[lx] - 1));
            }
        }
        else{
            int mid =  (lx + rx)/2;
            build(a, 2*x + 1, lx, mid);
            build(a, 2*x + 2, mid, rx);
            tree[x] = (tree[2*x + 1] | tree[2*x + 2]);
        }
    }

    void build(vector<int> &a){
        init(a.size());
        build(a, 0, 0, sizeTree);
    }

    void set(int i, int v, int x, int lx, int rx){
        if( rx - lx == 1){
            tree[x] = (unsigned long long) (1ULL << (v - 1));
            return;
        }
        int mid = (lx + rx)/2;
        if( i < mid ){
            set(i, v, 2*x + 1 , lx, mid);
        }
        else{
            set(i, v, 2*x + 2, mid, rx);
        }
        tree[x] = (tree[2*x + 1] | tree[2*x + 2]);

    }

    void set(int idx, int value){
        set(idx, value, 0, 0, sizeTree);
    }

    unsigned long long findDifferent(int l, int r, int x, int lx, int rx){
        if( l >= rx || lx >= r){
            return 0;
        }
        if( lx >= l && rx <= r){
            return tree[x];
        }
        int mid = (lx + rx)/2;
        unsigned long long amount1 = findDifferent(l, r, 2*x + 1, lx, mid);
        unsigned long long amount2 = findDifferent(l, r, 2*x + 2, mid, rx);
        unsigned long long answer = (amount1 | amount2);
        return answer;
    }

    unsigned long long findDifferent(int l, int r){
        //!!!!!!!!!!!!!!!!!!!!!
        //ATENTION VICTOR [l,r)
        //!!!!!!!!!!!!!!!!!!!!!
        return findDifferent(l, r, 0, 0, sizeTree);
    }
    
};

// #define _DEBUG

/*
Дан массив a, состоящий из небольших целых чисел (1≤ai≤40). Нужно построить структуру данных, 
которая обрабатывает два вида запросов:
    найти число различных элементов на отрезке массива,
    изменить элемент массива. 

Входные данные
В первой строке два целых числа n и q — длина массива и число запросов соответственно (1≤n,q≤105).
Во второй строке через пробел записано n чисел a1, ..., an, где ai — начальное состояние массива (1≤ai≤40).
Следующие q строк описывают запросы. Каждая из этих строк имеет формат «typei xi yi ».

Если typei=1, то в i-м запросе требуется определить число различных элементов на отрезке от xi до yi, включительно (в этом случае 1≤xi≤yi≤n).

Если typei=2, то элемент с индексом xi заменяется на yi (в этом случае 1≤xi≤n, 1≤yi≤40).

Выходные данные
Для каждого запроса типа 1 выведите ответ на этого запрос на отдельной строке.
*/

int main() {

	#ifdef _DEBUG
		freopen("input.txt", "r", stdin);
		int tt = clock();
	#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    // int a = 1 << 0;
    // int b = 1 << 1;
    // int c = 1 << 2;
    // cout << a << " " << b << " " << c << "\n";
    // cout << (a | b) << "\n";
    // cout << (a | c) << "\n";
    // cout << (b | b) << "\n";

    int n, q;
    cin >> n >> q;
    vector<int> nums(n);
    for(int i = 0; i < n; ++i){
        cin >> nums[i];
    }

    MySegmentTree tree;
    tree.build(nums);

    for(int i = 0; i < q; ++i){
        int operation;
        cin >> operation;
        if( operation == 1){
            //вычислить сумму элементов с индексами от l до r−1
            int l, r;
            cin >> l >> r;
            --l;
            unsigned long long mask = tree.findDifferent(l, r);
            long long answer = 0;
            // cout << "bitMask : ";
            for(int bit = 0; bit <= 40; ++bit){
                if((unsigned long long) (1ULL << bit) & mask){
                    answer += 1;
                    // cout << 1;
                }
                else{
                    // cout << 0;
                }
            }
            // cout << "\n";
            cout << answer << "\n";
        }
        if( operation == 2){
            //присвоить элементу с индексом i значение v
            int idx, value;
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