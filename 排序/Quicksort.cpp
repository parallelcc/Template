#include<iostream>
#include<algorithm>
using namespace std;
void Quicksort(int *a,int n)
{
    if(n==0) return;
    else
    {
        int b=*a,i=0,j=n-1;
        while(i!=j)
        {
            while(a[j]>=b&&i!=j)j--;
            swap(a[j],a[i]);
            while(a[i]<=b&&i!=j)i++;
            swap(a[j],a[i]);
        }
        Quicksort(a,i);
        Quicksort(a+i+1,n-i-1);
    }
} 
int main()
{
    int n;
    cin>>n;
    int *a=new int[n];
    for(int i=0;i<n;i++) cin>>a[i];
    Quicksort(a,n);
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
    cout<<endl;
    delete[] a;
    return 0; 
}
