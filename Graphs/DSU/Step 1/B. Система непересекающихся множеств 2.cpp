#include <bits/stdc++.h>
using namespace std;

// Реализуйте систему непересекающихся множеств. На структуре данных нужно выполнить набор запросов двух типов:

//     union u

// v — объединить два множества, содержащие u и v
// , соответственно;
// get v
//  — найти множество, которому принадлежит v

//     , найти минимальный и максимальный элемент, а также число элементов в множестве. 

// Входные данные

// Первая строка входного файла содержит два числа n
// и m (1≤n,m≤3⋅105) — число элементов и число запросов. Далее идут m строк запросов, по одному на строке. Для запросов union строка выглядит как union u v (1≤u,v≤n). Для запросов get строка выглядит как get v (1≤v≤n

// ).
// Выходные данные

// Выведите результат каждой операции get по одной на строке в соответствующем порядке. Каждый результат состоит из трёх чисел: минимальный элемент, максимальный элемент и число элементов. 







int updateParent(int x, vector<int> &par){
    if( x != par[x] ){
        par[x] = updateParent(par[x], par);
    }
    return par[x];
}

int main() {

    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> parent(n);
    vector<int> max(n);
    vector<int> min(n);
    vector<int> size(n);
    for(int i = 0; i < n; ++i){
        parent[i] = i;
        max[i] = i;
        min[i] = i;
        size[i] = 1;
    }

    for(int i = 0; i < m; ++i){
        string s;
        int u, v;
        cin >> s;

        if( s[0] == 'u' ){
            cin >> u >> v;
            --u;
            --v;
            int leaderU = updateParent(u, parent);
            int leaderV = updateParent(v, parent);
            if( leaderU == leaderV ){
                continue;
            }
            if( size[leaderU] < size[leaderV] ){
                size[leaderV] += size[leaderU];
                max[leaderV] = std::max(max[leaderV], max[leaderU]);
                min[leaderV] = std::min(min[leaderV], min[leaderU]);
                parent[leaderU] = leaderV;
            }
            else{
                size[leaderU] += size[leaderV];
                max[leaderU] = std::max(max[leaderV], max[leaderU]);
                min[leaderU] = std::min(min[leaderV], min[leaderU]);
                parent[leaderV] = leaderU;
            }
        }

        if( s[0] == 'g' ){
            cin >> v;
            --v;
            int leader = updateParent(v, parent);
            cout << min[leader] + 1 << " " << max[leader] + 1 << " " << size[leader] << "\n";
        }
    }


    return 0;
}
