#include <iostream>
#include <cstring>
#include <string>
using namespace std;
struct Segment_Tree{
    //constants and innerclass
    struct node{
        int l,r,lc,rc;
        int val,cover;
    };
    static const int N=100000;
    static const int root=0;

    //variables
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
    void lazyupdate(node &x, int increment){
        //set flag and update
        x.cover+=increment;
        x.val+=increment*(x.r-x.l+1);
    }
    void pushdown(node &f,node &lc, node &rc){
        //transfer flag and update
        lazyupdate(lc,f.cover);
        lazyupdate(rc,f.cover);
        f.cover=0;
    }
    void pushup(node &f,node &lc,node &rc){
        f.val=lc.val+rc.val;
    }

    //warning: don't invoke both update and updateR in single segment tree, it may cause error
    void update(int pos,int val,int now=root){
        int mid=(tr[now].l+tr[now].r)>>1;
        if (tr[now].l==tr[now].r) {
            tr[now].val+=val; 
            return;
        } else if (pos<=mid) update(pos,val,tr[now].lc);
        else update(pos,val,tr[now].rc);
        //write parent update here
        pushup(tr[now],tr[tr[now].lc],tr[tr[now].rc]);
    }

    void updateR(int l,int r,int val,int now=root){
        
        if (tr[now].l==l && tr[now].r==r) {
            //lazy operation
            lazyupdate(tr[now],val);
            return;
        } else {
            //Pushdown here
            if (tr[now].cover!=0) pushdown(tr[now],tr[tr[now].lc],tr[tr[now].rc]);

            int mid=(tr[now].l+tr[now].r)>>1;
            if (r<=mid) updateR(l,r,val,tr[now].lc);
            else if (l>mid) updateR(l,r,val,tr[now].rc);
            else {
                updateR(l,mid,val,tr[now].lc);
                updateR(mid+1,r,val,tr[now].rc);
            }
            //write parent update here
            pushup(tr[now],tr[tr[now].lc],tr[tr[now].rc]);
        }
    }
    int query(int l,int r,int now=root){
        if (tr[now].l==l && tr[now].r==r) return tr[now].val;
        else {
            if (tr[now].cover!=0) pushdown(tr[now],tr[tr[now].lc],tr[tr[now].rc]);
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
    int l,r;
    cout<<"input range of segment tree: ";
    cin>>l>>r;
    tr.setRange(l,r);
    cout<<"supported operations: \nADD l r val\nQUERY l r\n";
    string str;
    int val;
    while (cin>>str>>l>>r){
        if (str=="add"){
            cin>>val;
            tr.updateR(l,r,val);
        } else if (str=="query"){
            cout<<tr.query(l,r)<<endl;
        }
    }
}