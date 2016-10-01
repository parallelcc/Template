//o(V*V*V) 
#include<iostream>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN 200
int dis[MAXN+1][MAXN+1];//dp数组 
int path[MAXN+1][MAXN+1];//路径 
int n,m;//点、边数 
int u,v;//起点，终点 
void flo()
{
	scanf("%d%d",&n,&m);
	//初始化 
	for(int i=0;i<=n;i++) 
	{
		//需要记录路径时 
		for(int j=0;j<=n;j++)
		{
			dis[i][j]=INF;
			path[i][j]=j;
		}
		//不需要时
		//fill(dis[i],dis[i]+n,INF);
		dis[i][i]=0;
	}
	//输入 
	for(int i=0;i<m;i++)
	{
		int u1,v1,w;
		scanf("%d%d%d",&u1,&v1,&w);
		if(dis[u1][v1]>w)
		{
			dis[u1][v1]=w;
			dis[v1][u1]=w;	
		}
	}
	//核心 
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(dis[i][k]+dis[k][j]<dis[i][j]) 
				{
					dis[i][j]=dis[i][k]+dis[k][j];	
					path[i][j]=path[i][k];
				}		
			}
		}
	}
} 
//输出路径 
void printpath()
{
	int tmp=u; 
	printf("%d",u);
    while(tmp!=v)
    {
        printf("-->%d",path[tmp][v]);
        tmp=path[tmp][v];
    }
    printf("\n");
}
int main()
{
	flo();		
	while(~scanf("%d%d",&u,&v))
	{	
		printf("%d\n",dis[u][v]==INF?-1:dis[u][v]);
		if(dis[u][v]!=INF) printpath();		
	}
	return 0;
 } 
