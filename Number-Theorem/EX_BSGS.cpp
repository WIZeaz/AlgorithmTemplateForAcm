#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll quickmod(ll base,ll b,ll mod){
	ll res=1;
	while(b){
		if(b&1)res=res*base%mod;
		base=base*base%mod;
		b>>=1;
	}
	return res;
}
ll pre_inf,bsgs_inf;
struct Hash {
	static const int MOD=1999997;
	static const int N=1e6;
	int head[MOD+10],nextt[N+10],cnt,id[N+100];
	int pre[N+100];
	void init(){
		memset(head,-1,sizeof head);
		cnt=0;
	}
	void insert(int x, int y){
		int k=x%MOD;
		pre[++cnt]=x,id[cnt]=y,nextt[cnt]=head[k],head[k]=cnt;
	}
	int find(int x){
		int k=x%MOD;
		for(int i=head[k];i!=-1;i=nextt[i])
			if(pre[i]==x)return id[i];
		return -1;
	}
}has;
void pre_bsgs(ll a,ll mod){
	ll am=quickmod(a,bsgs_inf,mod),pre=1;
	has.init();
	has.insert(pre,0);
	for(int i=1;i<=pre_inf+1;i++){
		pre=pre*am%mod;
		if(has.find(pre)==-1)has.insert(pre,i);
		else break;
	}
}
ll gcd(ll a,ll b){
	return !b?a:gcd(b,a%b);
}
void exgcd(ll a,ll b,ll &x,ll &y){
	if(!b)x=1,y=0;
	else{
		exgcd(b,a%b,y,x);
		y=y-(a/b)*x;
	}
}
ll inv(ll x,ll mod){
	ll a,b;
	exgcd(x,mod,a,b);
	return (a%mod+mod)%mod;
}
ll bsgs(ll a,ll b,ll mod){
	// 对于a不同的题目，pre放这里 对于a相同的题目，pre放外面
	pre_inf=sqrt(mod);
	bsgs_inf=mod/pre_inf+1;
	pre_bsgs(a,mod);

	ll base=inv(a,mod),pre=b;
	ll ans=1e18;
	int x=has.find(pre);
	if(x!=-1)ans=x*bsgs_inf;
	for(int i=1;i<bsgs_inf;i++){
		pre=pre*base%mod;
		int x=has.find(pre);
		if(x!=-1)ans=min(ans,x*bsgs_inf+i);
	}
	return ans;
}
ll exbsgs(ll a,ll b,ll mod){
	if(b==1||mod==1)return 0;
	ll g=gcd(a,mod),k=1,t=0;
	while(g!=1){
		if(b%g)return 1e18;
		t++;
		b/=g,mod/=g,k=k*(a/g)%mod;
		if(b==k)return t;
		g=gcd(a,mod);
	}

	ll ans=bsgs(a,b*inv(k,mod)%mod,mod);
	if(ans==1e18)return 1e18;
	else return ans+t;
}

int main(){
	int t;scanf("%d",&t);
	while(t--){
		ll n,x0,a,b,p;scanf("%lld%lld%lld%lld%lld",&n,&x0,&a,&b,&p);
		ll less=quickmod((a*x0-x0+b)%p,p-2,p);
		pre_inf=pow(p,2.0/3.0);//
		bsgs_inf=p/pre_inf+1;//
		pre_bsgs(a,p);
		int q;scanf("%d",&q);
		while(q--){
			ll v;scanf("%lld",&v);
			if(a==0){
				if(x0==v)printf("0\n");
				else if(b==v&&1<n)printf("1\n");
				else printf("-1\n");
			}
			else if(a==1){
				ll ans=(v-x0+p)%p*quickmod(b,p-2,p)%p;
				if(ans<n)printf("%lld\n",ans);
				else printf("-1\n");
			}
			else{
				ll tmp=(b+(a-1)*v%p)%p*less%p;
				ll ans=bsgs(a,tmp,p);
				if(ans<n)printf("%lld\n",ans);
				else printf("-1\n");
			}
		}
	}
}
