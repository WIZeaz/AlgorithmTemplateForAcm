#include <bits/stdc++.h>
using namespace std;
namespace Tarjan{
    vector<int> edges[200001];
    set<int> rds[200001];
    int dfn[200001];
    int low[200001];
    int color[200001];
    int timestamp;
    int tot=0;
    stack<int> st;
    void tarjan(int u,int f){
        dfn[u]=low[u]=++timestamp;
        st.push(u);
        for (auto v:edges[u]){
            if (!dfn[v]) tarjan(v,u);
            if (v!=f) low[u]=min(low[u],low[v]);
        }
        if (low[u]==dfn[u]){
            tot++;
            while (!st.empty() && st.top()!=u){
                color[st.top()]=tot;
                st.pop();
            }
            st.pop();
            color[u]=tot;
        }
    }
}
using namespace Tarjan;
int main(){
    int n,m,T;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d",&n,&m);
        for (int i=1;i<=n;++i) edges[i].clear();
        for (int i=0;i<m;++i){
            int u,v;
            scanf("%d%d",&u,&v);
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        memset(dfn,0,sizeof(dfn));
        timestamp=0;
        tot=0;
        for (int i=1;i<=n;++i)
            if (!dfn[i]) tarjan(i,0);
        //build new graph
        for (int i=1;i<=n;++i) rds[i].clear();
        for (int u=1;u<=n;++u){
            for (auto v:edges[u]){
                if (color[u]!=color[v]){
                    rds[color[u]].insert(color[v]);
                }
            }
        }
    }
    return 0;
}