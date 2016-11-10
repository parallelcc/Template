#include<bits/stdc++.h>
using namespace std;
#define N 1005
struct node{
	int num, cap, rev;
	node(int num, int cap, int rev){
		this->num = num;
		this->cap = cap;
		this->rev = rev;
	}
};
vector<vector<node> > lj(N);
int dis[N], cur[N];
int n, m;
int s, d;
int bfs(){
	fill(dis, dis + n + 1, 0);
	dis[s] = 1;
	queue<int> q;
	q.push(s);
	whiler(!q.empty()){
		int p = q.front();
		q.pop();
		for (int i = 0; i < lj[p].size(); i++){
			if (!dis[lj[p][i].num] && lj[p][i].cap > 0){
				dis[lj[p][i].num] = dis[p] + 1;
				if (lj[p][i].num == d) return 1;
				q.push(lj[p][i].num);
			}
		}
	}
	return 0;
}
int Dinic(int p, int low){
	if (p == d) return low;
	int flow = 0;
	for (int &i = cur[p]; i < lj[p].size(); i++){
		if (dis[lj[p][i].num] == dis[p] + 1 && lj[p][i].cap > 0){
			int k = Dinic(lj[p][i].num, min(low, lj[p][i].cap));
			lj[p][i].cap -= k;
			lj[lj[p][i].num][lj[p][i].rev].cap += k;
			flow += k;
			low -= k;
			if (low == 0) break;
		}
	}
	return flow;
}
int init(){
	if (~scanf("%d%d", &n, &m) == 0) return 0;
	s = 1;
	d = n;
	for (int i = 1; i <= n; i++) lj[i].clear();
	for (int i = 0; i < m; i++)
	{
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		lj[u].push_back(node(v, c, lj[v].size()));
		lj[v].push_back(node(u, 0, lj[u].size() - 1));
	}
	return 1;
}
int solve(){
	int ans = 0;
	while (bfs()){
		fill(cur, cur + n + 1, 0);
	  	ans += Dinic(s, 0x3f3f3f3f);
	}
	printf("%d\n", ans);
}
int main(){
	while (init()) solve();
	return 0;
}
