#include <bits/stdc++.h>
using namespace std;
int Quadrant(double x,double y){
    if (x>0 && y>=0) return 1;
    if (x<=0 && y>0) return 2;
    if (x<0 && y<=0) return 3;
    return 4;
}
double x_0,y_0;
struct point{
    double x,y;
    point(){x=0; y=0;}
    point(double  _x,double _y){
        x=_x; y=_y;
    }
    point operator - (const point &b)  const{
        return point(x-b.x,y-b.y);
    }
    double operator ^ (const point &b) const{
        return x*b.y-y*b.x;
    }
    bool operator<(const point& b)const{
        point tmp1=*this,tmp2=b;
        tmp1.x-=x_0; tmp1.y-=y_0;
        tmp2.x-=x_0; tmp2.y-=y_0;
        double t=tmp1.x*tmp2.y-tmp1.y*tmp2.x;
        if (fabs(t)<1e-8) return (tmp1.x*tmp1.x+tmp1.y*tmp1.y)<(tmp2.x*tmp2.x+tmp2.y*tmp2.y);
        return t>0;
    }
};
double dis(point a,point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double cross(point c,point a,point b){
    a.x-=c.x; a.y-=c.y;
    b.x-=c.x; b.y-=c.y;
    return a.x*b.y-a.y*b.x;
}
int graham(point pts[],int len,point rnt[]){
    
    int ind=0;
    for (int i=1;i<len;++i)
        if (pts[ind].x>pts[i].x || (pts[ind].x==pts[i].x && pts[ind].y>pts[i].y)) ind=i;
    swap(pts[0],pts[ind]);
    x_0=pts[0].x;
    y_0=pts[0].y;
    sort(pts+1,pts+len);
    rnt[0]=pts[0];
    int rntlen=1;
    for (int i=1;i<len;++i){
        while (rntlen>1 && ((rnt[rntlen-1]-rnt[rntlen-2])^(pts[i]-rnt[rntlen-1]))<0) --rntlen;
        rnt[rntlen]=pts[i];
        ++rntlen;
    }
    return rntlen;
}
point pts[10001];
point convexHull[10001];
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        scanf("%lf%lf",&pts[i].x,&pts[i].y);
    }
    int len=graham(pts,n,convexHull);
    double ans=0;
    for (int i=1;i<len;++i){
        ans+=dis(convexHull[i],convexHull[i-1]);
    }
    ans+=dis(convexHull[0],convexHull[len-1]);
    printf("%.2f",ans);
}