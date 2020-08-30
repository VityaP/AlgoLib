#include <bits/stdc++.h>
using namespace std;


// Вам дан неориентированный связный граф из n вершин и m рёбер. Для каждого ребра известна стоимость его удаления в тугриках. У вас есть s тугриков. Вы хотите удалить как можно больше рёбер так, чтобы граф оставался связным, а суммарная стоимость всех удалённых рёбер не превосходила s тугриков.
// Входные данные

// Первая строка входных данных содержит три целых числа n, m и s (2 ≤ n ≤ 50 000, 1 ≤ m ≤ 100 000, 0 ≤ s ≤ 1018) — число вершин в графе, число рёбер в графе и число тугриков, соответственно. Следующие m строк содержат описания рёбер графа. Каждое описание состоит из трёх целых чисел — номера вершин, которые соединяет данное ребро, и стоимость удаления ребра в тугриках (стоимость не превосходит 109). В графе не бывает кратных рёбер и петель.
// Выходные данные

// В первой строке выведите максимальное число удаляемых рёбер. Во второй строке выведите номера удаляемых рёбер (рёбра нумеруются с единицы в порядке, данном во входном файле).


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
    int idx;
    friend bool operator<(pt &l, pt &r){
        return (l.cost < r.cost);
    }
};

int main() {

    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    long long n, m, s;
    cin >> n >> m >> s;

    vector<int> parent(n + 1);
    vector<int> size(n + 1);
    for(int i = 0; i <= n; ++i){
        parent[i] = i;
        size[i] = 1;
    }

    vector<pt> nums(m);
    for(int i = 0; i < m; ++i){
        cin >> nums[i].u >> nums[i].v >> nums[i].cost;
        nums[i].idx = i + 1;
    }
    sort(nums.begin(), nums.end());

    int addEdges = 0;
    for(int i = nums.size() - 1; i >= 0; --i){
        if( addEdges == n - 1 ){
            break;
        }
        int leader1 = updateParent(nums[i].u, parent);
        int leader2 = updateParent(nums[i].v, parent);
        if( leader1 != leader2 ){
            ++addEdges;
            nums[i].idx = -1;
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
    vector<int> answer;
    for(int i = 0; i < nums.size(); ++i){
        if( nums[i].idx != -1){
            if( s >= nums[i].cost ){
                answer.push_back(nums[i].idx);
                s-= nums[i].cost;
            }
            else{
                break;
            }
        }
    }

    cout << answer.size() << "\n";
    for(int i = 0; i < answer.size(); ++i){
        cout << answer[i] << " ";
    }
    cout << "\n";

    return 0;
}
