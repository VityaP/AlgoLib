#include <bits/stdc++.h>
using namespace std;


// Реализуйте систему непересекающихся множеств. На структуре данных нужно выполнить набор запросов двух типов:

//     union u

// v — объединить два множества, содержащие u и v
// , соответственно;
// get u
// v — проверить лежат ли элементы u и v

//     в одном множестве. 

// Входные данные

// Первая строка входного файла содержит два числа n
// и m (1≤n,m≤105) — число элементов и число запросов. Далее идут m строк запросов, по одному на строке. Для запросов union строка выглядит как union u v (1≤u,v≤n). Для запросов get строка выглядит как get u v (1≤u,v≤n

// ).
// Выходные данные

// Выведите результат каждой операции get по одной на строке в соответствующем порядке: «YES», если элементы лежат в одном множестве, и «NO», в противном случае.



int main() {

    int n, m;
    cin >> n >> m;
    vector<vector<int> >  lists(n);
    vector<int> DSU(n);
    for(int i = 0; i < n; ++i){
        lists[i].push_back(i);
        DSU[i] = i;
    }

    for(int i = 0; i < m; ++i){
        string s;
        int u, v;
        cin >> s;
        cin >> u >> v;
        --u;
        --v;
        if( s[0] == 'u'){
            if( DSU[u] == DSU[v] ){
                continue;
            }
            if( lists[DSU[v]].size() < lists[DSU[u]].size() ){
                //U is head
                //merge V to U
                int size = lists[DSU[v]].size();
                int cell = DSU[v];
                for(int j = 0; j < size; ++j){
                    int x = lists[cell][j];
                    DSU[x] = DSU[u];
                    lists[DSU[u]].push_back(x);
                }
            }
            else{
                //V is head
                //merge U to V
                int size = lists[DSU[u]].size();
                int cell = DSU[u];
                for(int j = 0; j < size; ++j){
                    int x = lists[cell][j];
                    DSU[x] = DSU[v];
                    lists[DSU[v]].push_back(x);
                }
            }
        }
        if( s[0] == 'g'){
            if( DSU[u] == DSU[v] ){
                cout << "YES\n";
            }
            else{
                cout << "NO\n";
            }
        }
    }


    return 0;
}
