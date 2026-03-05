//题目luoguP1115
#include<iostream>
#include<algorithm>
using namespace std;

using LL=long long;
const int N=2e5+10;

int n;
LL a[N],f[N];




int main()
{
	cin>>n;

	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		f[i]=f[i-1]+a[i];	//求出该数组的前缀和数组
	}

	LL res=-1e18;
	LL prev=0;

	for(int i=1;i<=n;i++)
	{		
		res=max(res,f[i]-prev);	//判断当前前缀和与之前的最小前缀和的差值是否为最大值
		prev=min(prev,f[i]);	//更新之前的最小前缀和
	}
	cout<<res<<endl;
	return 0;
}