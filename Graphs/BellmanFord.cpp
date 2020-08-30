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
    int from, to;
    ll w;
};

int n, m, start;
vector<ll> dist;


void BellmanFord(vector<edge> &e){

    //time complexity O(V * E)

    dist.assign(n, INF);
    dist[start] = 0LL;

    for(int i = 0; i < n; i++) {
        bool changed = false;
        for(int j = 0; j < e.size(); j++) {
            int from = e[j].from;
            int to = e[j].to;
            ll w = e[j].w;
            if( (dist[from] != INF) && (dist[from] + w < dist[to] ) ){
                dist[to] = dist[from] + w;
                changed = true;
            }
        }
        if( !changed ){
            break;
        }
    }

    for(int i = 0; i < n; ++i){
        if( dist[i] != INF ){
            cout << dist[i] << " ";
        }
        else{
            cout << -1 << " ";
        }
    }
    cout << endl;

    return;
}


int main() {

	//freopen("treemaster.in", "r", stdin);
  	//freopen("treemaster.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> start;
	--start;

  vector<edge> e;
  for(int i = 0; i < m; i++) {
      edge curEdge;
      int u, v;
      cin >> u >> v >> curEdge.w;
      --u;
      --v;
      curEdge.from = u;
      curEdge.to = v;
      e.push_back(curEdge);
      //undirected graph
      curEdge.from = v;
      curEdge.to = u;
      e.push_back(curEdge);
  }


  BellmanFord(e);

	return 0;
}
