#include <bits/stdc++.h>
using namespace std;

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
    vector<int> size(n);
    for(int i = 0; i < n; ++i){
        parent[i] = i;
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
                parent[leaderU] = leaderV;
            }
            else{
                size[leaderU] += size[leaderV];
                parent[leaderV] = leaderU;
            }
        }

        if( s[0] == 'g' ){
            cin >> v;
            --v;
            int leader = updateParent(v, parent);
            cout  << size[leader] << "\n";
        }
    }


    return 0;
}
