//题目luoguP2010

#include <iostream>

using namespace std;


int x,y;

int day[]={0,31,29,31,30,31,30,31,31,30,31,30,31};

int num=0;

int main()
{
	cin>>x>>y;

	for(int i=1;i<=12;i++)
	{
		for(int j=1;j<=day[i];j++)
		{
			int tmp=j%10*1000+j/10*100+i%10*10+i/10;
			int k=tmp*10000+100*i+j;
			if(k>=x&&k<=y) num++;
		}
	}
	cout<<num<<endl;
	return 0;
}