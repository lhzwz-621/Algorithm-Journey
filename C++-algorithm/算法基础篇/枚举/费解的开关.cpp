//题目luoguP10449

#include <iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=10;
int n=5;


int a[N];

int cal(int nums)
{
	int res=0;
	while(nums)
	{
		nums&=(nums-1);	//每次消除最低位的1，直到nums变为0
		res++;
	}
	return res;
}

int main()
{
	int num;cin>>num;
	while(num--)
	{
		memset(a,0,sizeof(a));	//每次测试用例都要重置a数组

		for(int i=0;i<n;i++)
		{
			for(int j=0;j<5;j++)
			{
				char c;cin>>c;
				if(c=='0') a[i] |=(1<<j);	//反向存储，0表示开关打开，1表示开关关闭
			}
		}

		int ans=0x3f3f3f3f;	//初始化为一个很大的数

		//开始枚举第一行所有的开灯状态
		for(int i=0;i<(1<<n);i++)
		{
			//每次枚举都要重置tmp数组,防止上一次枚举的结果对下一次枚举造成干扰
			int tmp[N];
			memcpy(tmp,a,sizeof(a));	
			int ret=0;	//计算当前枚举的开灯状态需要按下多少次开关
			int push=i;
			//遍历行数
			for(int j=0;j<5;j++)
			{
				ret+=cal(push);
				tmp[j]=tmp[j]^push^(push<<1)^(push>>1);	//根据当前行的状态和按下的开关状态计算下一行的状态
				tmp[j]&=(1<<n)-1;	//保证tmp数组中的值只保留5位有效位
				tmp[j+1]^=push;
				push=tmp[j];
			}
			if(tmp[n-1]==0) ans=min(ret,ans);
		}
		if(ans>6) cout<<-1<<endl;
		else cout<<ans<<endl;
	}
	return 0;
}
