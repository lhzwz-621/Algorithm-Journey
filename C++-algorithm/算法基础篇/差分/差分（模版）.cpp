#include <iostream>
using namespace std;
using LL=long long;
const int N=1e5+10;

int n,m;
LL f[N];
int main() {
    ios::sync_with_stdio(false);
    cin>>n>>m;
    //用差分性质写
    for(int i=1;i<=n;i++)
    {
        LL c;
        cin>>c;
        f[i]+=c;
        f[i+1]-=c;
    }
    while(m--)
    {
        LL l,r,k;cin>>l>>r>>k;
        f[l]+=k;
        f[r+1]-=k;
    }

    for(int i=1;i<=n;i++)
    {
        cout<<f[i]<<" ";
        f[i+1]+=f[i];
    }
    cout<<endl;
}
// 64 位输出请用 printf("%lld")