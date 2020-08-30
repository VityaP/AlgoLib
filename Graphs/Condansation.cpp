#include <bits/stdc++.h>
using namespace std;

int maxSize = 10010;

vector < vector<int> > g(maxSize);
vector < vector<int> > gr(maxSize);
vector<char> used;
vector<int> order, component;

void dfs1(int v) {
	used[v] = true;
	for(size_t i = 0; i < g[v].size(); ++i){
		if(!used[ g[v][i] ]){
			dfs1(g[v][i]);
		}
	}
	order.push_back(v);
	return;
}
 
void dfs2(int v) {
	used[v] = true;
	component.push_back(v);
	for(size_t i = 0; i < gr[v].size(); ++i){
		if(!used[ gr[v][i] ]){
			dfs2(gr[v][i]);
		}
	}
	return;
}

struct pt
{
	int from;
	int to;
	bool operator==(pt &lhs){
		return ( lhs.from == this->from ) && ( lhs.to == this->to );
	}
};

 
int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int n,m;
	cin >> n >> m;

	int color = 1;
	vector<int> colored(n,0);

	for(int i = 0;i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		g[a].push_back(b);
		gr[b].push_back(a);
	}
 
	used.assign(n, false);
	for(int i = 0; i < n; ++i){
		if(!used[i]){
			dfs1(i);
		}
	}

	used.assign(n, false);	
	for(int i = 0; i < n; ++i){
		int v = order[n - 1 - i];
		if(!used[v]){
			dfs2(v);
			for(int j = 0;j < component.size(); ++j){
				colored[component[j]] = color;
			}
			++color;
			component.clear();
		}
	}

	set<pair<int,int> > answer;
	int amount = 0;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < g[i].size(); ++j){
			if( colored[i] != colored[g[i][j]] ){
				pt tmp;
				tmp.from = colored[i];
				tmp.to = colored[g[i][j]];
				answer.insert( make_pair(colored[i],colored[g[i][j]]) );
			}
		}
	}
	
	cout << answer.size() << "\n";

	return 0;
}