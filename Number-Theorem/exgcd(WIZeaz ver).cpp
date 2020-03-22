#include <iostream>
using namespace std;
long long exgcd(long long a,long long b,long long &x,long long &y){
    if (b==0){ x=1; y=0; return a;}
    long long t=exgcd(b,a%b,y,x);
    y=y-(a/b)*x;
    return t;
}
int main()
{
    long long a,b,c;
    cin>>a>>b>>c;
    long long x,y;
    long long t=exgcd(a,b,x,y);
    if (c%t==0){
        cout<<x*c/t<<' '<<y*c/t;
    } else cout<<"No solution!";
}