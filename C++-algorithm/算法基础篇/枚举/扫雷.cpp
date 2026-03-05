//题目洛谷P2327

#include <iostream>

using namespace std;

const int N=1e5+10;

int n;	//行数
int a[N],b[N];	//a数组存雷，b数组存个数

int check1()
{
	a[1]=1;
	for(int i=2;i<=n+1;i++)
	{
		a[i]=b[i-1]-a[i-1]-a[i-2];
		if(a[i]<0||a[i]>1) return 0;
	}
	//还需判断a[n+1]是否为0
	if(a[n+1]==0) return 1;
	else return 0;
}

int check2()
{
	a[1]=0;
	for(int i=2;i<=n+1;i++)
	{
		a[i]=b[i-1]-a[i-1]-a[i-2];
		if(a[i]<0||a[i]>1) return 0;
	}
	if(a[n+1]==0) return 1;
	else return 0;
}

int main()
{
	cin>>n;

	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
	}

 	int ret=0;

	//分两种情况。
	//第一行有雷，
 	ret+=check1();
 	//第一行没有雷
 	ret+=check2();

 	cout<<ret<<endl;

	return 0;
}