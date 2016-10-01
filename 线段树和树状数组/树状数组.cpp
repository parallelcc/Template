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
#define sc(i) scanf("%d",&i)
#define pr(j) printf("%d\n",j)
#define N 100005 //最大数据数 
int tr[N];//树状数组 
int n;//当前数据数 
int lowbit(int x){return x&(-x);}//获取二进制下x最后一个1以及后面的0组成的数 
void add(int x,int k)//单点增加k 
{
	while(x<=n)
	{
		tr[x]+=k;
		x+=lowbit(x);
	}
}
int query(int x)//查询1到x的区间和 
{
	int ans=0;
	while(x)
	{
		ans+=tr[x];
		x-=lowbit(x);
	}
	return ans;
}
int main()
{
	//初始化 
	sc(n);
	fill(tr,tr+n+1,0);
	for(int i=1;i<=n;i++)
	{
		int x;
		sc(x);
		add(i,x);
	}
	return 0;
}
