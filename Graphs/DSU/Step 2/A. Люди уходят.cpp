#include <bits/stdc++.h>
using namespace std;



// Люди стоят в шеренге на позициях с 1 до n

// . Нужно выполнить набор запросов следующих двух типов:

//     «- x

// » — человек с позиции x
// ушёл;
// «? x

//     » — найти ближайшего человека справа, который ещё стоит. 

// Входные данные

// Первая строка входного файла содержит два числа n
// и m (1≤n,m≤106) — число людей и число запросов. Далее идут m строк запросов, по одному на строке. Для запросов на уход человека строка выглядит как «- x» (1≤x≤n). Для запросов на ближайшего человека справа строка выглядит как «? x» (1≤x≤n

// ). Известно, что все позиции, с которых уходят люди, различны.
// Выходные данные

// Выведите результат каждой операции «?» по одной на строке в соответствующем порядке. Если справа человека нет — выведите «-1».



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
    vector<int> parent(n + 1);
    // vector<int> size(n);
    // vector<int> max(n);
    // vector<int> min(n);
    for(int i = 0; i <= n; ++i){
        parent[i] = i;
        // size[i] = 1;
        // max[i] = i;
        // min[i] = i;
    }

    for(int i = 0; i < m; ++i){
        string s;
        int x;
        cin >> s;
        cin >> x;

        if( s[0] == '-' ){
            if( x == n){
                parent[x] = 0;
            }
            else{
                parent[x] = x + 1;
            }
        }

        if( s[0] == '?' ){
            int leader = updateParent(x, parent);
            if( leader == 0){
                cout << -1 << "\n";
            }
            else{
                cout << leader << "\n";
            }
        }

    }


    return 0;
}
