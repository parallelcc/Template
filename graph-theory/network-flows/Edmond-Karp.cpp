#include<bits/stdc++.h>
using namespace std;
#define N 10005
struct node
{
	int num,cap,rev;
	node(int num,int cap,int rev)
	{
		this->num=num;
		this->cap=cap;
		this->rev=rev;
	}
};
vector<vector<node> > lj(N);
pair<int,int> pre[N];
int flow[N];
int n,m;
int bfs(int s,int d)
{
	fill(flow,flow+n+1,0);
	flow[s]=0x3f3f3f3f;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int p=q.front();
		q.pop();
		for(int i=0;i<lj[p].size();i++)
		{
			if(!flow[lj[p][i].num]&&lj[p][i].cap>0)
			{
				pre[lj[p][i].num].first=p;
				pre[lj[p][i].num].second=i;
				flow[lj[p][i].num]=min(lj[p][i].cap,flow[p]);
				if(lj[p][i].num==d) return flow[d];
				q.push(lj[p][i].num);
			}
		}
	}
	return 0;
}
int maxflow(int s,int d)
{
	int flow=0;
	int sumflow=0;
	while(flow=bfs(s,d))
	{
		int k=d;
		while(k!=s)
		{
			int l=pre[k].first;
			int i=pre[k].second;
			lj[l][i].cap-=flow;
			lj[lj[l][i].num][lj[l][i].rev].cap+=flow;
			k=l;
		}
		sumflow+=flow;
	}
	return sumflow;
}
int init()
{
	if(~scanf("%d%d",&n,&m)==0) return 0;
	for(int i=1;i<=n;i++) lj[i].clear();
	for(int i=0;i<m;i++)
	{
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		lj[u].push_back(node(v,c,lj[v].size()));
		lj[v].push_back(node(u,0,lj[u].size()-1));
	}
	return 1;
}
int main()
{
	while(init())
	{
		printf("%d\n",maxflow(1,n));
	}
}
