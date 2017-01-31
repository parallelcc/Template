//o(V*V)
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN 200//点最大值 
int lj[MAXN+1][MAXN+1];//邻接矩阵 
int us[MAXN+1];//是否已用 
int pre[MAXN+1];//路径 
int n,m;//点、边数 
int S,N;//起点，终点 
//输出路径 
void printpath(int k)
{
	if(k==S) printf("%d->",S);
	else
	{
		printpath(pre[k]);
		if(k==N) printf("%d\n",N);
		else printf("%d->",k);
	}
}
int dij()
{
	if(~scanf("%d%d",&n,&m)==0) return 0;
	//初始化 
	S=1;
	N=n;
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
	vector<int> a(n+1);//每个点到S的最短距离  
	fill(a.begin(),a.end(),INF);
	a[S]=0;
	while(us[N]==0)
	{
		int min=INF,mini=S; 
		for(int i=1;i<=n;i++)//找到没用过的到S的距离最短的一个点 
		{
			if(us[i]==0&&min>a[i])
			{
				min=a[i];
				mini=i;
			}
		}
		if(min==INF) break;
		us[mini]=1;
		for(int i=1;i<=n;i++)//更新没用过的点到S的最短距离 
		{
			if(us[i]==0&&a[i]>a[mini]+lj[mini][i]) 
			{
				a[i]=a[mini]+lj[mini][i];
				pre[i]=mini;//存储路径 
			}
		}
	}
	//结果 
	if(us[N]) 
	{
		printf("%d\n",a[N]);
		printpath(N);
	}
	//else 不存在从S到N的路径
	return 1;
}
int main()
{
	while(dij());
	return 0;
} 
