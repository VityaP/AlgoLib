#include <bits/stdc++.h>
using namespace std;

int main() {
    // freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    int t;
    cin >> t;
    while(t--){

        int n, m, k;
        cin >> n >> m >> k;
        vector<set<int> > G(n + 1);
        vector<int> nums(k);
        for(int i = 0; i < k; ++i){
            cin >> nums[i];
        }
        for(int i = 0; i < m; ++i){
            int u, v;
            cin >> u >> v;
            G[u].insert(v);
            G[v].insert(u);
        }

        bool path = true;
        bool simple = true;
        bool cycle = true;
        if( nums[0] != nums[k - 1] ){
            cycle = false;
        }
        
        set<int> used;
        if( cycle == false ){
            used.insert(nums[0]);
        }
        for(int i = 1; i < k; ++i ){
            int cur = nums[i];
            int prev = nums[i - 1];
            if( G[cur].find(prev) == G[cur].end() ){
                path = false;
                break;
            }

            if( used.find(cur) != used.end() ){
                simple = false;
            }
            else{
                used.insert(cur);
            }
        }

        if( path == false ){
            cout << "none\n";
            continue;
        }
        if( (cycle == true) && (simple == true) ){
            cout << "simple cycle\n";
            continue;
        }

        if( cycle == true ){
            cout << "cycle\n";
            continue;
        }

        if( simple == true ){
            cout << "simple path\n";
            continue;
        }

        cout << "path\n";

    }

    return 0;
}
