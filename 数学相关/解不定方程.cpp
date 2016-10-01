#include<iostream>
using namespace std;
long long extend_gcd(long long a,long long b,long long &x,long long &y)//求 ax+by=gcd(a,b)的整数解,返回gcd(a,b)
{
	if(a==0&&b==0) return -1;//无最大公约数
	if(b==0){x=1;y=0;return a;}
	long long d=extend_gcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
int bdfc(long long a,long long b,long long c,long long &x,long long &y)//解ax+by=c的x的最小正整数解 (ax≡c(mod b)的最小正整数解) 
{
	long long d=extend_gcd(a,b,x,y);
	if(d==-1||c%d) return -1;
	x*=c/d;
	y*=c/d;//特解
	b/=d;
	a/=d;
	/*所有解
	x=x+b*t;
	y=y-a*t;
	模b不同的解共有 d 个，为：t=0,1,..d-1
	*/ 
	long long tx=x;
	x=(x%b+b)%b;//x的最小正整数解 
	y+=(tx-x)/b*a;//对应y的解 
	return 0;
} 
