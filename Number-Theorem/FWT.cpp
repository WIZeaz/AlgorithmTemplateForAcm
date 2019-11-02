#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
const ll inv2=(mod+1)/2;

void fwt_or(ll a[],int n,int opt){
	for(int i=1;i<n;i<<=1)
		for(int j=0,add=i<<1;j<n;j+=add)
			for(int k=0;k<i;k++)
				if(opt==1)a[i+j+k]=(a[i+j+k]+a[j+k])%mod;
				else a[i+j+k]=(a[i+j+k]-a[j+k]+mod)%mod;
}

void fwt_and(ll a[],int n,int opt){
	for(int i=1;i<n;i<<=1)
		for(int j=0,add=i<<1;j<n;j+=add)
			for(int k=0;k<i;k++)
				if(opt==1)a[j+k]=(a[j+k]+a[i+j+k])%mod;
				else a[j+k]=(a[j+k]-a[i+j+k]+mod)%mod;
}

void fwt_xor(ll a[],int n,int opt){
	for(int i=1;i<n;i<<=1)
		for(int j=0,add=i<<1;j<n;j+=add)
			for(int k=0;k<i;k++){
				int x=a[j+k],y=a[i+j+k];
				a[j+k]=(x+y)%mod,a[i+j+k]=(x-y+mod)%mod;
				if(opt==-1)a[j+k]=a[j+k]*inv2%mod,a[i+j+k]=a[i+j+k]*inv2%mod;
			}
}

// 下标从0开始
ll a[(1<<20)+10],b[(1<<20)+10],base[(1<<20)+10];
int main(){
	int n,t;scanf("%d%d",&n,&t);
	n=(1<<n);
	for(int i=0;i<n;i++)scanf("%lld",&a[i]);
	b[0]=1;
	for(int i=1;i<n;i<<=1)b[i]=1;
	fwt_xor(a,n,1);
	fwt_xor(b,n,1);
	for(int i=0;i<n;i++)base[i]=b[i];
	t--;
	while(t){
		if(t&1)for(int i=0;i<n;i++)b[i]=b[i]*base[i]%mod;
		for(int i=0;i<=n;i++)base[i]=base[i]*base[i]%mod;
		t>>=1;
	}
	for(int i=0;i<n;i++)a[i]=a[i]*b[i]%mod;
	fwt_xor(a,n,-1);
	for(int i=0;i<n;i++)printf("%lld ",a[i]);
}