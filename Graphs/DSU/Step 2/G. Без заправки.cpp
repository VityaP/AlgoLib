#include <bits/stdc++.h>
using namespace std;


// Между пунктами с номерами 1, 2, ..., n проложено несколько дорог. Длина каждой дороги известна. По этой системе дорог можно добраться из любого упомянутого пункта в любой другой. Автозаправки расположены только в пунктах. Требуется определить, какое максимальное расстояние без заправки должен быть в состоянии проезжать автомобиль, чтобы без проблем передвигаться между пунктами.
// Входные данные

// В первой строке входного файла находятся числа n и k (1 ≤ n ≤ 1 500, 1 ≤ k ≤ 400 000) — число пунктов и число дорог, соответственно. В следующих k строках указаны пары пунктов, связанные дорогой, и расстояние между ними — неотрицательное целое число километров, не превышающее 10 000.
// Выходные данные

// В выходном файле должно оказаться одно число — длина максимального пробега без дозаправки.



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
    for(int i = 0; i <= n; ++i){
        parent[i] = i;
    }

    vector<pt> nums(m);
    for(int i = 0; i < m; ++i){
        cin >> nums[i].u >> nums[i].v >> nums[i].cost;
    }
    sort(nums.begin(), nums.end());

    int addEdges = 0;
    int answer = 0;
    for(int i = 0; i < nums.size(); ++i){
        if( addEdges == n - 1 ){
            break;
        }
        int leader1 = updateParent(nums[i].u, parent);
        int leader2 = updateParent(nums[i].v, parent);
        if( leader1 != leader2 ){
            ++addEdges;
            answer = max(answer, nums[i].cost);
            parent[leader2] = leader1;
        }
    }

    cout << answer << "\n";

    return 0;
}
