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
	while((1<<bit)<len)bit++;
	for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
}

void ntt(ll x[],int len,int opt){
	for(int i=0;i<len;i++)
		if(i<rev[i])swap(x[i],x[rev[i]]);
	for(int mid=1;mid<len;mid<<=1){
		ll tmp=quickpow(g,(mod-1)/(mid*2));
		if(opt==-1)tmp=quickpow(tmp,mod-2);
		for(int i=0,add=mid<<1;i<len;i+=add){
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
	getrev(len);

	for(int i=0;i<lena;i++)ntta[i]=a[i];
	for(int i=lena;i<len;i++)ntta[i]=0;
	for(int i=0;i<lenb;i++)nttb[i]=b[i];
	for(int i=lenb;i<len;i++)nttb[i]=0;

	ntt(ntta,len,1),ntt(nttb,len,1);
	for(int i=0;i<len;i++)ntta[i]=ntta[i]*nttb[i]%mod;
	ntt(ntta,len,-1);

	int optmod=quickpow(len,mod-2);
	for(int i=0;i<len;i++)ntta[i]=ntta[i]*optmod%mod;

	return len;
}

char s1[N+10],s2[N+10];
int a[N+10],b[N+10],ans[2*N+10];
// 下标从0开始
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++)scanf("%d",&a[i]);
	for(int i=0;i<=m;i++)scanf("%d",&b[i]);

	int len=solve(a,b,n+1,m+1),pre=0;

	for(int i=0;i<=n+m;i++){
		ans[i]=int(ntta[i]+0.5);
		printf("%d ",ans[i]);
	}
}
