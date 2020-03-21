#include <bits/stdc++.h>
using namespace std;
deque<int> edges[500001];
//Maximum of digits
#define MAXD 19
int f[500001][MAXD+1];
int depth[500001];
//when invoke you must assure x equal to father
void lca_init(int x,int father,int d){
    depth[x]=d;
    f[x][0]=father;
    for (int i=1;(1<<i)<=d;++i){
        f[x][i]=f[f[x][i-1]][i-1];
    }
    for (auto v:edges[x]){
        if (v==father) continue;
        lca_init(v,x,d+1);
    }
}
int getLCA(int u,int v){
    if (depth[u]>depth[v]) swap(u,v);
    int len=depth[v]-depth[u];
    for (int i=0;(1<<i)<=len;++i)
        if ((1<<i)&len) v=f[v][i];
    for (int i=MAXD;i>=0;--i)
        if (f[u][i]!=f[v][i]){u=f[u][i]; v=f[v][i];}
    if (u==v) return u;
    else return f[u][0];
}
int main()
{
    int n,m,root;
    scanf("%d%d%d",&n,&m,&root);
    for (int i=0;i<n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        edges[u].emplace_back(v);
        edges[v].emplace_back(u);
    }
    lca_init(root,root,0);
    while (m--){
        int u,v;
        scanf("%d%d",&u,&v);
        printf("%d\n",getLCA(u,v));
    }
}