#include <iostream>
#include <cstring>
#include <set>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <random>
using namespace std;
#define S 5
mt19937_64 gen(time(0));
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
long long Max;
void Pollard_rho(long long x){
    if (x<2) return;
    if (isPrime(x)) {list[num]=x; ++num; return;}
    long long p=1;
    while (p==1){
        long long a,b;
        a=gen()%x; 
        b=gen()%x;
        p=gcd(ABS(a-b),x);
    }
    while (x%p==0) {x/=p;}
    Pollard_rho(p);
    Pollard_rho(x);
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