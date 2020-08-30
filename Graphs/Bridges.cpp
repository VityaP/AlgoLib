#include <bits/stdc++.h>
using namespace std;

int currentTime = 0;
int amount = 0;
set<int> answer;
struct pt
{
	int value;
	int ord;
};

void dfs(pt v,pt pv,vector<int>& tIn,vector<int>& tUp,vector< vector<pt> >& adj,vector<bool>& used){
	used[v.value] = true;
	tIn[v.value] = currentTime;
	tUp[v.value] = currentTime;
	++currentTime;
	for( auto u : adj[v.value]){
		if( u.value == pv.value ){
			continue;
		}
		if( used[u.value]){
			tUp[v.value] = min( tUp[v.value],tIn[u.value] );
		}
		else{
			dfs(u,v,tIn,tUp,adj,used);
			tUp[v.value] = min( tUp[v.value],tUp[u.value] );
		}
	}
	if( pv.value != -1 && tUp[v.value] == tIn[v.value] ){
		++amount;
		answer.insert(v.ord);
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	
	int n,m;
	cin >> n >> m;
	vector< vector<pt> > adj(n + 1);
	int value1,value2;
	pt temp1;
	pt temp2;
	for(int i = 1; i <= m; ++i){
		cin >> temp1.value >> temp2.value;
		temp1.ord = i;
		temp2.ord = i;
		adj[temp1.value].push_back(temp2);
		adj[temp2.value].push_back(temp1);
	}
	vector<int> tIn(n + 1);
	vector<int> tUp(n + 1);
	vector<bool> used(n + 1,false);

	for(int i = 1; i <= n; ++i){
		if( !used[i] ){
			temp1.value = i;
			temp1.ord = 0;
			temp2.value = -1;
			temp2.ord = 0;
			dfs(temp1,temp2,tIn,tUp,adj,used);
		}
	}
	cout << amount << "\n";
	for(auto it = answer.begin(); it != answer.end(); ++it){
		cout << *it << " ";
	}
	cout << "\n";
	
	return 0;	  
}
