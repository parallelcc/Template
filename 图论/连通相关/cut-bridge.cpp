#include<bits/stdc++.h>
using namespace std;
#define N 10005
int dfn[N],low[N],add_block[N];
int ind=1;
vector<vector<int> > lj(N);
vector<pair<int,int> > bridge;
void tarjan(int k,int l)
{
	dfn[k]=low[k]=ind++;
	int son=0;
	for(int i=0;i<lj[k].size();i++)
	{
		if(!dfn[lj[k][i]])
		{
			son++;
			tarjan(lj[k][i],k);
			low[k]=min(low[k],low[lj[k][i]]);
			//bridge 
			if(low[lj[k][i]] > dfn[k])
			{
				int u=min(k,lj[k][i]);
				int v=max(k,lj[k][i]);
				bridge.push_back(make_pair(u,v));
			}
			//not root - cut point 
			if(k!=l&&low[lj[k][i]]>=dfn[k])
			{
				add_block[k]++;
			}
		}
		else if(lj[k][i]!=l) low[k]=min(low[k],dfn[lj[k][i]]);
	}
	//root - cut point
	if(k==l) add_block[k]=son-1;
}
int main()
{
	int n,m;
	while(~scanf("%d%d",&n,&m))
	{
		//init
		bridge.clear();
		for(int i=1;i<=n;i++)
		{
			lj[i].clear();
			low[i]=0;
			add_block[i]=0;
			dfn[i]=0;
		}
		//input
		for(int i=0;i<m;i++)
		{
			int u,v;
			scanf("%d %d",&u,&v);
			/*u++;
			v++;*/
			lj[u].push_back(v);
			lj[v].push_back(u);
		}	
		//solve 
		for(int i=1;i<=n;i++)
		{
			if(!dfn[i])
			{
				ind=1;
				tarjan(i,i);
			}
		}
	}
	return 0;
}
