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
#include<stack>
#include<algorithm>
using namespace std;
#define sc(i) scanf("%d",&i)
#define pr(j) printf("%d\n",j)
#define LL long long int
#define INF 0x3f3f3f3f
struct node
{
	int sum;
	node *l,*r;
	node(int sum1=0,node *l1=NULL,node* r1=NULL):sum(sum1),l(l1),r(r1){
	}
};
node *root=new node;
void add(int d)
{
	node *n=root;
	for(int i=30;i>=0;i--)
	{
		int a=((d>>i)&1);
		if(a==0) 
		{
			if(n->l==NULL) 
			{
				n->l=new node;	
			}
			n=n->l;
			n->sum++;
		}
		else 
		{
			if(n->r==NULL) 
			{
				n->r=new node;	
			}
			n=n->r;
			n->sum++;
		}
	}
}
void sub(int d)
{
	node *n=root;
	for(int i=30;i>=0;i--)
	{
		int a=((d>>i)&1);
		if(a==0) 
		{
			n=n->l;	
			n->sum--;
		}
		else 
		{
			n=n->r;
			n->sum--;
		}
	}
}
int xz(int d)
{
	node *n=root;
	for(int i=30;i>=0;i--)
	{
		int a=((d>>i)&1);
		if(a==0)
		{
			if(n->r&&n->r->sum) 
			{
				n=n->r;	
				d=(d|(1<<i));
			}
			else n=n->l;
		}
		else 
		{			
			if(n->l&&n->l->sum) 
			{
				n=n->l;	
				d=d-(1<<i);
			}
			else n=n->r;
		}
	}
	return d;
}
int main()
{
	int t;
	cin>>t;
	add(0);
	while(t--)
	{
		char c;
		int d;
		cin>>c>>d;
		if(c=='+')
		{
			add(d);
		}
		if(c=='-')
		{
			if(d) sub(d);
		}
		if(c=='?')
		{
			pr(xz(d)^d);
		}
	}
	return 0;
}
