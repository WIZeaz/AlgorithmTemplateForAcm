#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define NODENUM 200000
struct splayTree{
    int son[NODENUM][2],size[NODENUM],f[NODENUM],cnt[NODENUM];
    int key[NODENUM];
    int root;
    int num;
    splayTree(){num=root=0;}
    int get(int x){
        return (son[f[x]][0]==x)?0:1;
    }
    void clear(int x){
        size[x]=0; f[x]=0; son[x][0]=son[x][1]=0; cnt[x]=0; key[x]=0;
    }
    void clear(){
        root=0; num=0;
        memset(cnt,0,sizeof(cnt));
        memset(f,0,sizeof(f));
        memset(size,0,sizeof(size));
        memset(son,0,sizeof(son));
    }
    void pushUp(int x){
        size[x]=son[x][0][size]+son[x][1][size]+cnt[x];
    }
    void rotate(int x){
        int k=get(x);
        int y=f[x];
        int z=f[y];
        if (z) son[z][get(y)]=x;
        son[y][k]=son[x][k^1]; f[son[x][k^1]]=y;
        son[x][k^1]=y;
        f[x]=z;
        f[y]=x;
        pushUp(y); pushUp(x);
    }
    void splay(int x,int to){
        int tf=f[to];
        while (f[x]!=to && f[x]!=tf){
            if (get(x)==get(f[x])) rotate(f[x]);
            else rotate(x);
            rotate(x);
        }
        if (f[x]!=tf) rotate(x);
        if (f[x]==0) root=x;
    }
    void insert(int val){
        int x=root,last=root;
        int t=-1;
        while (x!=0){
            last=x;
            if (val<key[x]) {x=son[x][0]; t=0;}
            else if (val>key[x]) {x=son[x][1]; t=1;}
            else {++cnt[x]; ++size[x]; splay(x,root); return;}
        }
        ++num;
        cnt[num]=1; size[num]=1; key[num]=val; 
        f[num]=last; 
        if (t!=-1) son[last][t]=num;
        splay(num,root);
    }
    //find: query what is the rank that val in this tree, if val doesn't exist in it, return -1.
    int find(int val){ 
        int x=root;
        int rnk=1;
        while (x!=0){
            if (val<key[x]) x=son[x][0];
            else if (val>key[x]) {rnk+=size[son[x][0]]+cnt[x];  x=son[x][1]; }
            else {
                rnk+=size[son[x][0]];
                splay(x,root);
                return rnk;
            }
        }
        return rnk;
    }
    int findx(int k){
        int last=root;
        int x=root;
        int s=0;
        while (x!=0){
            last=x;
            if (size[son[x][0]]>=k) x=son[x][0];
            else if (size[son[x][0]]+cnt[x]>=k){ splay(x,root); return key[x];}
            else {k-=size[son[x][0]]+cnt[x]; x=son[x][1];}
        }
        return key[last];
    }
    
    int findnum(int val){
        int x=root;
        while (x!=0){
            if (val<key[x]) x=son[x][0];
            else if (val>key[x]) x=son[x][1];
            else {return x;}
        }
        return -1;
    }
    void del(int val){
        int x=findnum(val);
        if (x==-1) return;
        --cnt[x];
        splay(x,root);
        if (cnt[x]>0) return;

        if (son[x][0]==0){ root=son[x][1]; f[root]=0; clear(x); pushUp(root); return;}

        int now=son[x][0];
        while (son[now][1]!=0) {now=son[now][1];}
        splay(now,son[x][0]);
        if (son[x][1]){
            son[now][1]=son[x][1];
            f[son[x][1]]=now;
        }

        f[now]=0;
        root=now;
        clear(x);
        pushUp(root);
    }
    int pre(int val){
        insert(val);
        int ans=-1;
        int now=son[root][0];
        while (now!=0){ans=key[now]; now=son[now][1];}
        del(val);
        return ans;
    }
    void traverse(int now){
        if (now==0) return;
        traverse(son[now][0]);
        cout<<key[now]<<' ';
        traverse(son[now][1]);
    }
    int nxt(int val){
        insert(val);
        int ans=-1;
        int now=son[root][1];
        while (now!=0){ans=key[now]; now=son[now][0];}
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
        else if (op==3) printf("%d\n",tr.find(x));
        else if (op==4) printf("%d\n",tr.findx(x));
        else if (op==5) printf("%d\n",tr.pre(x));
        else printf("%d\n",tr.nxt(x));
    }
}