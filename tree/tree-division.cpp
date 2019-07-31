#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
struct edge{
    int v,next;
} rds[1000001];
int num=0;
int head[500001];
void addedge(int u,int v){
    rds[num].v=v;
    rds[num].next=head[u];
    head[u]=num;
    ++num;
}
struct node{
    int top,f,size,id,hson,dep;
} trnds[500001];
int dfn[500001];
int cnt=0;
void dfs1(int x,int f,int d){
    trnds[x].f=f; trnds[x].size=1; trnds[x].hson=0; trnds[x].dep=d;
    for (int i=head[x];i!=0;i=rds[i].next)
        if (rds[i].v!=f){
            dfs1(rds[i].v,x,d+1);
            trnds[x].size+=trnds[rds[i].v].size;
            if (trnds[rds[i].v].size>trnds[trnds[x].hson].size) trnds[x].hson=rds[i].v;
        }
}
void dfs2(int x,int top){
    dfn[++cnt]=x;
    trnds[x].id=cnt;
    trnds[x].top=top;
    if (trnds[x].hson!=0) dfs2(trnds[x].hson,top);
    for (int i=head[x];i!=0;i=rds[i].next)
        if (rds[i].v!=trnds[x].f && rds[i].v!=trnds[x].hson){
            dfs2(rds[i].v,rds[i].v);
        }
}
int getLCA(int u,int v){
    while (trnds[u].top!=trnds[v].top){
        if (trnds[trnds[u].top].dep>trnds[trnds[v].top].dep) u=trnds[trnds[u].top].f;
        else v=trnds[trnds[v].top].f;
    }
    if (trnds[u].dep<trnds[v].dep) return u;
    return v;
}
int main()
{
    int n,u,v;
    int m,s;
    scanf("%d%d%d",&n,&m,&s);
    memset(head,0,sizeof(head));
    num=1;
    for (int i=0;i<n-1;++i){
        scanf("%d%d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(s,s,0);
    dfs2(s,s);
    for (int i=0;i<m;++i){
        scanf("%d%d",&u,&v);
        printf("%d\n",getLCA(u,v));
    }
}