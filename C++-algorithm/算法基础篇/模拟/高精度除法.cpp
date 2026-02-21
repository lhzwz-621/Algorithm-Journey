//题目luoguP1480

//注：高精度除以低精度
#include <iostream>
#include<string>

using namespace std;
typedef long long ll;
const int N=1e6+10;

int a[N],b,c[N];

int la,lc;

void div(int a[],int b,int c[],int& lc)
{
	ll t=0;	//记录每次除完的余数

	//从最高位开始向下除
	for(int i=la-1;i>=0;i--)
	{
		t=t*10+a[i];
		c[i]=t/b;
		t=t%b;
	}

	while(lc>1&&c[lc-1]==0)
	{
		lc--;
	}
}


int main()
{
	string s1;
	cin>>s1>>b;

	la=s1.size();lc=la;
	for(int i=la-1;i>=0;i--)
	{
		a[i]=s1[la-1-i]-'0';
	}

	div(a,b,c,lc);

	for(int i=lc-1;i>=0;i--)
	{
		cout<<c[i];
	}
	return 0;
}