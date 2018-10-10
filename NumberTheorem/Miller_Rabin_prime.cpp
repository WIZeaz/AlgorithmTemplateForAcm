// 2018 ACM-ICPC 中国大学生程序设计竞赛线上赛-B
// https://nanti.jisuanke.com/t/25985
// 将任意偶数（n<2^63）分解为两质数相加

#include<cstdio>
#include<ctime>
#include<iostream>
using namespace std;
#define ull unsigned long long
const int S=8,N=50000;// S为随机判断次数，一般8-10次就够了
int prime[N+100]={0}, num=0;

void pre(){
    for(int i=2;i<=N;i++){
        if(!prime[i])prime[++num]=i;
        for(int o=1;o<=num&&prime[o]<=N/i;o++){
            prime[prime[o]*i]++;
            if(i%prime[o]==0)break;
        }
    }
}

// long long范围的乘法 a,b,c < 2^63
ull mult_mod(ull a,ull b,ull c){
    a%=c,b%=c;
    ull ans=0,base=a;
    while(b){
        //if(b&1)ans=(ans+base)%c;
        //base=(base<<1)%c;
        if(b&1){
			ans+=base;
            if(ans>c)ans-=c;
        }
        base<<=1;
        if(base>c)base-=c;
        b>>=1;
    }
    return ans;
}

// long long 范围的快速幂 a,b,c < 2^63
ull pow_mod(ull a,ull b,ull c){
    ull base=a%c,ans=1;
    while(b){
        if(b&1)ans=mult_mod(ans,base,c);
        base=mult_mod(base,base,c);
        b>>=1;
    }
    return ans;
}

bool Miller_Rabin(ull n){
    if(n&1==0&&n<2)return false;
    if(n==2)return true;

    // n-1=x* 2^t
    ull x=n-1,t=0;
    while(x&1==0)x>>=1,t++;
    
    for(int i=0;i<S;i++){
        ull a=rand()%(n-1)+1;
        a=pow_mod(a,x,n);
        ull pre=a;
        for(int o=1;o<=t;o++){
            a=mult_mod(a,a,n);
            if(a==1&&pre!=1&&pre!=n-1)return false;
            // 模板是这样写的 但是只用判 a!=1&&a!=n-1 就行了
            // 不懂.jpg
            pre=a;
        }
        if(a!=1)return false;
    }
    return true;

    // 骚方法 照样能过
    // 运用费马小定理
    /*for(int i=0;i<S;i++){
        ull a=rand()%(n-1)+1;
		if(pow_mod(a,n-1,n)!=1)return false;
    }
    return true;*/
}

int main(){
    pre();
    srand((unsigned)time(NULL));

    int t;
    scanf("%d", &t);
    while(t--){
        ull n;
        scanf("%llu", &n);
        for(int i=1;i<=num;i++){
            if(prime[i]&1&&Miller_Rabin(n-prime[i])){
                printf("%d %llu\n",prime[i],n-prime[i]);
                break;
            }
        }
        
    }
}
