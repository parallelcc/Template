//o(ElogV) 稀疏图 
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
#define MAXN 30000
#define INF 0x3f3f3f3f       
struct edge
{
    int v,w;//终点，两点距离/点，到树的距离 
    edge(int v1,int w1):v(v1),w(w1){}
    bool operator < (const edge &a) const{return w>a.w;} //小顶堆 
};
int us[MAXN+1];//是否已用 
int n,m;//点、边数  
int Prim()
{		
  	if(~scanf("%d%d",&n,&m)==0) return 0;
  	//初始化 
	vector<vector<edge> > lj(n+1);//邻接表
	int qz=0,us_num=0;//权值和，用过的点数 
	fill(us,us+n+1,0);
	//输入 
	for(int i=0;i<m;i++)
	{
		int v,e,w;
		scanf("%d%d%d",&v,&e,&w);
		lj[v].push_back(edge(e,w));
		lj[e].push_back(edge(v,w));
	}//无向图 
	//核心 
	priority_queue<edge> q;//优先队列实现堆
	vector<int> a(n+1);//存放各点进入队列时的到树的距离，发现某次进入后比之前记录的距离小，就更新距离和路径 
	fill(a.begin(),a.end(),INF);
	q.push(edge(1,0));//标号从1开始 
	edge mini(0,0);
	while(!q.empty())
	{	 
		do
		{
			mini=q.top();
			q.pop();
		}while(us[mini.v]==1&&!q.empty());//找到没用过的到树的距离最短的一个点 
		if(us[mini.v]==0)
		{			
			qz+=mini.w;
			us[mini.v]=1;
			us_num++; 
			if(us_num==n) break; 
			for(int i=0;i<lj[mini.v].size();i++)//更新没用过的点到树的最短距离 
			{
				if(us[lj[mini.v][i].v]==0) 
				{
					int k=lj[mini.v][i].w;
					if(a[lj[mini.v][i].v]>k)
					{
						a[lj[mini.v][i].v]=k;
						q.push(edge(lj[mini.v][i].v,k));//也可以不放到if里，但内存会增大，因为堆会选择加入的相同点中到树的距离最小的，其他的都不会选到,所以即使插入的比之前的大也没关系 
					}
				} 
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
