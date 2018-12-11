#include <iostream>
#include <cstring>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define S 10
long long ABS(long long x){
    if (x>=0) return x;
    return -x;
}
long long mul(long long x,long long y,long long mod){
    long long ans=0;
    x%=mod;
    y%=mod;
    while (y!=0){
        if (y&1){
            ans=(ans+x)%mod;
        }
        x=(x<<1)%mod;
        y>>=1;
    }
    return ans;
}
long long QuickPower(long long x,long long y,long long p) //unit*x=x
{
    if (y==0) return 1;
    long long tmp=x;
    long long ans=1;
    while (y>0){
        if (y&1) ans=mul(ans,tmp,p);
        tmp=mul(tmp,tmp,p);
        y=y>>1;
    }
    return ans;
}

bool isPrime(long long x){
    if (x<=1) return false;
    if (x==2) return true;
    if ((x&1)==0) return false; 
    for (int i=0;i<S;++i){
        long long a=rand()%(x-2)+2;
        long long d=x-1;
        while ((d&1)==0) d>>=1;
        long long tmp=QuickPower(a,d,x);
        while (d!=x-1 && tmp!=x-1 && tmp!=1){
            tmp=mul(tmp,tmp,x);
            d<<=1;
        }
        if ((tmp==1 && (d&1)==0) || (tmp==x-1 && d==x-1) || (tmp!=x-1 && tmp!=1)) return false;
    }
    return true;
}

long long gcd(long long a,long long b)
{
    long long c;
    while (b!=0){
        c=a%b;
        a=b;
        b=c;
    }
    return a;
}

long long list[100001];
int num;

long long f(long long x,long long c,long long mod)
{
    return (mul(x,x,mod)+c)%mod;
}

void Pollard_rho(long long x){
    if (isPrime(x)) {list[num]=x; ++num; return;}
    long long p=1;
    long long c=0;
    while (p==1){
        long long a,b;
        ++c;
        a=rand()%x; 
        b=f(a,c,x);
        while (a!=b){
            p=gcd(ABS(a-b),x);
            if (p>1) break;
            a=f(a,c,x);
            b=f(f(b,c,x),c,x);
        }
    }
    Pollard_rho(p);
    Pollard_rho(x/p);
}

int main()
{
    long long n;
    while (cin>>n){
        num=0;
        Pollard_rho(n);
        for (int i=0;i<num;++i) cout<<list[i]<<' ';
        cout<<endl;
    }
    return 0;
}