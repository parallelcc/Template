#include<bits/stdc++.h>
using namespace std;
#define N 10005
int dfn[N],low[N],bl[N];
int ind=1;
int h=1;
stack<int> s;
vector<vector<int> > lj(N),lj1(N);
void tarjan(int k)
{
	dfn[k]=low[k]=ind++;
	s.push(k);
	for(int i=0;i<lj[k].size();i++)
	{
		if(!dfn[lj[k][i]])
		{
			tarjan(lj[k][i]);
			low[k]=min(low[k],low[lj[k][i]]);
		}
		else if(!bl[lj[k][i]]) low[k]=min(dfn[lj[k][i]],low[k]);
	}
	if(low[k]==dfn[k])
	{
		int v;
		do
		{
			v=s.top();
			bl[v]=h;
			s.pop();
		}while(v!=k);
		h++;
	}
}
int main()
{
	int n,m;
	while(~scanf("%d%d",&n,&m))
	{
		//init
		for(int i=1;i<=n;i++)
		{
			lj[i].clear();
			lj1[i].clear();
			low[i]=0;
			bl[i]=0;
			dfn[i]=0;
		}
		//input
		for(int i=0;i<m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			lj[u].push_back(v);
		}	
		//solve
		h=1;
		for(int i=1;i<=n;i++)
		{
			if(!bl[i])
			{
				ind=1;
				tarjan(i);
			}
		}
		//gather point
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<lj[i].size();j++)
			{
				if(bl[i]!=bl[lj[i][j]]) lj1[bl[i]].push_back(bl[lj[i][j]]);
			}
		}
	}
	return 0;
}
