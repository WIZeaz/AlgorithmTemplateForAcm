#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=1400000;
const double PI=acos(-1.0);
const int mod=998244353;
const int g=3;// 原根

ll quickpow(ll a,ll b){
	ll ans=1,base=a;
	while(b){
		if(b&1)ans=ans*base%mod;
		base=base*base%mod;
		b>>=1;
	}
	return ans%mod;
}

int rev[2*N+10];
void getrev(int len){
	int bit=0;
	while((1<<bit)<len-1)bit++;
	for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
}

void ntt(ll x[],int len,int inv){
	for(int i=0;i<len;i++)
		if(i<rev[i])swap(x[i+1],x[rev[i]+1]);
	for(int mid=1;mid<len;mid<<=1){
		ll tmp=quickpow(g,(mod-1)/(mid*2));
		if(inv==-1)tmp=quickpow(tmp,mod-2);
		for(int i=1;i<=len;i+=(mid<<1)){
			ll base=1;
			for(int j=i;j<i+mid;j++,base=base*tmp%mod){
				int a=x[j],b=base*x[j+mid]%mod;
				x[j]=(a+b)%mod,x[j+mid]=(a-b+mod)%mod;
			}
		}
	}
}

ll ntta[2*N+10],nttb[2*N+10];
int solve(int a[],int b[],int lena,int lenb){
	int len=1;
	while(len<lena+lenb)len<<=1;

	for(int i=1;i<=lena;i++)ntta[i]=a[i];
	for(int i=lena+1;i<=len;i++)ntta[i]=0;
	for(int i=1;i<=lenb;i++)nttb[i]=b[i];
	for(int i=lenb+1;i<=len;i++)nttb[i]=0;

	getrev(len);
	ntt(ntta,len,1),ntt(nttb,len,1);
	for(int i=1;i<=len;i++)ntta[i]=ntta[i]*nttb[i]%mod;
	ntt(ntta,len,-1);

	int invmod=quickpow(len,mod-2);
	for(int i=1;i<=len;i++)ntta[i]=ntta[i]*invmod%mod;

	return len;
}

char s1[N+10],s2[N+10];
int a[N+10],b[N+10],ans[2*N+10];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n+1;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m+1;i++)scanf("%d",&b[i]);

	int len=solve(a,b,n+1,m+1),pre=0;

	for(int i=1;i<=n+m+1;i++){
		ans[i]=ntta[i];
		printf("%d ",ans[i]);
	}
}
