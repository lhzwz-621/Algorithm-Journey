//题目luoguP5731

#include<iostream>
using namespace std;

const int N=9;
int a[N][N];

//设置方向向量
//注意：在二维数组中，行数对应x坐标，列数对应y坐标
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};

int main()
{
	int n;    
	cin>>n;    //输入该蛇形方阵的阶数

	int num=1;    //要填入方阵的数字
	int x=1,y=1;	//当前要填入数字的位置
	int pos=0;	//当前的方向

	while(num<=n*n)
	{
		a[x][y]=num;
		num++;
		int tmpX=x+dx[pos];
		int tmpY=y+dy[pos];
		if(tmpX<1||tmpX>n||tmpY<1||tmpY>n||a[tmpX][tmpY]!=0)//如果越界
		{
			pos=(pos+1)%4;	//改变方向
			tmpX=x+dx[pos];
			tmpY=y+dy[pos];
		}

		x=tmpX;
		y=tmpY;
	}

	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%3d",a[i][j]);
		cout<<endl;
	}
	return 0;
}