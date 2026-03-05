//题目luoguP1003

#include<iostream>

using namespace std;

const int N=1e5+10;

int n;	//有多少地毯
int a[N],b[N],g[N],k[N];	//a,b记录地毯左下角的坐标，g,k记录地毯长，宽

int x,y;	//目标坐标

int find()
{
	for(int i=n;i>=1;i--)
	{
		//逆序查找，便于找到最上层的地毯
		if(x>=a[i]&&x<=a[i]+g[i]&&y>=b[i]&&y<b[i]+k[i])
		{
			return i;
		}
	}
	return -1;
}

int main()
{
	cin>>n;

	for(int i=1;i<=n;i++)	//从一开始，便于找到时第几个地毯覆盖
	{
		cin>>a[i]>>b[i]>>g[i]>>k[i];
	}

	cin>>x>>y;


	cout<<find()<<endl;
	return 0;
}