#include <bits/stdc++.h>
using namespace std;


// Требуется найти в связном графе остовное дерево минимального веса.
// Входные данные

// Первая строка входного файла содержит два натуральных числа n
// и m (2≤n≤200000,1≤m≤200000) — число вершин и ребер, соответственно. Следующие m строк содержат описание ребер по одному на строке. Ребро номер i описывается тремя натуральными числами bi, ei и wi — номера концов ребра и его вес соответственно (1≤bi,ei≤n, 0≤wi≤100000

// ).

// Граф является связным.
// Выходные данные

// Первая строка выходного файла должна содержать одно натуральное число — вес минимального остовного дерева.


int updateParent(int x, vector<int> &par){
    if( x != par[x] ){
        par[x] = updateParent(par[x], par);
    }
    return par[x];
}

struct pt{
    int u;
    int v;
    int cost;
    friend bool operator<(pt &l, pt &r){
        return (l.cost < r.cost);
    }
};

int main() {

    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> parent(n + 1);
    vector<int> size(n + 1);
    for(int i = 0; i <= n; ++i){
        parent[i] = i;
        size[i] = 1;
    }

    vector<pt> nums(m);
    for(int i = 0; i < m; ++i){
        cin >> nums[i].u >> nums[i].v >> nums[i].cost;
    }
    sort(nums.begin(), nums.end());

    int addEdges = 0;
    long long minCost = 0;
    for(int i = 0; i < nums.size(); ++i){
        if( addEdges == n - 1 ){
            break;
        }
        int leader1 = updateParent(nums[i].u, parent);
        int leader2 = updateParent(nums[i].v, parent);
        if( leader1 != leader2 ){
            ++addEdges;
            minCost += nums[i].cost;
            if( size[leader1] < size[leader2] ){
                size[leader2] += size[leader1];
                parent[leader1] = leader2;
            }
            else{
                size[leader1] += size[leader2];
                parent[leader2] = leader1;
            }
        }
    }

    cout << minCost << "\n";

    return 0;
}
