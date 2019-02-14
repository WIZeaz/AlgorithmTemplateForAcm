#include <iostream>
#include <cstring>
using namespace std;
struct node{
    int l,r,lc,rc;
    int val;
};
const int N=100000;
const int root=0;
struct Segment_Tree{
    //constants

    //clarification
    int num;    
    node tr[2*N];

    //methods
    void setRange(int l,int r,int now=root){
        num=0;
        build(l,r,now);
    }
    void build(int l,int r,int now){
        tr[now].l=l; tr[now].r=r; tr[now].val=0;
        if (l<r){
            int mid=(l+r)>>1;
            ++num; tr[now].lc=num;
            ++num; tr[now].rc=num;
            build(l,mid,tr[now].lc);
            build(mid+1,r,tr[now].rc);
        }
    }
    void update(int pos,int val,int now=root){
        int mid=(tr[now].l+tr[now].r)>>1;
        if (tr[now].l==pos && tr[now].r==pos) {
            //change the value you need
            tr[now].val+=val; 
            return;
        } else if (pos<=mid) update(pos,val,tr[now].lc);
        else update(pos,val,tr[now].rc);
        //write parent update here
        tr[now].val=tr[tr[now].lc].val+tr[tr[now].rc].val;
    }
    /*void update(int l,int r,int val,int now=root){
        
        if (tr[now].l==l && tr[now].r==r) {
            //lazy operation
            tr[now].val=val; 
            return;
        } else {
            //Pushdown here
            //Pushdown end
            int mid=(tr[now].l+tr[now].r)>>1;
            if (pos<=mid) update(pos,val,tr[now].lc);
            else update(pos,val,tr[now].rc);
            //write parent update here
            tr[now].val=tr[tr[now].lc].val+tr[tr[now].rc].val;
        }
    }*/
    int query(int l,int r,int now=root){
        if (tr[now].l==l && tr[now].r==r) return tr[now].val;
        else {
            int mid=(tr[now].l+tr[now].r)>>1;
            if (r<=mid) return query(l,r,tr[now].lc);
            else if (l>mid) return query(l,r,tr[now].rc);
            else return query(l,mid,tr[now].lc)+query(mid+1,r,tr[now].rc);
        }
    }

};
Segment_Tree tr;
int main()
{
    int T;
    char str[100];
    scanf("%d",&T);
    for (int Case=1;Case<=T;++Case){
        int n,a,b;
        scanf("%d",&n);
        tr.setRange(1,n);
        for (int i=1;i<=n;++i){
            int tmp;
            scanf("%d",&tmp);
            tr.update(i,tmp);
        }
        printf("Case %d:\n",Case);
        while (1){
            scanf("%s",str);
            if (strcmp(str,"End")==0) break;
            scanf("%d%d",&a,&b);
            if (strcmp(str,"Add")==0){
                tr.update(a,b);
            } else if (strcmp(str,"Sub")==0){
                tr.update(a,-b);
            } else {
                printf("%d\n",tr.query(a,b));
            }
        }
    }
}