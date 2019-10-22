// 多项式四则运算
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> V;
ll quick_pow(ll base,ll b,ll mod){
	ll res=1;
	while(b){
		if(b&1)res=res*base%mod;
		base=base*base%mod;b>>=1;
	}
	return res;
}
ll get_inv(ll x,ll mod){
	return quick_pow(x,mod-2,mod);
}
const int mod=998244353;
const int N=200000;
const int g=3;
int rev[2*N+10];
int getrev(int len){
	int bit=0,n=1;
	while((1<<bit)<len)bit++;
	for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	return 1<<bit;
}
void ntt(V &x,int len,int opt){
	for(int i=0;i<len;i++)
		if(i<rev[i])swap(x[i],x[rev[i]]);
	for(int mid=1;mid<len;mid<<=1){
		ll tmp=quick_pow(g,(mod-1)/(mid*2),mod);
		if(opt==-1)tmp=quick_pow(tmp,mod-2,mod);
		for(int i=0,add=mid<<1;i<len;i+=add){
			ll base=1;
			for(int j=i;j<i+mid;j++,base=base*tmp%mod){
				int a=x[j],b=base*x[j+mid]%mod;
				x[j]=(a+b)%mod,x[j+mid]=(a-b+mod)%mod;
			}
		}
	}
	if(opt==-1){
		int optmod=quick_pow(len,mod-2,mod);
		for(int i=0;i<len;i++)x[i]=x[i]*optmod%mod;
	}
}
V solve(const V &a,const V &b,int lena,int lenb){
	int len=1;
	while(len<lena+lenb)len<<=1;
	getrev(len);

	V ntta=a,nttb=b;
	ntta.resize(len),nttb.resize(len);

	ntt(ntta,len,1),ntt(nttb,len,1);
	for(int i=0;i<len;i++)ntta[i]=ntta[i]*nttb[i]%mod;
	ntt(ntta,len,-1);
	ntta.resize(a.size()+b.size()-1);

	return ntta;
}
V get_inv(const V &a){
	V res(1,get_inv(a[0],mod)),inv;
	int inf=1;
	while(inf<=a.size())inf<<=1;
	for(int i=2;i<inf;i<<=1){
		int len=getrev(i<<1);
		inv=a;inv.resize(len);res.resize(len);
		for(int j=i;j<len;j++)inv[j]=0;
		ntt(inv,len,1);ntt(res,len,1);
		for(int j=0;j<len;j++)
			res[j]=(2-inv[j]*res[j]%mod+mod)%mod*res[j]%mod;
		ntt(res,len,-1);
		for(int j=i;j<len;j++)res[j]=0;
	}
	res.resize(a.size());
	return res;
}
V operator+(const V &a,const V &b){
	V res=a;res.resize(max(a.size(),b.size()));
	for(int i=0;i<b.size();i++)res[i]=(res[i]+b[i])%mod;
	return res;
}
V operator-(const V &a,const V &b){
	V res=a;res.resize(max(a.size(),b.size()));
	for(int i=0;i<b.size();i++)res[i]=(res[i]-b[i]+mod)%mod;
	return res;
}
V operator*(const V &a,const V &b){
	return solve(a,b,a.size(),b.size());
}
V operator/(const V &a,const V &b){
	V res=a,x=b;
	reverse(res.begin(),res.end());
	reverse(x.begin(),x.end());
	int sz=1,deg=a.size()-b.size()+1;
	while(sz<=deg)sz<<=1;
	x.resize(sz);
	x=get_inv(x);
	x.resize(deg);
	res=res*x;
	res.resize(deg);
	reverse(res.begin(),res.end());
	return res;
}
V operator%(const V &a,const V &b){
	V res=a-(a/b)*b;
	res.resize(b.size()-1);
	return res;
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	V v(n);
	for(int i=0;i<n;i++)scanf("%lld",&v[i]),v[i]%=mod;
	auto x=BM::BM(v);
	for(int i=0;i<x.size();i++)x[i]=(x[i]+mod)%mod;
}