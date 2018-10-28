#include <iostream>
#include <cstring>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define S 10

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

int main()
{
    long long n;
    while (cin>>n){
        if (isPrime(n)) cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}