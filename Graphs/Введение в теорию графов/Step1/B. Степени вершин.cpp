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
        vector<int> degree(n + 1, 0);
        for(int i = 0; i < m; ++i){
            int u, v;
            cin >> u >> v;
            degree[u]++;
            degree[v]++;
        }
        for(int i = 1; i <= n; ++i){
            cout << degree[i] << " ";
        }
        cout << "\n";
    }
    


    return 0;
}
