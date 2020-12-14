/*
Linear Sieve 
适用于各种积性函数
*/
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define N 10000000
vector<int> primes;
bool isPrime[N+1];
int mo[N+1];
int phi[N+1];
int num;
void Sieve(int n){
    num=0;
    memset(isPrime,true,sizeof(isPrime));
    phi[1]=1;
    mo[1]=1;
    for (int i=2;i<=n;++i){
        if (isPrime[i]) {
            primes.push_back(i);
            mo[i]=-1;
            phi[i]=i-1;
        }
        for (int j=0;j<primes.size() && primes[j]*i<=n;++j){
            isPrime[primes[j]*i]=false;
            if (i%primes[j]==0){
                mo[primes[j]*i]=0;
                phi[primes[j]*i]=phi[i]*primes[j];
                break;
            }
            else{
                phi[primes[j]*i]=phi[primes[j]]*phi[i];
                mo[primes[j]*i]=-mo[i];
            }
        }
    }
}

//区间埃氏筛 效率O( (r-l)loglog(r-l) )
bool segPrime[N];
using ll=long long;
ll SegmentSieve(ll l,ll r){
    if (l<2) l=2;
    ll ans=r-l+1;
    for (ll i=l;i<=r;++i) segPrime[i-l]=true;
    for (auto p:primes){
        if (p*p>r) break;
        for (ll i=max((l+p-1)/p,2ll)*p;i<=r;i+=p){
            segPrime[i-l]=false;
        }
    }
    return ans;
}
int main()
{
    Sieve(10000000);
    cout<<num;
    //for (int i=0;primeList[i]<4000;++i) printf("%d ",primeList[i]);
}