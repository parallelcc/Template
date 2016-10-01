#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
struct node
{
	char data;
	int weight; 
    int parent;  
	int rchild,lchild;
	node(int b=-1):weight(b),parent(b),rchild(b),lchild(b){} 
};
void select(node *tree,int i,int &s1,int &s2)
{
	int min=1000;
	for(int j=0;j<i;j++)
	{
		if(tree[j].weight<min&&tree[j].parent==-1) 
		{
			s1=j;
			min=tree[j].weight;
		}
	}
	min=1000;
	for(int j=0;j<s1;j++)
	{
		if(tree[j].weight<min&&tree[j].parent==-1) 
		{
			s2=j;
			min=tree[j].weight;
		}
	}
	for(int j=s1+1;j<i;j++)
	{
		if(tree[j].weight<min&&tree[j].parent==-1)
		{
			s2=j;
			min=tree[j].weight;
		}
	}
}
void creat(node *tree,char *a,int *b,int n)
{
	for(int i=0;i<n;i++)
	{
		tree[i].weight=b[i];
		tree[i].data=a[i];
	}
	for(int i=n;i<2*n-1;i++)
	{
		int s1,s2;
		select(tree,i,s1,s2);
		tree[i].lchild=s1;
		tree[i].rchild=s2;
		tree[i].weight=tree[s1].weight+tree[s2].weight;
		tree[s1].parent=i;
		tree[s2].parent=i;
	}
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int m;
		char c[1000];
		cin>>m>>c;
		char a[1000];
		int b[1000];
		int h=0;
		for(int i=0;i<strlen(c);i++)
		{
			int j;
			for(j=0;j<h&&c[i]!=a[j];j++)
			{
			};
			if(h==j)
			{
				a[h]=c[i];
				b[h]=1;
				h++; 
			} 
			else
			{
				b[j]++;
			}
		}
		node *tree=new node[2*h-1];
		creat(tree,a,b,h);
		int sum=0;
		for(int i=h;i<2*h-1;i++)
		{
			sum+=tree[i].weight;
		}
		if(sum==0) sum=b[0];
		if(sum<=m) cout<<"yes"<<endl;
		else cout<<"no"<<endl;
	}
}
