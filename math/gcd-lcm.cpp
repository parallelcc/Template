int gcd(int a,int b)
{
	if(!b) return a;
	return gcd(b,a%b);
}
最小公倍数：lcm(a,b) = a*b/gcd(a,b)

