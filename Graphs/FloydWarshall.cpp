#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstring>
#include <chrono>
#include <complex>
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
//#pragma GCC optimization ("unroll-loops")
using namespace std;
using ll = long long;
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()


vector< vector<ll> > dist;

int main() {
    //freopen("treemaster.in", "r", stdin);
    //freopen("treemaster.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    dist.resize(n, vector<ll>(n));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> dist[i][j];
        }
    }

    for(int k = 0; k < n; ++k){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j] );
            }
        }
    }
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
