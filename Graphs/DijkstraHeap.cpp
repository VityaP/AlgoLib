#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <queue>
#include <stack>
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
//#pragma GCC optimization ("unroll-loops")

using namespace std;
using ll = long long;

#define endl "\n"
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

const ll INF = 1e12;


struct edge {
    int to;
    long long w;
};

int n, m, start;
vector< vector<edge> > g;
vector<long long> dist;


void Dijkstra(){

    priority_queue< pair<long long, int>, vector< pair<long long, int> >, std::greater<pair<long long, int> > > minQ;

    for(int i = 0; i < n; i++) {
        if( i != start ){
            dist[i] = INF;
            minQ.push(make_pair(INF, i));
        }
    }
    dist[start] = 0;
    minQ.push(make_pair(0, start));

    while (!minQ.empty()) {
        int curentV = minQ.top().second;
        long long curentDist = minQ.top().first;
        minQ.pop();
        if(curentDist > dist[curentV]){
            continue;
        }
        for (int i = 0; i < (int) g[curentV].size(); i++) {
            int to = g[curentV][i].to;
            long long w = g[curentV][i].w;
            if (curentDist + w < dist[to]) {
                dist[to] = curentDist + w;
                minQ.push(make_pair(dist[to], to));
            }
        }
    }

    return;
}

int main() {

    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> start;
    --start;
    g.resize(n);
    dist.resize(n);
    edge e;
    for (int i = 0; i < m; i++){
        int a, b;
        long long w;
        cin >> a >> b >> w;
        --a;
        --b;

        e.to = b;
        e.w = w;
        g[a].push_back(e);

        //if undirected graph
        e.to = a;
        e.w = w;
        g[b].push_back(e);
    }

    Dijkstra();

    for(int i = 0; i < n; ++i){
        if( dist[i] == INF ){
            cout << -1 << " ";
        }
        else{
            cout << dist[i] << " ";
        }
    }
    cout << "\n";


    return 0;
}


