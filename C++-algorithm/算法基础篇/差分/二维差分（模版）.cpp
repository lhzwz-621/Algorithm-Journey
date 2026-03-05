#include <iostream>
using namespace std;
using LL=long long;
const int N=1010;

int n,m,q;
LL f[N][N]; //差分矩阵

//由于f[i][j]+=k,会使前缀和时导致从i->n,j->m的前缀矩阵元素都加上k
void insert(int x1,int y1,int x2,int y2,int k)
{
    f[x1][y1]+=k;f[x1][y2+1]-=k;f[x2+1][y1]-=k;f[x2+1][y2+1]+=k;
}


int main() {
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            LL x;cin>>x;
            insert(i,j,i,j,x);    //初始化差分矩阵，用差分性质
        }
    }

    for(int i=0;i<q;i++)
    {
        int x1,y1,x2,y2;LL k;cin>>x1>>y1>>x2>>y2>>k;
        insert(x1,y1,x2,y2,k);
    }

    //用前缀和相加得到最终结果
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1]+f[i][j];
            cout<<f[i][j]<<" ";
        }
        cout<<endl;
    }
}
// 64 位输出请用 printf("%lld")