//bzoj3295
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int n,m;
struct point{
    int x,y;
    int num;
    bool operator <(const point& b) const{
        return x<b.x;
    }
};

int lowbit(int x){return x&(-x);}
struct TreeArray{
    int n;
    long long a[200001];
    void setRange(int N) { n=N;}
    void clear() {n=0; memset(a,0,sizeof(a));}
    void verify(int pos,long long val){
        for (int i=pos;i<=n;i+=lowbit(i))
            a[i]+=val;
    }
    long long query(int pos){
        long long rnt=0;
        for (int i=pos;i>0;i-=lowbit(i)) rnt=rnt+a[i];
        return rnt;
    }
    void clear(int pos){
        for (int i=pos;i<=n;i+=lowbit(i)) a[i]=0;
    }
};
TreeArray tr1,tr2;
long long ans[200001];
point pts[200001];
long long sum;

bool cmp(point a,point b){
    return a.num<b.num;
}

void cdq(int l,int r){
    if (l==r) return;
    int mid=l+r>>1;
    cdq(l,mid);
    sort(pts+mid+1,pts+r+1);
    int i=l; int j=mid+1;
    for (int k=l;k<=mid;++k) tr2.verify(pts[k].y,1); 
    for (int k=l;k<=r;++k)
        if (i>mid) {ans[pts[j].num]+=tr2.query(m+1)-tr2.query(pts[j].y); tr1.verify(pts[j].y,1); ++j; }
        else if (j>r) {ans[pts[i].num]+=tr1.query(m+1)-tr1.query(pts[i].y); tr2.verify(pts[i].y,-1); ++i; }
        else {
            if (pts[j]<pts[i]) {ans[pts[j].num]+=tr2.query(m+1)-tr2.query(pts[j].y); tr1.verify(pts[j].y,1); ++j; sum+=mid-i+1; }
            else {ans[pts[i].num]+=tr1.query(m+1)-tr1.query(pts[i].y); tr2.verify(pts[i].y,-1); ++i; }
        }
    for (int k=mid+1;k<=r;++k){
        tr1.verify(pts[k].y,-1);
    }
    sort(pts+mid+1,pts+r+1,cmp);
    cdq(mid+1,r);
    sort(pts+l,pts+r+1);
}
int pos[200001];
int del[200001];
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i){
        scanf("%d",&pts[i].x); 
        pts[i].num=i;
        pts[i].y=m+1;
        pos[pts[i].x]=i;
        
    }
    for (int i=1;i<=m;++i){
        scanf("%d",&del[i]); 
        pts[pos[del[i]]].y=i;
    }
    tr1.setRange(m+1);
    tr2.setRange(m+1);
    memset(ans,0,sizeof(ans));
    sum=0;
    cdq(1,n);
    /*for (int i=1;i<=n;++i) printf("%d ",ans[i]);
    printf("\n");*/
    for (int i=1;i<=m;++i){
        printf("%lld\n",sum);
        sum-=ans[pos[del[i]]];
    }
}