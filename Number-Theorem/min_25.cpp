#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+100;
const ll mod=1e9+7;
const ll inv6=(mod+1)/6;
const ll inv2=(mod+1)/2;
const ll inv3=(mod+1)/3;
ll prime[N+10],id1[N+10],id2[N+10],w[N+10];
ll sp[N+10],g1[N+10],g2[N+10],sqr,n;
ll cnt=0;
// 求f(p^c)=p^c,f(ab)=f(a)f(b),f(1)=1;
void sieve(){
	prime[0]=0;
	for(ll i=2;i<=N;i++){
		if(!prime[i]){
			prime[++prime[0]]=i;
			sp[prime[0]]=(sp[prime[0]-1]+i)%mod;
			// sp里维护 sp[i]=sigma(prime[i])
		}
		for(int o=1;o<=prime[0]&&i*prime[o]<=N;o++){
			prime[i*prime[o]]++;
			if(i%prime[o]==0)break;
		}
	}
}
ll S(ll x,int y){
	if(prime[y]>=x&&y)return 0;
	ll k;
	if(x<=sqr)k=id1[x];
	else k=id2[n/x];
	ll ans=(g2[k]-g1[k]+mod-(sp[y]-y)+mod)%mod;
	if(y==0)ans+=2;
	for(int i=y+1;i<=prime[0]&&prime[i]*prime[i]<=x;i++){
		ll tmp=prime[i];
		for(int o=1;tmp*prime[i]<=x;o++,tmp*=prime[i]){
			ans=(ans+(prime[i]^o)%mod*S(x/tmp,i)%mod+(prime[i]^(o+1)))%mod;
		}
	}
	return ans%mod;
}
int main(){
	scanf("%lld",&n);
	if(n==1){printf("1");return 0;}
	sqr=sqrt(n);
	sieve();
	for(ll l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		w[++cnt]=n/l;
		ll k=w[cnt]%mod;
		// g1维护sigma([i is prime] 1) 这里先维护sigma(i)=k 从2开始，所以减掉1
		g1[cnt]=(k+mod-1)%mod;
		// g2维护sigma([i is prime] i) 这里先维护sigma(i)=k*(k+1)/2 从2开始，所以减掉1
		g2[cnt]=(k*(k+1)%mod*inv2%mod+mod-1)%mod;
		if(w[cnt]<=sqr)id1[w[cnt]]=cnt;
		else id2[r]=cnt;
	}
	for(int i=1;i<=prime[0];i++)
		for(int o=1;o<=cnt&&prime[i]*prime[i]<=w[o];o++){
			ll k;
			if(w[o]/prime[i]<=sqr)k=id1[w[o]/prime[i]];
			else k=id2[n/(w[o]/prime[i])];
			// g1维护sigma([i is prime] 1)
			g1[o]=(g1[o]-(g1[k]-(i-1))+mod)%mod;
			// g2维护sigma([i is prime] i)
			g2[o]=(g2[o]-prime[i]*(g2[k]-sp[i-1])%mod+mod)%mod;
		}
	printf("%lld\n",(S(n,0)+1)%mod);
}