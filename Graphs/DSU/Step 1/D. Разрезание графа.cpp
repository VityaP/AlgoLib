#include <bits/stdc++.h>
using namespace std;


// Дан неориентированный граф. Над ним в заданном порядке производят операции следующих двух типов:

//     cut u v — удалить из графа ребро u - v;
//     ask u v — проверить, лежат ли две вершины u и v в одной компоненте связности. 

// Известно, что после выполнения всех операций типа cut, рёбер в графе не осталось. Найдите результат выполнения каждой из операций типа ask.
// Входные данные

// Первая строка входного файла содержит три целых числа, разделённые пробелами n, m и k (1 ≤ n ≤ 50 000, 0 ≤ m ≤ 100 000, m ≤ k ≤ 150 000) — количество вершин графа, количество рёбер и количество операций, соответственно.

// Следующие m строк задают рёбра графа; i-я из этих строк содержит два числа u i и v i (1 ≤ u i,  v i ≤ n), разделённые пробелами — номера концов i-го ребра. Вершины нумеруются с единицы; граф не содержит петель и кратных рёбер.

// Далее следуют k строк, описывающих операции. Операция типа cut задаётся строкой «cut u v» (1 ≤ u,  v ≤ n), которая означает, что из графа удаляют ребро между вершинами u и v. Операция типа ask задаётся строкой «ask u v» (1 ≤ u,  v ≤ n), которая означает, что необходимо узнать, лежат ли в данный момент вершины u и v в одной компоненте связности. Гарантируется, что каждое ребро графа встретится в операциях типа cut ровно один раз.
// Выходные данные

// Для каждой операции ask во входном файле выведите на отдельной строке слово «YES», если две указанные вершины лежат в одной компоненте связности, и «NO» в противном случае. Порядок ответов должен соответствовать порядку операций ask во входном файле.




int updateParent(int x, vector<int> &par){
    if( x != par[x] ){
        par[x] = updateParent(par[x], par);
    }
    return par[x];
}

int main() {

    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> parent(n);
    vector<int> size(n);
    // vector<int> max(n);
    // vector<int> min(n);


    for(int i = 0; i < n; ++i){
        parent[i] = i;
        size[i] = 1;
        // max[i] = i;
        // min[i] = i;
    }

    for(int i = 0; i < m; ++i){
        int vert1, vert2;
        cin >> vert1 >> vert2;
    }

    vector<tuple<string, int, int> > memory(k);
    for(int i = 0; i < k; ++i){
        string s;
        int u, v;
        cin >> s >> u >> v;
        memory[i] = make_tuple(s, u, v);
    }
    
    vector<string> answer;
    for(int i = k - 1; i >= 0; --i){
        string s;
        int u, v;
        s = get<0>(memory[i]);
        u = get<1>(memory[i]);
        v = get<2>(memory[i]);
        --u;
        --v;

        if( s[0] == 'c' ){
            
            int leaderU = updateParent(u, parent);
            int leaderV = updateParent(v, parent);
            if( leaderU == leaderV ){
                continue;
            }
            if( size[leaderU] < size[leaderV] ){
                size[leaderV] += size[leaderU];
                parent[leaderU] = leaderV;
                // max[leaderV] = std::max(max[leaderV], max[leaderU]);
                // min[leaderV] = std::min(min[leaderV], min[leaderU]);
            }
            else{
                size[leaderU] += size[leaderV];
                parent[leaderV] = leaderU;
                // max[leaderU] = std::max(max[leaderV], max[leaderU]);
                // min[leaderU] = std::min(min[leaderV], min[leaderU]);
            }
        }

        if( s[0] == 'a' ){
            int leader1 = updateParent(u, parent);
            int leader2 = updateParent(v, parent);
            if( leader1 == leader2 ){
                answer.push_back("YES\n");
            }
            else{
                answer.push_back("NO\n");
            }
        }
    }

    for(auto it = answer.rbegin(); it != answer.rend(); ++it){
        cout << *it;
    }


    return 0;
}
