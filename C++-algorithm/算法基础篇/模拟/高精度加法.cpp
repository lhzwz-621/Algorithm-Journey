//题目luoguP1601

#include<iostream>
#include<string>

using namespace std;

const int N=1e6+10;

//设三个数组存输入的数以及相加结果
int a[N],b[N],c[N];
//记录长度
int la,lb,lc;

void add(int a[],int b[],int c[],int& len)	//需要修改加法结果的长度
{
	for(int i=0;i<lc;i++)
	{
		c[i]+=a[i]+b[i];	//重点：一定要加上原来的c[i]因为已经存了上一位进位的数
		c[i+1]=c[i]/10;//处理进位
		c[i]=c[i]%10;//处理余数
	}
	if(c[lc]) lc++;
}


int main()
{
	string s1,s2;
	cin>>s1>>s2;
	la=s1.size();lb=s2.size();lc=max(la,lb);
	//逆序存储
	for(int i=la-1;i>=0;i--)
	{
		a[i]=s1[la-1-i]-'0';
	}
	for(int i=lb-1;i>=0;i--)
	{
		b[i]=s2[lb-1-i]-'0';
	}

	//加法
	add(a,b,c,lc);

	for(int i=lc-1;i>=0;i--) cout<<c[i];


	return 0;
}