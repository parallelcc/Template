//求循环节
//if(len%(len-next[len])==0)  p=len/(len-next[len]);
//else p=1;  
#include <iostream>
#include<string>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void asd(int *next,string &S,int n)
{
	int i=-1,j=0;
	next[0]=-1;
	while(j<n)
	{
		if(-1==i||S[i]==S[j])
		{
			i++;
			j++;
			//优化 
			if(S[i]!=S[j]) next[j]=i; 
			else next[j]=next[i];
			//未优化
			//next[j]=i;
		}
		else
		{
			i=next[i];
		}
	}
}
int kmp(int *next,string &T,string &S)
{
	int i=-1,j=-1;
	while(j<(int)S.length()&&i<(int)T.length())
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
	if(j==(int)T.length()) return (i-S.length()+1);
	else return 0;
}
int main(int argc, char *argv[]) {
	string T,S;
	cin>>T>>S;
	int *next=new int[S.length()];
	asd(next,S,S.length());
	cout<<kmp(next,T,S)<<endl;
	delete[] next;
	return 0;
}
