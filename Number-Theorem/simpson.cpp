#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

double a;
double f(double x){
    return pow(x,a/x-x);
}
double simpson(double l,double r){
    double mid=(l+r)/2.0;
    return (r-l)*(f(l)+4*f(mid)+f(r))/6.0;
}
double solve(double l,double r,double ans,double eps){
    double mid=(l+r)/2.0;
    double ansl=simpson(l,mid),ansr=simpson(mid,r);
    if(fabs(ansl+ansr-ans)<=15*eps)return ansl+ansr+(ansl+ansr-ans)/15.0;
    return solve(l,mid,ansl,eps/2.0)+solve(mid,r,ansr,eps/2.0);
}
double solve(double l,double r,double eps){
    return solve(l,r,simpson(l,r),eps);
}

int main(){
    scanf("%lf",&a);
    if(a<0)printf("orz");
    else printf("%.5lf\n",solve(1e-10,15,1e-6));
}