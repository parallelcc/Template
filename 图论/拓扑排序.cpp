#include<iostream>
#include<cstdio>
#include<cmath>
#include<sstream>
#include<cstring>
#include<string>
#include<map>
#include<vector>
#include<queue>
#include<set>
#include<list>
#include<algorithm>
#include<stack>
using namespace std;
#define LL long long int
#define INF 0x3f3f3f3f
#define MAXN 150005//点最大值 
int n,m;//点、边数 
int jg[MAXN+5];//结果 
int ds[MAXN+5];//每个点的入度数 
int topsort()
{
	if(~scanf("%d%d",&n,&m)==0)	return 0;
	//初始化
	int h=0;
	fill(ds,ds+n+1,0); 
	vector<vector<int> > lj(n+5);//邻接表 
	//输入
	for(int i=0;i<m;i++)
	{
		int e,v;
		scanf("%d%d",&e,&v);
		lj[e].push_back(v); 
		ds[v]++;
	}
	queue<int> ld;//入度为0的点的队列 
	for(int i=1;i<=n;i++)//标号从1开始 
	{
		if(ds[i]==0) ld.push(i); 
	}
	if(!ld.empty()) 
	{
		while(!ld.empty())
		{
			jg[h]=ld.front();
			for(int i=0;i<lj[jg[h]].size();i++)
			{
				ds[lj[jg[h]][i]]--;
				if(ds[lj[jg[h]][i]]==0) ld.push(lj[jg[h]][i]);
			}
			//lj[jg[h]].clear();//将入度为0的点从图中去掉 
			h++;
			ld.pop();
		}
		if(h==n)
		{
			//输出 
			for(int i=0;i<n;i++) 
			{
				if(i!=n-1) printf("%d ",jg[i]);
				else printf("%d\n",jg[i]);
			}
		}
		//else 有环 
	}
	//else 有环 
	return 1; 
}
int main()
{
	while(topsort());
	return 0; 
} 
