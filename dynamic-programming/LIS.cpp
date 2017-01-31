//o(n*n) 
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f 
const int N=10010;
int a[N],dp[N];
int path[N];
int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		for(int i=0;i<n;i++) scanf("%d",&a[i]);
		dp[0]=1;
		for(int i=1;i<n;i++)
		{
			int m=1;
			for(int j=0;j<i;j++) 
			{
				if(a[j]<a[i]) m=max(m,dp[j]+1);
			}
			dp[i]=m;
		}
		int m=1,mi=0;
		for(int i=0;i<n;i++) 
		{
			m=max(m,dp[i]);
			mi=i;
		}
		printf("%d\n",m);
		// 输出一个子序列 
		path[m-1]=a[mi];
		m--;
		for(int i=mi-1;i>=0&&m>0;i--)
		{
			if(dp[i]==m&&a[i]<path[m]) 
			{
				path[m-1]=a[i];
				m--;
			}
		}
		for(int i=0;i<mi;i++) 
		{
			if(i!=mi-1) printf("%d ",path[i]);
			else printf("%d\n",path[i]);
		}
	}
}
