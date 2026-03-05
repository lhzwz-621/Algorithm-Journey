#include<iostream>
using namespace std;
using LL=long long;
const int N=1e5+10;

int n,m;
LL f[N];	//差分数组存储两城市间经过次数

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	//计算每两个相邻城市间经过的次数
	int x,y;
	cin>>x;
	for(int i=2;i<=m;i++)	//从第二个城市开始算，所以等于2
	{
		cin>>y;
		//有n个城市，就有n-1条铁路，第i个城市到第i+1个城市铁路就相当于f[i]
		//原本应该是diff[x]++,diff[y+1]--,但从城市l到城市r，相当于铁路区间[l,r-1]都加1
		//所以是f[x]++,f[y]--;
		if(x>y)
		{
			f[x]--;	
			f[y]++;
		}
		if(x<y)
		{
			f[x]++;
			f[y]--;
		}
		x=y;
	}
	LL ret=0;
	//前缀和得到原数组
	for(int i=1;i<=n;i++)
	{
		f[i]+=f[i-1];
	}
	for(int i=1;i<n;i++)
	{
		LL a,b,c;cin>>a>>b>>c;
		ret+=min(a*f[i],c+b*f[i]);
	}
	cout<<ret<<endl;
	return 0;
}