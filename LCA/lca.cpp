#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
struct edge{
    int v,next;
} rds[10001];
int num;
int head[10001];
void addedge(int u,int v){
    rds[num].v=v;
    rds[num].next=head[u];
    head[u]=num;
    ++num;
}
int f[10001][20];
int depth[10001];
int MaxL=19;
void init(int x,int father,int d){
    depth[x]=d;
    f[x][0]=father;
    for (int i=1;(1<<i)<=d;++i){
        f[x][i]=f[f[x][i-1]][i-1];
    }
    for (int v=head[x];v!=0;v=rds[v].next){
        init(rds[v].v,x,d+1);
    }
}
int getLCA(int u,int v){
    if (depth[u]>depth[v]){
        int t=u; u=v; v=t;
    }
    int len=depth[v]-depth[u];
    for (int i=0;(1<<i)<=len;++i)
        if ((1<<i)&len){
            v=f[v][i];
        }
    for (int i=MaxL;i>=0;--i)
        if (f[u][i]!=f[v][i]){u=f[u][i]; v=f[v][i];}
    if (u==v) return u;
    else return f[u][0];
}
int deg[10001];
int main()
{
    int T;
    scanf("%d",&T);
    while (T--){
        int n,u,v;
        scanf("%d",&n);
        memset(head,0,sizeof(head));
        memset(deg,0,sizeof(deg));
        memset(f,0,sizeof(f));
        num=1;
        for (int i=0;i<n-1;++i){
            scanf("%d%d",&u,&v);
            ++deg[v];
            addedge(u,v);
        }
        for (int i=1;i<=n;++i)
            if (deg[i]==0){init(i,i,0); break;}
        scanf("%d%d",&u,&v);
        printf("%d\n",getLCA(u,v));
    }
}