//扩展欧几里得算法(exgcd)，用于求整数域上二元一次方程的解，求乘法逆元等
//貌似O(logn)
#include<iostream>
#define ll long long
using namespace std;

//ax+by=z 有解条件：gcd(a,b)|z
//ax+by=gcd(a,b)
//求出一组特解
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1;
        y=0;
        return a;//gcd(a,b)
    }
    ll gcd_ab=exgcd(b,a%b,x,y);
    ll temp=x;
    x=y;
    y=temp-a/b*y;
    return gcd_ab;
}