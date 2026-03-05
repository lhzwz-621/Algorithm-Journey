#include <iostream>
using namespace std;
using LL=long long;
const int N=1010;

int n,m,q;
LL a[N][N];
LL f[N][N]; //对应的前缀和矩阵

int main() {
    cin>>n>>m>>q;
    //构建二维矩阵同时构造该矩阵的二维前缀和
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
            //通过面积法构造矩阵
            f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1]+a[i][j];
        }
    }
    for(int i=0;i<q;i++)
    {
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        cout<<f[x2][y2]-f[x1-1][y2]-f[x2][y1-1]+f[x1-1][y1-1]<<endl;
    }

    return 0;
}
// 64 位输出请用 printf("%lld")