#include <bits/stdc++.h>
using namespace std;

int currentTime = 0;
set<int> answer;

void dfs(int v,int pv,vector<int>& tIn,vector<int>& tUp,vector< vector<int> >& adj,vector<bool>& used){
	used[v] = true;
	tIn[v] = currentTime;
	tUp[v] = currentTime;
	++currentTime;
	int cnt = 0;
	for( auto u : adj[v]){
		if( u == pv ){
			continue;
		}
		if( used[u] ){
			tUp[v] = min( tUp[v],tIn[u] );
		}
		else{
			dfs(u,v,tIn,tUp,adj,used);
			tUp[v] = min( tUp[v],tUp[u] );
			if (tUp[u] >= tIn[v] && pv != -1){
				answer.insert(v);
			}
			++cnt;
		}
	}
	if( pv == -1 && cnt > 1 ){
		answer.insert(v);
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	
	int n,m;
	cin >> n >> m;
	vector< vector<int> > adj(n + 1);
	vector<int> tIn(n + 1);
	vector<int> tUp(n + 1);
	vector<bool> used(n + 1,false);

	int temp1,temp2;
	for(int i = 1; i <= m; ++i){
		cin >> temp1 >> temp2;
		adj[temp1].push_back(temp2);
		adj[temp2].push_back(temp1);
	}
	
	for(int i = 1; i <= n; ++i){
		if( !used[i] ){	
			dfs(i,-1,tIn,tUp,adj,used);
		}
	}

	cout << answer.size() << "\n";
	for(auto it = answer.begin(); it != answer.end(); ++it){
		cout << *it << "\n";
	}
	
	return 0;	  
}