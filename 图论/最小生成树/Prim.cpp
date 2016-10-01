//o(V*V)  稠密图 
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<map>
#include<vector>
#include<queue>
#include<set>
#include<list>
#include<algorithm>
using namespace std;
#define ll long long int
#define INF 0x3f3f3f3f       
#define MAXN 200//点最大值 
int lj[MAXN+1][MAXN+1];//邻接矩阵 
int us[MAXN+1];//是否已用 
int n,m;//点、边数 
int Prim()
{
	if(~scanf("%d%d",&n,&m)==0) return 0;
	//初始化 
	int qz=0,us_num=0;//权值和、用过的点数 
	for(int i=1;i<=n;i++) //标号从1开始 
	{
		fill(lj[i],lj[i]+n+1,INF);
		lj[i][i]=0;
	}
	fill(us,us+n+1,0);
	//输入 
	for(int i=0;i<m;i++)
	{
		int v,e,w;
		scanf("%d%d%d",&v,&e,&w);
		if(lj[v][e]>w) 
		{
			lj[v][e]=w;	
			lj[e][v]=w;
		}//无向图 
	}
	//核心 
	vector<int> a(n+1);//每个点到树的最短距离  
	fill(a.begin(),a.end(),INF);
	a[1]=0;//标号从1开始 
	while(us_num!=n)
	{
		int min=INF,mini=1; 
		for(int i=1;i<=n;i++)//找到没用过的到树的距离最短的一个点 
		{
			if(us[i]==0&&min>a[i])
			{
				min=a[i];
				mini=i;
			}
		}
		if(min==INF) break;
		us[mini]=1;
		qz+=min;
		us_num++;
		for(int i=1;i<=n;i++)//更新没用过的点到树的最短距离 
		{
			if(us[i]==0&&a[i]>lj[mini][i]) 
			{
				a[i]=lj[mini][i];
			}
		}
	}
	//结果 
	if(us_num==n) 
	{
		printf("%d\n",qz);
	}
	//else 非连通图 
	return 1;
}
int main()
{
	while(Prim());
	return 0;
} 
