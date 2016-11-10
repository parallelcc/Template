#include<bits/stdc++.h>
using namespace std;
#define N 10005
int dfn[N],low[N],bl[N];
int ind=1,h=1;
vector<vector<int> > lj(N);
stack<int> s;
void tarjan(int k,int l)
{
	dfn[k]=low[k]=ind++;
	for(int i=0;i<lj[k].size();i++)
	{
		if(!dfn[lj[k][i]])
		{
			s.push(lj[k][i]);
			tarjan(lj[k][i],k);
			low[k]=min(low[k],low[lj[k][i]]);
			//bridge 
			if(low[lj[k][i]] > dfn[k])
			{
				while(s.top()!=lj[k][i])
				{
					bl[s.top()]=h;
					s.pop();
				}
				bl[s.top()]=h;
				s.pop();
				h++;
			}
		}
		else if(lj[k][i]!=l) low[k]=min(low[k],dfn[lj[k][i]]);
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
			bl[i]=0;
			lj[i].clear();
			low[i]=0;
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
		while(!s.empty())
		{
			bl[s.top()]=h;
			s.pop();
		}
	}
	return 0;
}
