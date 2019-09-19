// 效率O(n)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=9999991;
const int N=1010;
ll a[N+10];
ll fac[N+10],pre[N+10],back[N+10];
// fac[i]=i!,pre[i]=(k-i)连乘对[1,i],back[i]=(k-i)连乘对[i,n]

ll quickmod(ll base,ll b){
    ll ans=1;
    while(b){
        if(b&1)ans=ans*base%mod;
        base=base*base%mod;
        b>>=1;
    }
    return ans;
}

ll cal(ll a[],ll n,ll k){
    if(k<=n)return a[k];
    back[n+1]=1,pre[0]=k;
    for(int i=1;i<=n;i++)pre[i]=pre[i-1]*(k-i)%mod;
    for(int i=n;i>=0;i--)back[i]=back[i+1]*(k-i)%mod;

    ll ans=a[0]*back[1]%mod*fac[n]%mod;
    if(n&1)ans=-ans;
    for(int i=1;i<=n;i++)
        if((n-i)&1)
            ans=(ans-a[i]*pre[i-1]%mod*back[i+1]%mod*fac[i]%mod*fac[n-i]%mod+mod)%mod;
        else 
            ans=(ans+a[i]*pre[i-1]%mod*back[i+1]%mod*fac[i]%mod*fac[n-i]%mod)%mod;
    return ans;
}
int main(){
    fac[0]=1;
    for(int i=1;i<=N;i++)fac[i]=fac[i-1]*i%mod;
    for(int i=1;i<=N;i++)fac[i]=quickmod(fac[i],mod-2);

    int t;scanf("%d",&t);
    while(t--){
        int n,m;scanf("%d%d",&n,&m);
        for(int i=0;i<=n;i++)scanf("%lld",&a[i]);
        a[n+1]=cal(a,n,n+1);
        for(int i=1;i<=n+1;i++)a[i]=(a[i]+a[i-1]+mod)%mod;

        while(m--){
            int l,r;scanf("%d%d",&l,&r);
            printf("%lld\n",(cal(a,n+1,r)-cal(a,n+1,l-1)+mod)%mod);
        }
    }
}
