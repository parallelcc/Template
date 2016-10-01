#include<iostream>
using namespace std;
int *hebin(int *a,int *b,int n)
{
	int *c=new int[n],i=0,j=0,m,k,l=n/2;
	if(n%2) k=n/2+1;
	else k=n/2;
	for(m=0;i!=l&&j!=k;m++)
	{
		if(a[i]>b[j]) 
		{
			c[m]=b[j];
			j++;
		}
		else 
		{
			c[m]=a[i];
			i++;
		}
	}
	while(m!=n)
	{
		if(i==l) 
		{
			c[m]=b[j];
			j++;
		}
		else
		{
			c[m]=a[i];
			i++;
		}
		m++;
	}
	return c;
} 
int *chaifen(int *a,int n)
{
	if(n==1) return a;
	else
	{
		if(n%2) return hebin(chaifen(a,n/2),chaifen(a+n/2,n/2+1),n);
		else return hebin(chaifen(a,n/2),chaifen(a+n/2,n/2),n);
	}
}
int main()
{
	int n;
	cin>>n;
	int *a=new int[n];
	for(int i=0;i<n;i++) cin>>a[i];
	a=chaifen(a,n);
	for(int i=0;i<n;i++) cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}
