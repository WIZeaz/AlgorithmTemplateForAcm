//codeforces-906D
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll MOD(ll x,ll m){return x>=m?x%m+m:x;}
ll quickmod(ll base,ll b,ll mod){
    ll ans=1;
    while(b){
        if(b&1)ans=MOD(ans*base,mod);
        base=MOD(base*base,mod);
        b>>=1;
    }
    return ans;
}

ll a[100010];
map<ll,ll>mapp;
ll phi(ll x){
    if(mapp[x])return mapp[x];
    ll ans=x,prex=x;
    for(ll i=2;i*i<=x;i++)
        if(x%i==0){
            ans=ans/i*(i-1);
            while(x%i==0)x/=i;
        }
    if(x>1)ans=ans/x*(x-1);
    return mapp[prex]=ans;
}

ll solve(int l,int r,ll mod){
    if(l==r||mod==1)return MOD(a[l],mod);

    return quickmod(a[l],solve(l+1,r,phi(mod)),mod);
}

int main(){
    ll n,mod;scanf("%lld%lld",&n,&mod);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    int q;scanf("%d",&q);
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        printf("%lld\n",solve(l,r,mod)%mod);
    }
}
