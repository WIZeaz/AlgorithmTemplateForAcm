#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define NODENUM 200000
struct splayTree{
    struct node{
        int size,cnt,son[2],f;
        int key;
    } tr[NODENUM];
    int root,num;
    splayTree(){
        root=0;
        num=0;
    }
    void clear(){
        memset(tr,0,sizeof(tr));
        root=num=0;
    }
    void pushup(int x){
        tr[x].size=tr[tr[x].son[0]].size+tr[tr[x].son[1]].size+tr[x].cnt;
    }
    int get(int x){
        return (tr[tr[x].f].son[0]==x)?0:1;
    }
    void rotate(int x){
        int k=get(x);
        int y=tr[x].f;
        int z=tr[y].f;
        if (z) tr[z].son[get(y)]=x;
        tr[x].f=z;
        tr[y].f=x;
        tr[tr[x].son[k^1]].f=y;
        tr[y].son[k]=tr[x].son[k^1];
        tr[x].son[k^1]=y;
        pushup(y); pushup(x);
    }
    void splay(int x,int to){
        int tf=tr[to].f;
        while (tr[x].f!=tf && tr[x].f!=to){
            if (get(x)==get(tr[x].f)) rotate(tr[x].f);
            else rotate(x);
            rotate(x);
        }
        if (tr[x].f!=tf) rotate(x);
        if (tr[x].f==0) root=x;
    }
    void insert(int key){
        int now=root;
        int last=root;
        int t=-1;
        while (now!=0){
            last=now;
            if (key<tr[now].key) {now=tr[now].son[0]; t=0;}
            else if (key>tr[now].key) {now=tr[now].son[1]; t=1;}
            else {tr[now].cnt++; splay(now,root); return;}
        }
        ++num; tr[num].size=tr[num].cnt=1; tr[num].key=key; tr[num].f=last;
        if (t!=-1) tr[last].son[t]=num;
        
        splay(num,root);
    }
    void traverse(int x){
        if (x==0) return;
        traverse(tr[x].son[0]);
        cout<<tr[x].key<<' ';
        traverse(tr[x].son[1]);
    }
    bool isExist(int key){
        int now=root;
        while (now!=0){
            if (key<tr[now].key) now=tr[now].son[0];
            else if (key>tr[now].key) now=tr[now].son[1];
            else {splay(now,root); return true;}
        }
        return false;
    }
    void del(int key){
        if (!isExist(key)) return;
        tr[root].cnt--; tr[root].size--;
        if (tr[root].cnt>0) return;
        if (tr[root].son[0]==0) {root=tr[root].son[1]; tr[root].f=0; return;}
        
        //find rightmost son in left subtree, i.e. the greatest key one.
        int now=tr[root].son[0];
        while (tr[now].son[1]!=0) {now=tr[now].son[1];}
        
        if (tr[root].son[1]){
            tr[now].son[1]=tr[root].son[1];
            tr[tr[root].son[1]].f=now;
        }
        splay(now,tr[root].son[0]);
        tr[now].f=0;
        root=now;
    }
    int getRank(int key){
        int now=root;
        int rnk=1;
        while (now!=0){
            if (key<tr[now].key) now=tr[now].son[0];
            else if (key>tr[now].key){rnk+=tr[tr[now].son[0]].size+tr[now].cnt;  now=tr[now].son[1]; }
            else {
                rnk+=tr[tr[now].son[0]].size;
                splay(now,root);
                return rnk;
            }
        }
        return rnk;
    }
    int getKeyFromRank(int rnk){
        int now=root;
        int last=now;
        while (now!=0){
            if (tr[tr[now].son[0]].size>=rnk) now=tr[now].son[0];
            else if (tr[tr[now].son[0]].size+tr[now].cnt>=rnk){
                splay(now,root); return tr[now].key;
            } else {rnk-=tr[tr[now].son[0]].size+tr[now].cnt; now=tr[now].son[1];}
        }
        return tr[last].key;
    }
    int pre(int val){
        insert(val);
        int ans=-1;
        int now=tr[root].son[0];
        while (now!=0) {ans=tr[now].key; now=tr[now].son[1];}
        del(val);
        return ans;
    }
    int nxt(int val){
        insert(val);
        int ans=-1;
        int now=tr[root].son[1];
        while (now!=0) {ans=tr[now].key;now=tr[now].son[0];}
        del(val);
        return ans;
    }
};
splayTree tr;
int main()
{
    int n;
    scanf("%d",&n);
    while (n--){
        int op,x;
        scanf("%d%d",&op,&x);
        if (op==1) tr.insert(x);
        else if (op==2) tr.del(x);
        else if (op==3) printf("%d\n",tr.getRank(x));
        else if (op==4) printf("%d\n",tr.getKeyFromRank(x));
        else if (op==5) printf("%d\n",tr.pre(x));
        else printf("%d\n",tr.nxt(x));
    }
}