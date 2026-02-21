//题目洛谷P1098

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int p1,p2,p3;
string s;
string ret;

//判断是否是数字
bool isdigit(char c)
{
	return c>='0'&&c<='9';
}

//判断是否是小写字母
bool islet(char c)
{
	return c>='a'&&c<='z';
}


void add(char left,char right)
{
	string tmp;
	for(char c=left+1;c<right;c++)
	{
		char ch=c;	//不能直接用c，因为后面要修改ch的值

		if(p1==2&&islet(ch))	//如果是小写字母，转换成大写字母
		{
			ch-=32;
		}
		if(p1==3)
		{
			ch='*';
		}
		//重复次数
		for(int i=0;i<p2;i++)
		{
			tmp+=ch;
		}
	}

	if(p3==2)
	{
		reverse(tmp.begin(),tmp.end());
	}

	ret+=tmp;
}

int main()
{
	cin>>p1>>p2>>p3;

	cin>>s;

	int len=s.size();
	for(int i=0;i<len;i++)
	{
		if(s[i]!='-'||i==0||i==len-1)
		{
			ret+=s[i];
		}
		else
		{
			//判断是否展开
			char left=s[i-1];
			char right=s[i+1];
			if(isdigit(left)&&isdigit(right)&&left<right ||
				islet(left)&&islet(right)&&left<right)
			{
				//展开
				add(left,right);
			}
			else
			{
				ret+=s[i];
			}
		}
	}
	cout<<ret<<endl;
	return 0;
}