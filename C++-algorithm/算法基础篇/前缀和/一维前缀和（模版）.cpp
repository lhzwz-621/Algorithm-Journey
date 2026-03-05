//题目牛客前缀和（模版）
#include <iostream>
using namespace std;
using LL=long long;

const int N=1e5+10;

int n,m;    //n为数量，m为查询次数
int l,r;
LL a[N];
LL f[N];
int main() {
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        //设一个前缀和数组
        f[i]=f[i-1]+a[i];
    }

    for(int i=0;i<m;i++)
    {
        cin>>l>>r;
        cout<<f[r]-f[l-1]<<endl;
    }
    return 0;
}
// 64 位输出请用 printf("%lld")