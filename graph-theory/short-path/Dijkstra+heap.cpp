//o((E+V)logV) 
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN 30000
struct edge
{
	int v,w;//终点，两点距离/点，到S的距离 
	edge(int v1,int w1):v(v1),w(w1){}	
	bool operator < (const edge &e) const {return w>e.w; } //小顶堆
};
int us[MAXN+1];//是否已用 
int pre[MAXN+1];//存储路径 
int n,m;//点、边数  
int S,N;//起点,终点 
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
	vector<vector<edge> > lj(n+1);//邻接表
	fill(us,us+n+1,0);
	//输入 
	for(int i=0;i<m;i++)
	{
		int v,e,w;
		scanf("%d%d%d",&v,&e,&w);
		lj[v].push_back(edge(e,w));//有向图 
	}
	//核心 
	priority_queue<edge> q;//优先队列实现堆
	vector<int> a(n+1);//存放各点进入队列时的到S的距离，发现某次进入后比之前记录的距离小，就更新距离和路径 
	fill(a.begin(),a.end(),INF); 
	q.push(edge(S,0));
	edge mini(0,0);
	while(!q.empty())
	{	 
		do
		{
			mini=q.top();
			q.pop();
		}while(us[mini.v]==1&&!q.empty());//找到没用过的到S的距离最短的一个点 
		if(us[mini.v]==0)
		{				
			us[mini.v]=1;
			if(mini.v==N) break; 
			for(int i=0;i<lj[mini.v].size();i++)//更新没用过的点到S的最短距离 
			{
				if(us[lj[mini.v][i].v]==0) 
				{
					int k=mini.w+lj[mini.v][i].w;
					if(a[lj[mini.v][i].v]>k)  
					{
						a[lj[mini.v][i].v]=k;
						q.push(edge(lj[mini.v][i].v,k));//也可以不放到if里，但内存会增大，因为堆会选择加入的相同点中到S的距离最小的，其他的都不会选到,所以即使插入的比之前的大也没关系 
						pre[lj[mini.v][i].v]=mini.v;
					}
				}
			}
		}
	}
	//结果 
	if(us[N]==1) 
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
