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
struct node
{
    int l;
    int r;
    int sum;
    int ad;
};
const int N=100001;//Çø¼ä´óÐ¡ 
int a[N];//Êý×é 
node xds[4*N];//Ïß¶ÎÊ÷ 
int x,y;//ÐÞ¸Ä»ò²éÑ¯µÄÇø¼ä
int q;//ÐÞ¸ÄµÄÖµ 
void creat(int l,int r,int jd)
{
    xds[jd].l=l;
    xds[jd].r=r;
    if(l!=r)
    {
        creat(l,(l+r)/2,2*jd);
        creat((l+r)/2+1,r,2*jd+1);
        xds[jd].sum=xds[2*jd].sum+xds[2*jd+1].sum;
    }
    else 
    {
        xds[jd].sum=a[l-1];
    }
    xds[jd].ad=0;
}
int query(int k)
{
    if(xds[k].r<x||xds[k].l>y) return 0; 
    else if(xds[k].l>=x&&xds[k].r<=y) return xds[k].sum+xds[k].ad*(xds[k].r-xds[k].l+1);
    else 
    {
        xds[k].sum+=(xds[k].r-xds[k].l+1)*xds[k].ad;
        xds[2*k].ad+=xds[k].ad;
        xds[2*k+1].ad+=xds[k].ad;
        xds[k].ad=0;
        return query(2*k)+query(2*k+1);
    }
}
void add(int k)
{
    if(xds[k].r<x||xds[k].l>y) return; 
    else if(xds[k].l>=x&&xds[k].r<=y) 
    {
        xds[k].ad+=q;
    }
    else
    {
        xds[k].sum+=q*((y>xds[k].r?xds[k].r:y)-(x<xds[k].l?xds[k].l:x)+1);
        add(2*k);
        add(2*k+1);
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++) scanf("%d",&a[i]);
        creat(1,n,1); 
        for(int i=0;i<m;i++)
        {
            int k;
            scanf("%d",&k);
            if(k==1)
            {
                scanf("%d%d%d",&x,&y,&q);
                add(1);
            }
            if(k==2)
            {
                scanf("%d%d",&x,&y);
                printf("%d\n",query(1));
            }
        }
    }
    return 0;
}

