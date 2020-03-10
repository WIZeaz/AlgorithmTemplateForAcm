#include <bits/stdc++.h>
using namespace std;
vector<int> edges[20001];
set<int> rds[20001];
int dfn[20001];
int low[20001];
int color[20001];
int timestamp;
int tot=0;
int val[20001];
int totval[20001],dp[20001];
bool vis[20001];
stack<int> st;
void tarjan(int u,int f){
    dfn[u]=low[u]=++timestamp;
    st.push(u);
    for (auto v:edges[u]){
        if (!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
        } else if (!color[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if (low[u]==dfn[u]){
        tot++;
        while (!st.empty() && st.top()!=u){
            color[st.top()]=tot;
            totval[tot]+=val[st.top()];
            st.pop();
        }
        st.pop();
        color[u]=tot;
        totval[tot]+=val[u];
    }
}
void dfs(int u){
    vis[u]=true;
    dp[u]=totval[u];
    for (auto v:rds[u]){
        if (!vis[v]) dfs(v);
        dp[u]=max(dp[u],dp[v]+totval[u]);
    }
}
int main(){
    int n,m,T;

    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i) scanf("%d",&val[i]);
    for (int i=1;i<=n;++i) edges[i].clear();
    for (int i=0;i<m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        edges[u].push_back(v);
    }
    memset(dfn,0,sizeof(dfn));
    timestamp=0;
    tot=0;
    for (int i=1;i<=n;++i)
        if (!dfn[i]) tarjan(i,0);
    //build new graph
    for (int i=1;i<=n;++i) rds[i].clear();
    //invert edge graph (for toposort & dp)
    for (int u=1;u<=n;++u){
        for (auto v:edges[u]){
            if (color[u]!=color[v]){
                rds[color[v]].insert(color[u]);
            }
        }
    }
    for (int i=1;i<= tot;++i)
        if (!vis[i]){
            dfs(i);
        }
    int ans=0;
    for (int i=1;i<=tot;++i) ans=max(ans,dp[i]);
    printf("%d",ans);
    return 0;
}