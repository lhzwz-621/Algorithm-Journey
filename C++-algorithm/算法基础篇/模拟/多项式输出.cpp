//题目luoguP1067

#include <iostream>
#include<cmath>
using namespace std;

int main() {
    int n;    //传入该多项式是n次项
    cin>>n;

    for(int i=n;i>=0;i--)
    {
        int a;    //该项的系数
        cin>>a;

        if(a==0) continue;

        //打印符号
        if(a<0)
        {
            cout<<"-";
        }
        else
        {
            if(i!=n) cout<<"+";
        }

        //处理系数
        int abs_a=abs(a);
        if(abs_a!=1||i==0)
        {
            cout<<abs_a;
        }

        //处理指数
        if(i==0) continue;//常数项
        
        if(i>1)
        {
            cout<<"x^"<<i;
        }
        else
        {
            cout<<"x";
        }
    }
    return 0;
}
