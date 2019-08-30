#include <bits/stdc++.h>
using namespace std;
struct permanentSegmentTree{
    struct node{
        int lc,rc,l,r;
        int val;
    };
    node tr[5000001];
    int roots[200001];
    int num;
    int vernum;
    void setRange(int l,int r){
        num=0;
        vernum=0;
        roots[0]=0;
        build(l,r,0);
    }
    void build(int l,int r,int now){
        tr[now].l=l; tr[now].r=r; tr[now].val=0; 
        if (tr[now].l!=tr[now].r){
            int mid=l+r>>1;
            tr[now].lc=++num;
            tr[now].rc=++num;
            build(l,mid,tr[now].lc);
            build(mid+1,r,tr[now].rc);
        }
    }
    void update(int pos,int val){
        roots[vernum+1]=update(pos,val,roots[vernum]);
        ++vernum;
    }
    int update(int pos,int val,int now){
        int t=++num;
        tr[t]=tr[now];
        if (tr[t].l==tr[t].r){
            tr[t].val+=val;
        } else {
            int mid=tr[now].l+tr[now].r>>1;
            if (pos<=mid) tr[t].lc=update(pos,val,tr[now].lc);
            else tr[t].rc=update(pos,val,tr[now].rc);
            tr[t].val=tr[tr[t].lc].val+tr[tr[t].rc].val;
        }
        return t;
    }
    int query(int v1,int v2,int k){
        return _query(roots[v1],roots[v2],k);
    }
    int _query(int now1,int now2,int k){
        if (tr[now1].l==tr[now1].r) return tr[now1].l;
        int t=tr[tr[now2].lc].val-tr[tr[now1].lc].val;
        if (t>=k) return _query(tr[now1].lc,tr[now2].lc,k);
        else return _query(tr[now1].rc,tr[now2].rc,k-t);
    }
};
permanentSegmentTree tr;
int a[500001];
int b[500001];
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;++i){
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b,b+n);
    int len=unique(b,b+n)-b;
    tr.setRange(0,len-1);
    for (int i=0;i<n;++i){
        int t=lower_bound(b,b+len,a[i])-b;
        tr.update(t,1);
    }
    for (int i=0;i<m;++i){
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        printf("%d\n",b[tr.query(l-1,r,k)]);
    }
}