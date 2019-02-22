#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
struct state{
    long double x,y;
    state(){}
    state(long double _x,long double _y){x=_x; y=_y;}
};
state pts[1001];
int n;
long double dis(const state& a,const state& b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
long double f(state t)
{
    long double rnt=0;
    for (int i=0;i<n;++i) rnt+=dis(t,pts[i]);
    return rnt;
}
state getRandomState(const state& now,long double t)
{
    int dir=rand()%8;
    long double scale=100;
    t*=scale;
    switch(dir){
        case 0: return state(now.x-t,now.y); 
        case 1: return state(now.x-t,now.y+t); 
        case 2: return state(now.x,now.y+t); 
        case 3: return state(now.x+t,now.y+t); 
        case 4: return state(now.x+t,now.y); 
        case 5: return state(now.x+t,now.y-t);
        case 6: return state(now.x,now.y-t); 
        case 7: return state(now.x-t,now.y-t); 
    };
}
long double solve(){
    long double t=100,t_min=1e-14;
	const double delta=0.98;
    state now,next;
    long double nowval,nextval;
    srand(n);
    now=pts[0]; nowval=f(now);
    while (t>t_min){
        next=getRandomState(now,t);
        nextval=f(next);

        if (nextval<nowval || exp((nowval-nextval)/t)*RAND_MAX>=rand()){ now=next; nowval=nextval;}
        
        t*=delta;
    }
    return nowval;
}
int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        int tx,ty;
        scanf("%d%d",&tx,&ty);
        pts[i].x=tx; pts[i].y=ty;
    }
    //printf("%.0lf\n",solve());
    cout<<int(solve()+0.5f);
    return 0;
}