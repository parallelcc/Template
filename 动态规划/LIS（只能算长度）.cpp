//o(nlogn) 
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N= 50000+5;
int lis[N];
int main()
{
	int n;
	scanf("%d",&n);
	int h=0,k;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&k);
		if(!h||lis[h-1]<k) lis[h++]=k;
		else lis[lower_bound(lis,lis+h,k)-lis]=k;//upper_bound为非降子序列 
	}
	printf("%d\n",h);
	return 0;	
} 
