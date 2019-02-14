#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
struct node{
    int v,next;
    node(){}
} rds[300001];
int num;
int n;
int head[501];
int match[501];
int type[501],pre[501],f[501];
queue<int> que;
void addedge(int u,int v){
    rds[num].v=v;
    rds[num].next=head[u];
    head[u]=num;
    ++num;
}
int find(int x){
    if (x!=f[x]) f[x]=find(f[x]);
    return f[x];
}
void shrink(int u,int v,int l){
    while (find(u)!=l){
        pre[u]=v; v=match[u];
        if (type[v]==2){ type[v]=1; que.push(v);}
        f[u]=l; 
        f[v]=l;
        u=pre[v];
    }
}
int LCA(int u,int v){
    bool vis[1001];
    memset(vis,false,sizeof(vis));
    while (1){
        if (u){
            u=find(u);
            if (vis[u]) return u;
            vis[u]=true;
            u=pre[match[u]];
        }
        swap(u,v);
    }
}

bool bfs(int x){
    memset(type,0,sizeof(type));
    for (int i=1;i<=n;++i) f[i]=i;
    //memset(pre,0,sizeof(pre));
    que=queue<int>();
    que.push(x);
    type[x]=1;
    while (!que.empty()){
        x=que.front();
        que.pop();
        for (int i=head[x];i;i=rds[i].next){
            if (!type[rds[i].v]){
                pre[rds[i].v]=x; type[rds[i].v]=2;
                if (!match[rds[i].v]){
                    int now=rds[i].v;
                    while (now!=0){
                        int last=match[pre[now]];
                        match[now]=pre[now]; match[pre[now]]=now;
                        now=last;
                    }
                    return true;
                }
                type[match[rds[i].v]]=1;
                que.push(match[rds[i].v]);
            } else if (type[rds[i].v]==1 && find(x)!=find(rds[i].v)){
                int l=LCA(x,rds[i].v);
                shrink(x,rds[i].v,l);
                shrink(rds[i].v,x,l);
            }
        }
    }
    return false;
}
int solve(){
    memset(match,false,sizeof(match));
    
    int ans=0;
    for (int i=1;i<=n;++i)
        if (!match[i] && bfs(i)) {++ans;}
    
    return ans;
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    memset(head,0,sizeof(head));
    memset(match,0,sizeof(match));
    num=0;
    for (int i=0;i<m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    printf("%d\n",solve());
    for (int i=1;i<=n;++i) printf("%d ",match[i]);
}