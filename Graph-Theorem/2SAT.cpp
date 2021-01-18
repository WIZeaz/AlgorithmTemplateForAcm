#include <bits/stdc++.h>
using namespace std;
vector<int> edges[3000000];
namespace Tarjan{
    const int N=3000000;
    int dfn[N];
    int low[N];
    int color[N];
    int timestamp;
    int scc=0;
    stack<int> st;
    void init(int n){
        fill(dfn+1,dfn+1+n,0);
        fill(color+1,color+1+n,0);
        timestamp=0;
        scc=0;
    }
    void tarjan(int u){
        dfn[u]=low[u]=++timestamp;
        st.push(u);
        for (auto v:edges[u]){
            if (!dfn[v]) tarjan(v);
            if (!color[v]) low[u]=min(low[u],low[v]);
        }
        if (low[u]==dfn[u]){
            scc++;
            while (!st.empty() && st.top()!=u){
                color[st.top()]=scc;
                st.pop();
            }
            st.pop();
            color[u]=scc;
        }
    }
}
namespace TwoSat{
    void TwoSat(int n){
        Tarjan::init(2*n);
        for (int i=1;i<=2*n;++i)
            if (!Tarjan::dfn[i]) Tarjan::tarjan(i);
        for (int i=1;i<=n;i++)
            if (Tarjan::color[i]==Tarjan::color[n+i]) {printf("IMPOSSIBLE\n"); return;}
        
        printf("POSSIBLE\n");
        for (int i=1;i<=n;++i)
            if (Tarjan::color[i] < Tarjan::color[n+i]) printf("1 ");
            else printf("0 ");
        printf("\n");
    }
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=0;i<m;++i){
        int x,a,y,b;
        scanf("%d%d%d%d",&x,&a,&y,&b);
        // -x -> y   -y->x
        edges[a*n+x].push_back((b^1)*n+y);
        edges[b*n+y].push_back((a^1)*n+x);
    }
    TwoSat::TwoSat(n);

}