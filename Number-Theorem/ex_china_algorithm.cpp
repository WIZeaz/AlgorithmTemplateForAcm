#include<iostream>
#include<cstring>
#define ll long long
#define MAX 25//方程组数量
using namespace std;

//exgcd
ll exgcd(ll aa,ll bb,ll &x,ll &y){
    if(bb==0){
        x=1;
        y=0;
        return aa;
    }
    ll gcd_ab=exgcd(bb,aa%bb,x,y);
    ll temp=x;
    x=y;
    y=temp-aa/bb*y;
    return gcd_ab;
}

ll x0=0,c0=1;//通解形式x=x0+k*c0
ll a[MAX],mod[MAX];//同余方程组,a为等号右边的常数，mod为模数

//扩展中国剩余定理，num为实际方程数
bool ex_china(int num){
    x0=a[0];c0=mod[0];//第一个方程的通解
    for(int i=1;i<num;++i){
        //联立x=x0+k*c0和x=ai(mod mi),解出k
        ll right=a[i]-x0;
        ll holder0=0,holder1=0;
        ll gcd=exgcd(c0,mod[i],holder0,holder1);
        if(right%gcd!=0){
            return false;//无解
        }

        holder1=mod[i]/gcd;
        holder0*=right/gcd;
        holder0=(holder0%holder1+holder1)%holder1;
        x0+=holder0*c0;
        c0*=holder1;
        x0=(x0%c0+c0)%c0;
    }
    return true;
}

int main(){
    //组织a数组和mod数组
    
    //if(ex_china())
    //else
}