#include<iostream>
#include<cstring>
using namespace std;
const int maxn=50010;   //字符串长度最大值
int GETNEXT(char *str,int *next)
{
    int i=0,j,po,len=strlen(str);
    next[0]=len;//初始化next[0]
    while(str[i]==str[i+1]&&i+1<len)//计算next[1]
    i++;
    next[1]=i;
    po=1;//初始化po的位置
    for(i=2;i<len;i++)
    {
        if(next[i-po]+i<next[po]+po)//第一种情况，可以直接得到next[i]的值
        next[i]=next[i-po];
        else//第二种情况，要继续匹配才能得到next[i]的值
        {
            j=next[po]+po-i;
            if(j<0)j=0;//如果i>po+next[po],则要从头开始匹配
            while(i+j<len&&str[j]==str[j+i])//计算next[i]
            j++;
            next[i]=j;
            po=i;//更新po的位置
        }
        if(i+next[i]==len) return i;
    }
    return -1;
}
void asd(char *a,int *next,int len) //KMP的失配数组
{
	next[0]=-1;
	int j=-1;
	for(int i=0;i<len;)
	{
		if(j==-1||a[i]==a[j])
		{
			j++;
			i++; 
			if(a[i]==a[j]) next[i] = next[j];  
			else next[i]=j;
		}
		else j=next[j];
	}
}
void asd1(char *a,int *next,int len) //改造后的失配数组 
{
	next[0]=-1;
	int j=-1;
	for(int i=0;i<len;)
	{
		if(j==-1||a[i]==a[j])
		{
			j++;
			i++; 
			if(a[i]==a[j]) next[i] = j; 
			else next[i]=-1;
		}
		else j=next[j];
	}
}
int kmp(int *next,char *T,char *S) 
{
	int i=-1,j=-1;
	while(j<(int)strlen(S)&&i<(int)strlen(T))
	{
		if(-1==j||T[i]==S[j])
		{
			i++;
			j++;
		}
		else
		{
			j=next[j];
		}
	}
	if(j==strlen(S)&&i!=strlen(T)) return 1;//匹配成功且不是后缀 
	else return 0;
}
int main()
{
	char a[50010];
	while(cin>>a)
	{
		int next[maxn];
		int i=GETNEXT(a,next);
		if(i!=-1)
		{
			int next1[maxn];
			asd(a+i,next1,next[i]);
			if(kmp(next1,a+1,a+i))
			{
				cout<<next[i]<<endl;
			}
			int next2[maxn];
			asd1(a+i,next2,next[i]);
			int k=next2[next[i]-1];
			while(k!=-1)
			{
				cout<<k+1<<endl;
				k=next2[k];	
			}
		}
	}
	return 0;
} 
