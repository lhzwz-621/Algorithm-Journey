//题目luoguP2142

#include <iostream>
#include<string>
using namespace std;

const int N=1e6+10;

int a[N],b[N],c[N];

int la,lb,lc;

bool cmp(const string& x,const string& y)
{
	//先比较长度
	if(x.size()!=y.size()) return x.size()<y.size();

	//如果相同，按照字典序方式比较
	return x<y;
}

void sub(int a[],int b[],int c[])
{
	for(int i=0;i<lc;i++)
	{
		c[i]+=a[i]-b[i];
		if(c[i]<0)
		{
			c[i]+=10;
			c[i+1]--;
		}
	}

	//处理前导零
	while(lc>1&&c[lc-1]==0)
	{
		lc--;
	}
}

int main()
{
	string s1,s2;
	cin>>s1>>s2;

	if(cmp(s1,s2))	//如果s1<s2
	{
		cout<<"-";
		swap(s1,s2);
	}

	la=s1.size();lb=s2.size();lc=max(la,lb);

	for(int i=la-1;i>=0;i--)
	{
		a[i]=s1[la-1-i]-'0';
	}
	for(int i=lb-1;i>=0;i--)
	{
		b[i]=s2[lb-1-i]-'0';
	}

	//减法
	sub(a,b,c);


	for(int i=lc-1;i>=0;i--)
	{
		cout<<c[i];
	}

	return 0;
}