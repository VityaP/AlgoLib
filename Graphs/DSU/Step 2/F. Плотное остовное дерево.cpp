#include <bits/stdc++.h>
using namespace std;




// Требуется найти в графе остовное дерево, в котором разница между весом максимального и минимального ребра минимальна.
// Входные данные

// Первая строка входного файла содержит два числа n и m (2 ≤ n ≤ 1000, 0 ≤ m ≤ 10 000) — количество вершин и ребер графа соответственно. Следующие m строк содержат описание ребер по одному на строке. Ребро номер i описывается тремя целыми числами b i, e i и w i (1 ≤ b i, e i ≤ n,  - 109 ≤ w i ≤ 109) — номера концов ребра и его вес соответственно.
// Выходные данные

// Если остовное дерево существует, выведите в первой строке выходного файла YES, а во второй строке одно целое число — минимальную разность между весом максимального и минимального ребра в остовном дереве.

// В противном случае, в единственной строке выведите NO.





int updateParent(int x, vector<int> &par){
    if( x != par[x] ){
        par[x] = updateParent(par[x], par);
    }
    return par[x];
}

struct pt{
    int u;
    int v;
    long long cost;
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

    vector<pt> nums(m);
    for(int i = 0; i < m; ++i){
        cin >> nums[i].u >> nums[i].v >> nums[i].cost;
    }
    sort(nums.begin(), nums.end());


    long long answer = LLONG_MAX;

    for(int idx = 0; idx < nums.size(); ++idx ){

        for(int i = 0; i <= n; ++i){
            parent[i] = i;
            size[i] = 1;
        }

        int addEdges = 0;
        long long minEdge = LLONG_MAX;
        long long maxEdge = LLONG_MIN;
        for(int i = idx; i < nums.size(); ++i){
            if( addEdges == n - 1 ){
                break;
            }
            int leader1 = updateParent(nums[i].u, parent);
            int leader2 = updateParent(nums[i].v, parent);
            if( leader1 != leader2 ){
                ++addEdges;
                minEdge = min(minEdge, nums[i].cost);
                maxEdge = max(maxEdge, nums[i].cost);
                if( size[leader1] < size[leader2] ){
                    parent[leader1] = leader2;
                    size[leader2] += size[leader1];
                }
                else{
                    parent[leader2] = leader1;
                    size[leader1] += size[leader2];
                }
            }
        }

        if( addEdges < n - 1){
            break;
        }
        else{
            answer = min(answer, maxEdge - minEdge);
        }

    }

    if( answer == LLONG_MAX ){
        cout << "NO\n";
    }
    else{
        cout << "YES\n";
        cout << answer << "\n";
    }
    

    return 0;
}
