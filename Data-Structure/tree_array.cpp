#include <bits/stdc++.h>
using namespace std;
int lowbit(int x){return x&(-x);}
struct tree_array{
    int n,st;
    int a[200001];
    inline void setRange(int N) {
        n=N;
        st=1;
        while ((st<<1)<=n) st<<=1;
    }
    inline void clear() {memset(a,0,sizeof(a));}
    inline void add(int pos,int val){
        for (int i=pos;i<=n;i+=lowbit(i)) a[i]+=val;
    }
    inline int query(int pos){
        int rnt=0;
        for (int i=pos;i>0;i-=lowbit(i)) rnt+=a[i];
        return rnt;
    }
    inline int smallestK(int k){
        int ans=0;
        for (int i=st;i>0;i>>=1)
            if (ans+i<=n && a[ans+i]<k){
                ans+=i;
                k-=a[ans];
            }
        return ans+1;
    }
};
tree_array tr;
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    tr.clear();
    tr.setRange(n);
    for (int i=1;i<=n;++i){
        int t;
        scanf("%d",&t);
        tr.add(i,t);
    }
    for (int i=1;i<=m;++i){
        int x,y,t;
        scanf("%d%d%d",&t,&x,&y);
        if (t==1) tr.add(x,y);
        else {
            printf("%d\n",tr.query(y)-tr.query(x-1));
        }
    }
}