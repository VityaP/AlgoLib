#include <bits/stdc++.h>
using namespace std;

int main() {
    // freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<set<int> > G(n + 1);
        bool ok = true;
        for(int i = 0; i < m; ++i){
            int u, v;
            cin >> u >> v;
            if( G[u].find(v) != G[u].end()){
                ok = false;
            }
            if( u == v){
                ok = false;
            }
            G[u].insert(v);
            G[v].insert(u);
        }
        if( ok == true ){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }


    return 0;
}
