// Cipolla
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct F{
    ll x,y;
    F(){};
    F(ll _x,ll _y):x(_x),y(_y){};
};

F mul(F a,F b,ll mod,ll w){
    return F((a.x*b.x%mod+a.y*b.y%mod*w%mod)%mod,(a.x*b.y%mod+a.y*b.x%mod)%mod);
}

F quick_mod(F base,ll b,ll mod,ll w){
    F res=F(1,0);
    while(b){
        if(b&1)res=mul(res,base,mod,w);
        base=mul(base,base,mod,w);
        b>>=1;
    }
    return res;
}

ll quick_mod(ll base,ll b,ll mod){
    ll res=1;
    while(b){
        if(b&1)res=res*base%mod;
        base=base*base%mod;
        b>>=1;
    }
    return res;
}

ll legendre(ll a,ll mod){
    return quick_mod(a,(mod-1)/2,mod);
}

ll solve(ll n,ll mod){
    if(mod==2)return n%2==1?1:-1;// 
    if(legendre(n,mod)!=1)return -1;
    if(mod%4==3)return quick_mod(n,(mod+1)/4,mod);
    while(1){
        ll a=rand()%(mod-1)+1;
        ll w=(a*a%mod+mod-n)%mod;
        if(legendre(w,mod)==mod-1)
            return quick_mod(F(a,1),(mod+1)/2,mod,w).x;
    }
}

int main(){
    srand(unsigned(time(NULL)));
    int t;scanf("%d",&t);
    while(t--){
        ll n,mod;scanf("%lld%lld",&n,&mod);
        n%=mod;
        ll ans=solve(n,mod);
        if(ans==-1)printf("No root\n");
        else {
            ll ans1=mod-ans;
            if(ans1==ans)printf("%lld\n",ans);
            else printf("%lld %lld\n",min(ans,ans1),max(ans,ans1));
        }
    }
}