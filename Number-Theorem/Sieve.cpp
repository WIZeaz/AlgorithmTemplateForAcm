/*
Linear Sieve 
适用于各种积性函数
*/
#include <iostream>
#include <cstring>
using namespace std;
#define N 100000
int primeList[N+1];
bool isPrime[N+1];
int mo[N+1];
int phi[N+1];
int num;
void Sieve(int n)
{
    num=0;
    memset(isPrime,true,sizeof(isPrime));
    phi[1]=1;
    mo[1]=1;
    for (int i=2;i<=n;++i){
        if (isPrime[i]) {
            primeList[num]=i;
            mo[i]=-1;
            phi[i]=i-1;
            ++num;
        }
        for (int j=0;j<num && primeList[j]*i<=n;++j){
            isPrime[primeList[j]*i]=false;
            if (i%primeList[j]==0){
                mo[primeList[j]*i]=0;
                phi[primeList[j]*i]=phi[i]*primeList[j];
                break;
            }
            else{
                phi[primeList[j]*i]=phi[primeList[j]]*phi[i];
                mo[primeList[j]*i]=-mo[i];
            }
        }
    }
}
int main()
{
    Sieve(1000);
    for (int i=1;i<=1000;++i) printf("%d ",phi[i]);
}