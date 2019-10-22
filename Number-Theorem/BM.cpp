// BM算法，通过给前n项，可以求最短的递推式
// 用NTT优化，可以在O(nlogn)的效率下求得第N项
// 对模数有要求，需要是能用NTT解决的
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using V=vector<ll>;
ll quick_pow(ll base,ll b,ll mod){
	ll res=1;
	while(b){
		if(b&1)res=res*base%mod;
		base=base*base%mod;
		b>>=1;
	}
	return res;
}
ll get_inv(ll x,ll mod){return quick_pow(x,mod-2,mod);}
const int mod=998244353;
namespace NTT{
	const int N=20000;
	const int g=3;
	int rev[2*N+10];
	ll ntta[2*N+10],nttb[2*N+10];
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
		ntta.resize(len);nttb.resize(len);

		ntt(ntta,len,1),ntt(nttb,len,1);
		for(int i=0;i<len;i++)ntta[i]=ntta[i]*nttb[i]%mod;
		ntt(ntta,len,-1);

		return ntta;
	}
}
V get_inv(const V &a){
	V res(1,get_inv(a[0],mod)),inv;
	int inf=1;
	while(inf<=a.size())inf<<=1;
	for(int i=2;i<inf;i<<=1){
		int len=NTT::getrev(i<<1);
		inv=a;inv.resize(len);res.resize(len);
		for(int j=i;j<len;j++)inv[j]=0;
		NTT::ntt(inv,len,1);NTT::ntt(res,len,1);
		for(int j=0;j<len;j++)
			res[j]=(2-inv[j]*res[j]%mod+mod)%mod*res[j]%mod;
		NTT::ntt(res,len,-1);
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
	return NTT::solve(a,b,a.size(),b.size());
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
namespace BM{
	using V=vector<ll>;
	const int N=20000;
	V pow(const V &m,ll n){
		int k=m.size()-1;
		V r(k),x(k);
		r[0]=x[1]=1;
		while(n){
			if(n&1)r=x*r%m;
			n>>=1;x=x*x%m;
		}
		return r;
	}
	ll solve(const V &a,const V &b,ll n){
		int k=a.size()-1;
		if(n<=k)return b[n-1];
		if(a.size()==2)return b[0]*quick_pow(a[0],n-1,mod)%mod;
		V r=pow(a,n-1);
		ll ans=0;
		for(int i=0;i<k;i++)ans=(ans+r[i]*b[i]%mod)%mod;
		return (ans+mod)%mod;
	}
	// 返回的式子，删掉首项后调转头尾，即为BM递推式
	V BM(const V &x){
		V a{-1},b{-1};
		ll l=0,m=1,c=1;
		for(int n=0;n<x.size();n++){
			ll d=0;
			for(int i=0;i<l+1;i++)d=(d+a[i]*x[n-i]%mod)%mod;
			if(d==0){
				m++;continue;
			}
			V cur=a;
			ll f=mod-d*get_inv(c,mod)%mod;
			for(int i=a.size();i<b.size()+m;i++)a.push_back(0);
			for(int i=0;i<b.size();i++)a[i+m]=(a[i+m]+f*b[i]%mod)%mod;
			if(2*l>n){
				m++;continue;
			}
			l=n+1-l;b.swap(cur);c=d;m=1;
		}
		reverse(a.begin(),a.end());
		return a;
	}
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	vector<ll>v;
	for(int i=1;i<=n;i++){
		ll x;scanf("%lld",&x);
		x%=mod;
		v.push_back(x);
	}
	auto x=BM::BM(v);
	for(int i=0;i<x.size();i++)x[i]=(x[i]+mod)%mod;
	auto y=x;
	y.pop_back();
	reverse(y.begin(),y.end());
	for(auto i:y)printf("%lld ",i);printf("\n");
	printf("%lld\n",BM::solve(x,v,m+1));
}