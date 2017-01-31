#include<iostream>
using namespace std;
int PowMod(int a, int b, int c)
{
	int ans = 1;
	a = a % c;
	while(b>0)
	{
		if(b & 1)
		ans = (ans * a) % c;
		b >>= 1;
		a = (a * a) % c;
	}
	return ans;
} 
int PowSumMod(int a,int n,int p)
{// return (a+ a^2 + ... + a^n) Mod p;
	if( n == 1) return a%p;
	if( n % 2 == 0)return (1+PowMod(a,n/2,p))*PowSumMod(a,n/2,p) % p;
	else return ((1+PowMod(a,(n-1)/2,p)) * PowSumMod(a,(n-1)/2,p)+ PowMod(a,n,p)) % p;
}
int main()
{
	int a,n,p;
	cin>>a>>n>>p;
	cout<<PowSumMod(a,n,p)<<endl;
}
