#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char a[1005],b[1005],c[1005];
int al,bl,dp[1005][1005];
int main()
{
	int i,j;
	scanf("%s%s",a+1,b+1);
	for(i=1;a[i];i++)
	{
		for(j=1;b[j];j++)
		{
			if(a[i]==b[j]) dp[i][j]=dp[i-1][j-1]+1;
			else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
		}
	}
	printf("%d\n",dp[--i][--j]);
	//输出一个子序列
	c[dp[i][j]]='\0';
	while(dp[i][j])
	{
		if(a[i]==b[j]) c[dp[--i][--j]]=a[i+1];
		else
		{
			if(dp[i][j]==dp[i-1][j]) i--;
			else if(dp[i][j]==dp[i][j-1]) j--;
		}
	}
	printf("%s\n",c);
	return 0;
} 
