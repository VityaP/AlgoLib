#include <bits/stdc++.h>
using namespace std;


// Задан неориентированный граф на n вершинах без рёбер. Каждая вершина графа в каждый момент времени покрашена в один из цветов: 0 или 1

//  — и верно, что цвета вершин, между которыми есть ребро, различны.

// Поступают два вида запросов:

//     Заданы два элемента x

// и y из разных компонент связности: добавить в граф ребро (x,y)
// , изменив цвета вершин для соответствия условию.
// Заданы два элемента x
// и y

//     из одной компоненты связности: ответить, правда ли, что их цвета различаются. 

// Входные данные

// В первой строке содержится два целых числа n
// и m (1≤n,m≤2⋅105

// ) — число вершин в графе и число запросов, соответственно. Вершины нумеруются с нуля.

// В последующих m

// строках содержится описание запросов.

//     Запрос первого вида имеет вид: «0 a

// b» (1≤a,b≤n), означающий, что нужно объединить компоненты с вершинами x и y, такие что xmodn=(a+shift)modn и ymodn=(b+shift)modn
// Запрос второго типа имеет вид: «1 a
// b» (1≤a,b≤n), означающий, что нужно проверить различность цветов вершин x и y, таких что xmodn=(a+shift)modn и ymodn=(b+shift)modn

// Если ответ на этот запрос — да, то нужно выполнить присвоение shift=(shift+1)modn

//     . 

// Изначально shift

// равен нулю.
// Выходные данные

// Для каждого запроса второго типа выведите в отдельной строке: «YES», если цвета вершин различны, иначе, «NO».




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

void Union(int a, int b, vector<int> &parent, vector<int> &len, vector<int> &size){
    auto leaderA = Get(a, parent, len, size);
    auto leaderB = Get(b, parent, len, size);
    if( size[leaderA.first] > size[leaderB.first] ){
        swap(leaderA, leaderB);
    }
    parent[leaderA.first] = leaderB.first;
    len[leaderA.first] = (1 + leaderA.second + leaderB.second) % 2;
    size[leaderB.first] += size[leaderA.first];
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

    int shift = 0;

    for(int i = 0; i < m; ++i){
        string s;
        int a, b;
        cin >> s >> a >> b;
        if( s[0] == '0' ){
            a = (a + shift) % n;
            b = (b + shift) % n;
            Union(a, b, parent, len, size);
        }
        if( s[0] == '1' ){
            a = (a + shift) % n;
            b = (b + shift) % n;
            auto leaderA = Get(a, parent, len, size);
            auto leaderB = Get(b, parent, len, size);
            if( leaderB.second == leaderA.second ){
                cout << "Yes\n";
                shift = (shift + 1) % n;
            }
            else{
                cout << "No\n";
            }
        }
    }
    


    return 0;
}
