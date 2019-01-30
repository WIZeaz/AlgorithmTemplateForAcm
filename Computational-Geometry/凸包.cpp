#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;
#define ll long long

inline int read() {
    int input=0,v=1;
    char c=getchar();
    while((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-')v=-1,c=getchar();
    while(c>='0'&&c<='9')input=input*10+c-'0',c=getchar();
    return v*input;
}

struct point {
    int x,y;
    point() {}
    point(int a,int b):x(a),y(b) {}
    point operator +(const point &b)const {
        return point(x+b.x,y+b.y);
    }
    point operator -(const point &b)const {
        return point(x-b.x,y-b.y);
    }
    double operator *(const point &b)const {
        return x*b.x+y*b.y;
    }
    double operator ^(const point &b)const {
        return x*b.y-y*b.x;
    }
};

inline double dis(point a,point b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

point a[11000],stack[11000];
int n,num,l;

bool cmp(point b,point c){
    double cmp=(b.y-a[1].y)*(c.x-a[1].x)-(c.y-a[1].y)*(b.x-a[1].x);
    if(!cmp)return b.x<c.x;
    return cmp<0;
}

// 返回凸包 stack[1~n]
void Graphm() {
    int k=1;
    for(int i=1; i<=n; i++)
        if(a[i].y<a[k].y||(a[i].y==a[k].y&&a[i].x<a[k].x))k=i;
    swap(a[1],a[k]);

    sort(a+2,a+1+n,cmp);
    //for(int i=1;i<=n;i++)printf("%d %d\n",a[i].x,a[i].y);
    if(n==1) {
        num=1;
        stack[1]=a[1];
    } else if(n==1) {
        num=2;
        stack[1]=a[1],stack[2]=a[2];
    } else {
        stack[1]=a[1];
        stack[2]=a[2];
        num=2;
        for(int i=3; i<=n;) {
            if(num!=1&&((stack[num]-stack[num-1])^(a[i]-stack[num-1]))<=0)
                num--;
            else
                stack[++num]=a[i++];
        }
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d %d",&a[i].x,&a[i].y);
    Graphm();

    double ans=0;
    // 叉乘计算面积
    for(int i=2;i<num;i++)
        ans+=((stack[i]-stack[1])^(stack[i+1]-stack[1]))/2.0;
    int anss=ans/50.0;
    printf("%d\n",anss);
}
