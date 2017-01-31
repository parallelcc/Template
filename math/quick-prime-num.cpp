//1e11 1500ms 6000k O(n^(3/4))
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
ll f[340000],g[340000];
void init(ll k){
    ll i,j,m;
    for(m=1;m*m<=k;++m)f[m]=k/m-1;//1-sqrt(k)的倍数的数的数量 
    for(i=1;i<=m;++i)g[i]=i-1;
    for(i=2;i<=m;++i){
    	for(int s=1;s<=m;s++) std::cout<<g[s]<<" ";
        std::cout<<endl;
        if(g[i]==g[i-1])continue;
        for(j=1;j<=min(m-1,k/i/i);++j){
            if(i*j<m)f[j]-=f[i*j]-g[i-1];
            else f[j]-=g[k/i/j]-g[i-1];
        }
        for(j=m;j>=i*i;--j)g[j]-=g[j/i]-g[i-1];
    }
}
int main(){
	ll n;
    while(scanf("%I64d",&n)!=EOF){
        init(n);
        for(int i=1;i<sqrt(n)+1;i++) std::cout<<f[i]<<" ";
        std::cout<<endl;
        for(int i=1;i<=sqrt(n)+1;i++) std::cout<<g[i]<<" ";
        std::cout<<endl;
        printf("%I64d\n",f[1]);
    }
    return 0;
}
