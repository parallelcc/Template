#include<iostream>
using namespace std;
#define LL long long 
LL extend_gcd(LL a,LL b,LL &x,LL &y)//求 ax+by=gcd(a,b)的整数解,返回gcd(a,b)
{
	if(a==0&&b==0) return -1;//无最大公约数
	if(b==0){x=1;y=0;return a;}
	LL d=extend_gcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
//*********求逆元*******************
// ax ≡ 1(mod n)
LL mod_reverse(LL a,LL n)
{
	LL x,y;
	LL d=extend_gcd(a,n,x,y);
	if(d==1) return (x%n+n)%n;
	else return -1;
} 
//求 x ≡ ai(mod bi) bi两两互质 
LL a[10005],b[10005],c[10005];
int main()
{
	int n;
	scanf("%d",&n);
	LL sum=1;//bi累乘 
	for(int i=0;i<n;i++) 
	{
		scanf("%I64d",&b[i]);
		scanf("%I64d",&a[i]);
		sum*=b[i];
	}
	for(int i=0;i<n;i++) 
	{
		c[i]=sum/b[i];
	}
	LL x=0;
	for(int i=0;i<n;i++) x=(x+a[i]*mod_reverse(c[i],b[i])*c[i]%sum)%sum;//求出一个解 
	while(x<=0) x+=sum;//最小正整数解 
	printf("%d\n",x);
}
