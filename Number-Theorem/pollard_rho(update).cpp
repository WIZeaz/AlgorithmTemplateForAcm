#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
#define ll long long
const int S=8,N=50000;// S为随机判断次数，一般8-10次就够了
int num=0;
ll fac[300];

// long long范围的乘法 a,b,c < 2^63
ll mult_mod(ll a,ll b,ll c) {
	ll d=(long double)a/c*b+1e-8;
	ll r=a*b-d*c;
	if(r<0)return r+c;
	return r;
}

// long long 范围的快速幂 a,b,c < 2^63
ll pow_mod(ll a,ll b,ll c) {
	ll base=a%c,ans=1;
	while(b) {
		if(b&1)ans=mult_mod(ans,base,c);
		base=mult_mod(base,base,c);
		b>>=1;
	}
	return ans;
}

bool Miller_Rabin(ll n) {
	if((n&1)==0&&n<2)return false;
	if(n==2)return true;

	ll x=n-1,t=0;
	while((x&1)==0)x>>=1,t++;

	for(int i=0; i<S; i++) {
		ll a=rand()%(n-1)+1;
		a=pow_mod(a,x,n);
		ll pre=a;
		for(int o=1; o<=t; o++) {
			a=mult_mod(a,a,n);
			if(a==1&&pre!=1&&pre!=n-1)return false;
			pre=a;
		}
		if(a!=1)return false;
	}
	return true;
}

ll gcd(ll a,ll b) {
	ll t;
	while(b) {
		t=a;
		a=b;
		b=t%b;
	}
	if(a>=0)return a;
	return -a;
}

ll maxx=0;

ll pollard_rho(ll n) {
	ll c=rand()%(n-1)+1;
	ll a=0,b=0,t=1,val=1;
	for(ll k=1;; k<<=1,b=a,val=1) {
		for(ll i=1; i<=k; i++) {
			a=(mult_mod(a,a,n)+c)%n;
			val=mult_mod(val,abs(a-b),n);
			if(i%127==0){
				t=gcd(n,val);
				if(t>1)return t;
			}
		}
		t=gcd(n,val);
		if(t>1)return t;
	}
}

void findfac(ll n) {
	if(n==1)return;
	if(Miller_Rabin(n)) {
		maxx=max(maxx,n);
		return;
	}

	ll p=n;
	while(p>=n)p=pollard_rho(p);

	if(p>maxx)findfac(p);
	while(n%p==0)n/=p;
	if(n>maxx)findfac(n);
}

int main() {
	srand((unsigned)time(NULL));

	int t;
	cin>>t;
	while(t--) {
		ll n;
		cin>>n;
		if(Miller_Rabin(n))cout<<"Prime\n";
		else {
			maxx=0;
			findfac(n);
			cout<<maxx<<endl;
		}
	}
}
