#include <bits/stdc++.h>
using namespace std;


// Двудольным графом называется такой неориентированный граф, все вершины которого можно разбить на две доли так, что ребра соединяют только вершины разных долей.

// В этой задаче к пустому графу из n вершин последовательно добавляют m ребер. Ваша задача состоит в том, чтобы вывести номер первого такого ребра, после добавления которого граф перестает быть двудольным.

// Пустым графом из n вершин называется граф из n вершин, не содержащий ребер вообще.
// Входные данные

// В первой строке записаны целые числа n и m (1 ≤ n, m ≤ 3·105) — число вершин в графе и число вставляемых рёбер, соответственно. Далее в m строках записана информация об m ребрах в виде пар a i, b i (1 ≤ a i, b i ≤ n). Граф не содержит кратных ребер и петель в любой момент времени.
// Выходные данные

// Выведите номер искомого ребра (нумеруются от 1 в порядке их появления во входных данных) или «-1», если такого ребра нет.



// pair<int parent, int length>
pair<int, int> Get(int x, vector<int> &parent, vector<int> &len, vector<int> &size){
    if( x == parent[x] ){
        return {x, 0};
    }
    auto tmp = Get(parent[x], parent, len, size);
    parent[x] = tmp.first;
    len[x] = (len[x] + tmp.second) % 2;
    return {parent[x], len[x]};
}


int main() {

    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> parent(n + 1);
    vector<int> len(n + 1);
    vector<int> size(n + 1);
    for(int i = 1; i <= n; ++i){
        parent[i] = i;
        len[i] = 0;
        size[i] = 1;
    }

    int answer = -1;
    for(int i = 0; i < m; ++i){
        
        int a, b;
        cin >> a >> b;
        auto leader1 = Get(a, parent, len, size);
        auto leader2 = Get(b, parent, len, size);
        if( leader1.first == leader2.first ){
            if( leader1.second == leader2.second ){
                answer = i + 1;
                break;
            }
        }
        else{
            if( size[leader1.first] < size[leader2.first] ){
                swap(leader1, leader2);
            }
            
            parent[leader2.first] = leader1.first;
            size[leader1.first] += size[leader2.first];
            if( leader1.second == leader2.second ){
                len[leader2.first] ^= 1;
            }
        }
    }

    cout << answer << "\n";
    


    return 0;
}
