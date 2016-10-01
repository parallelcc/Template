#include <iostream> 
#include <algorithm> 
#include <cmath> 
using namespace std;
int prime[100010];
int pd[100010];
int h=0;
void db()
{
    for(int i=2;i<100000;i++)
    {
        if(pd[i]==0)
        {
            prime[h++]=i;
        }
        for(int j=0;j<h&&i*prime[j]<100000;j++)
        {
            pd[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}
int main() 
{ 
    db();
    return 0;
} 
