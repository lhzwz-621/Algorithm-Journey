//题目https://www.luogu.com.cn/problem/P2280
#include <iostream>
#include<algorithm>
using namespace std;
const int N=5010;

int n,m;
int a[N][N];
int f[N][N];	//a数组的前缀和数组

int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		int x,y,v;cin>>x>>y>>v;
		x++,y++;	//题目坐标从0开始，而数组从1开始，所以坐标加1
		a[x][y]+=v;
	}

	n=5001;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			f[i][j]=f[i][j-1]+f[i-1][j]-f[i-1][j-1]+a[i][j];
		}
	}

	int res=0;
	for(int x1=m;x1<=n;x1++)
	{
		for(int y1=m;y1<=n;y1++)
		{
			int x2=x1-m+1;int y2=y1-m+1;
			res=max(res,f[x1][y1]-f[x1][y2-1]-f[x2-1][y1]+f[x2-1][y2-1]);
		}
	}
	cout<<res<<endl;
	return 0;
}