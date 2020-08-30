#include <bits/stdc++.h>
using namespace std;


// Hа кольцевой парковке есть n мест пронумерованых от 1 до n. Всего на парковку приезжает n машин в порядке нумерации. У i-й машины известно место pi

// , которое она хочет занять. Если машина приезжает на парковку, а её место занято, то она едет далее по кругу и встаёт на первое свободное место.
// Входные данные

// В первой строке входного файла находится число n
// (1≤n≤300000) — размер парковки и число машин. Во второй строке записаны n чисел, i-е из которых pi (1≤pi≤n) — место, которое хочет занять машина с номером i

// .
// Выходные данные

// Выведите n
// чисел: i-е число — номер парковочного места, которое было занято машиной с номером i.



int updateParent(int x, vector<int> &par){
    if( x != par[x] ){
        par[x] = updateParent(par[x], par);
    }
    return par[x];
}

int main() {

    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> parent(n + 1);
    for(int i = 0; i <= n; ++i){
        parent[i] = i;
    }

    for(int i = 0; i < n; ++i){
        int pos;
        cin >> pos;
        int leader = updateParent(pos, parent);
        cout << leader << " ";
        if( leader + 1 <= n){
            parent[leader] = parent[leader + 1];
        }
        else{
            parent[leader] = parent[1];
        }
        
    }
    cout << "\n";


    return 0;
}
