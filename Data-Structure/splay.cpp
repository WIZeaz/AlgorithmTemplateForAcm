#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define nodeMaxNum 200000
struct splayTree{
    int son[nodeMaxNum][2],size[nodeMaxNum],f[nodeMaxNum],cnt[nodeMaxNum];
    int key[nodeMaxNum];
    int root;
    int num=0;
    int get(int x){
        return (son[f[x]][0]==x)?0:1;
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
    //TODO: fix rotate and splay function
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
            else {++cnt[x]; ++size[x]; splay(x,root); break;}
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
            if (son[x][0][size]<k) {x=son[x][1]; k-=son[x][0][size];}
            else x=son[x][0];
        }
        return key[last];
    }
    
    int findnum(int val){
        int x=root;
        int rnk=1;
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
        if (cnt[x]>0) return;

        splay(x,root);

        if (son[x][0]==0){ root=son[x][1]; pushUp(root); return;}

        int now=son[x][0];
        while (son[now][1]!=0) {now=son[now][1];}
        splay(now,son[x][0]);
        son[now][1]=son[x][1];
        if (son[x][1]) f[son[x][1]]=now;

        root=now;
        pushUp(root);
        /*if (son[x][k][son][k^1]==0){
            root=son[x][k]; f[son[x][k]]=0;
            son[root][k^1]=son[x][k^1];
            f[son[x][k^1]]=root;
        } else {
            int x=son[x][k];
            while (son[x][k^1]!=0) {x=son[x][k^1];}
            son[f[x]][get(x)]=0;
            root=x; f[x]=0;
            son[x][0]=son[x][0]; son[x][1]=son[x][1];
        }*/
    }
    int pre(int val){
        insert(val);
        int ans=-1;
        if (son[root][0]!=0) ans=key[son[root][0]];
        del(val);
        return ans;
    }
    int nxt(int val){
        insert(val);
        int ans=-1;
        if (son[root][1]!=0) ans=key[son[root][1]];
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