//题目luoguP1303

#include <iostream>
#include<string>
using namespace std;

const int N=1e6+10;

int a[N],b[N],c[N];
int la,lb,lc;

void multi(int a[],int b[],int c[],int& len)
{
	//把每位数的结果相加但不进位
	for(int i=0;i<la;i++)
	{
		for(int j=0;j<lb;j++)
		{
			c[i+j]+=a[i]*b[j];
		}
	}

	//开始进位化结果
	for(int i=0;i<lc;i++)
	{
		c[i+1]+=c[i]/10;
		c[i]=c[i]%10;
	}
	//去除前导零
	while(lc>1&&c[lc-1]==0)
	{
		lc--;
	}
}

int main()
{
	string s1,s2;
	cin>>s1>>s2;
	la=s1.size();lb=s2.size();lc=la+lb;
	//逆序存储
	for(int i=la-1;i>=0;i--)
	{
		a[i]=s1[la-1-i]-'0';
	}
	for(int i=lb-1;i>=0;i--)
	{
		b[i]=s2[lb-1-i]-'0';
	}

	//乘法
	multi(a,b,c,lc);

	for(int i=lc-1;i>=0;i--)
	{
		cout<<c[i];
	}
	return 0;
}