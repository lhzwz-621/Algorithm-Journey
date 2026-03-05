#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
const int N=20;

int n;
int a[N];
int tmp[N];

int cal(int x,int y)	//x->y有多少步
{
	//0->1，不合法，return -1
	//1->0，合法，++i
	int num=0;
	for(int i=0;i<n;i++)
	{
		if(((x>>i)&1)==0&&((y>>i)&1)==1)
		{
			num++;
		}
		if(((x>>i)&1)==1&&((y>>i)&1)==0)
		{
			return -1;
		}
	}
	return num;

}

int main()
{
	int T;cin>>T;
	for(int k=1;k<=T;k++)
	{
		cin>>n;	//输入有多少个例子
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++)	//从1开始，因为change需要知道前两层情况，直接默认第一层为0
		{
			for(int j=0;j<n;j++)
			{
				int c;cin>>c;
				if(c) a[i]|=(1<<j);
			}
		}

		int ans=0x3f3f3f;
		//暴力枚举第一行所有情况
		for(int i=0;i<(1<<n);i++)
		{
			memcpy(tmp,a,sizeof(a));
			int ret=0;
			int flag=1;	//标记该步骤变化是否合法
			int change=i;
			for(int j=1;j<=n;j++)
			{
				int res=cal(tmp[j],change);
				if(res==-1)
				{
					flag=0;
					break;
				}
				ret+=res;
				tmp[j]=change;	//前两行直接确定该行状态
				change=tmp[j-1]^(change<<1)^(change>>1);	//根据上一行的状态和按下的开关状态(当前行)计算下一行的状态
				change&=(1<<n)-1;	//保证tmp数组中的值只保留n位有效位
			}
			if(flag) ans=min(ans,ret);	//如果该步骤合法，更新答案
		}
		if(ans==0x3f3f3f) printf("Case %d: %d\n",k,-1);
		else printf("Case %d: %d\n",k,ans);
	}

	return 0;
}