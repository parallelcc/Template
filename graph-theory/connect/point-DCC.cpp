#include<bits/stdc++.h>
using namespace std;
#define N 10005
#define M 10005
int dfn[N],low[N];
int ind=1,h=1;
stack<pair<int,int> > s;
vector<vector<int> > lj(N);
vector<vector<pair<int,int> > > edge(M);
void tarjan(int k,int l)
{
	dfn[k]=low[k]=ind++;
	for(int i=0;i<lj[k].size();i++)
	{
		if(!dfn[lj[k][i]])
		{
			s.push(make_pair(k,lj[k][i]));
			tarjan(lj[k][i],k);
			low[k]=min(low[k],low[lj[k][i]]);
			//find it is cut
			if(dfn[k]<=low[lj[k][i]])
			{
				while(s.top().first!=k||s.top().second!=lj[k][i])
				{
					edge[h].push_back(s.top());
					s.pop();
				}
				edge[h].push_back(s.top());
				s.pop();
				h++;
			}
		}
		else if(lj[k][i]!=l) 
		{
			low[k]=min(low[k],dfn[lj[k][i]]);
			//edge connect to ancestors
			if(dfn[k]>dfn[lj[k][i]]) s.push(make_pair(k,lj[k][i]));
		}
	}
}
int main()
{
	int n,m;
	while(~scanf("%d%d",&n,&m))
	{
		//init
		h=1;
		for(int i=1;i<=n;i++)
		{
			lj[i].clear();
			low[i]=0;
			dfn[i]=0;
		}
		for(int i=1;i<=m;i++) edge[i].clear();
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
		for(int i=1;i<h;i++) 
		{
			for(auto j:edge[i]) cout<<j.first<<" "<<j.second<<endl;
			cout<<endl;
		}
	}
	return 0;
}
