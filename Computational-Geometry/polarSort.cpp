#include <bits/stdc++.h>
using namespace std;
long long x_0,y_0;
long long cross(long long x1,long long y1,long long x2,long long y2){
    return x1*y2-x2*y1;
}
int Quadrant(int x,int y){
    if (x>0 && y>=0) return 1;
    if (x<=0 && y>0) return 2;
    if (x<0 && y<=0) return 3;
    return 4;
}
struct point{
    long long x,y;
    point(){}
    point(long long _x,long long _y){
        x=_x; y=_y;
    }
    bool operator<(const point& b)const{
        //return atan2(double(y-y_0),double(x-x_0))<atan2(double(b.y-y_0),double(b.x-x_0));
        point tmp1=*this,tmp2=b;
        tmp1.x-=x_0; tmp1.y-=y_0;
        tmp2.x-=x_0; tmp2.y-=y_0;
        int q1=Quadrant(tmp1.x,tmp1.y);
        int q2=Quadrant(tmp2.x,tmp2.y);
        if (q1==q2) return tmp1.x*tmp2.y-tmp1.y*tmp2.x>0;
        return q1<q2;
    }
};
point pts[10001];
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        scanf("%lld %lld",&pts[i].x,&pts[i].y);
    }
    sort(pts,pts+n);
    for (int i=0;i<n;++i){
        printf("%lld %lld\n",pts[i].x,pts[i].y);
    }
}