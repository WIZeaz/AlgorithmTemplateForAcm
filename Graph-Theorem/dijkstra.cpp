#include <bits/stdc++.h>
using namespace std;
namespace Graph{
    struct edge{
        int v,w;
        bool operator<(const edge& b) const{
            return w>b.w;
        }
    };
    vector<edge> edges[200001];
    int dist[200001];
    bool vis[200001];
    const int INF=0x3f3f3f3f;
    void dijkstra(int s){
        memset(dist,0x3f,sizeof(dist));
        memset(vis,0,sizeof(vis));
        priority_queue<edge> que;
        que.push({s,0});
        dist[s]=0;
        while (!que.empty()){
            auto tmp=que.top();
            que.pop();
            if (vis[tmp.v]) continue;
            int &u=tmp.v;
            int &d=tmp.w;
            vis[u]=true;
            for (auto it:edges[u]){
                int &v=it.v;
                int &w=it.w;
                if (!vis[v] && d+w<dist[v]){
                    dist[v]=d+w;
                    que.push({v,d+w});
                }
            }
        }
    }
}
using namespace Graph;
int main()
{
    int n,m,s;
    scanf("%d%d%d",&n,&m,&s);
    for (int i=0;i<m;++i){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        edges[u].push_back({v,w});
    }
    dijkstra(s);
    for (int i=1;i<=n;++i) printf("%d ",dist[i]);
}
