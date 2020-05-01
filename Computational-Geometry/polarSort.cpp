#include <bits/stdc++.h>
using namespace std;
long long cross(long long x1,long long y1,long long x2,long long y2){
    return x1*y2-x2*y1;
}
struct Point{
    long long x,y,h;
    Point(){}
    Point(long long _x,long long _y){
        x=_x; y=_y;
    }
    int quadrant() const{
        if (x>0 && y>=0) return 1;
        if (x<=0 && y>0) return 2;
        if (x<0 && y<=0) return 3;
        return 4;
    }
    long long dis2() const{
        return x*x+y*y;
    }
    bool operator<(const Point& b)const{
        int q1=quadrant();
        int q2=b.quadrant();
        if (q1!=q2) return q1<q2;
        long long c=cross(x,y,b.x,b.y);
        if (c!=0) return c>0;
        return dis2()<b.dis2();
    }
    long long operator^(const Point& b) const{
        return cross(x,y,b.x,b.y);
    }
};
Point pts[10001];
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        scanf("%lld %lld",&pts[i].x,&pts[i].y);
    }
    //polar sort, with (0,0) as polar
    sort(pts,pts+n);
    for (int i=0;i<n;++i){
        printf("%lld %lld\n",pts[i].x,pts[i].y);
    }
}