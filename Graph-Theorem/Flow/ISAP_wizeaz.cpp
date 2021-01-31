#include <bits/stdc++.h>
using namespace std;

struct ISAP{
    struct Edge{
        int u,v,c,f;
    };
    
    static const int _num_v=1000;

    vector<Edge> edges;
    vector<int> e[_num_v];
    bool vis[_num_v];
    int dist[_num_v];
    int num[_num_v];
    int cur[_num_v];
    int n,s,t;
    void init(int _n,int _s,int _t){
        n=_n; s=_s; t=_t;
        edges.clear();
        for (int i=1;i<=_n;++i) e[i].clear();
        fill(dist+1,dist+1+n,n);
        fill(num+1,num+1+n,0);
        fill(cur+1,cur+1+n,0);
        fill(vis+1,vis+1+n,0);
    }
    void addedge(int u,int v,int c){
        edges.push_back({u,v,c,0});
        edges.push_back({v,u,0,0});
        int num=edges.size();
        e[u].push_back(num-2);
        e[v].push_back(num-1);
    }

    void bfs(int s,int t){
        queue<int> que;
        que.push(t);
        vis[t]=true;
        dist[t]=0;
        num[0]++;
        while (!que.empty()){
            int u=que.front();
            que.pop();
            for (auto i:e[u]){
                Edge &e=edges[i^1];
                if (vis[e.u] || e.c==e.f) continue;
                dist[e.u]=dist[u]+1;
                num[dist[e.u]]++;
                vis[e.u]=true;
                que.push(e.u);
            }
        }
    }
    
    int augment(int u,int f){
        if (u==t) return f;
        
        int rest=f;
        int len=e[u].size();
        // printf("augment(%d,%d) len=%d\n",u,f,len);
        bool ok=false;
        for (int i=cur[u];i<len;++i){
            int &j=e[u][i];
            Edge &e=edges[j];
            if (dist[e.v]+1!=dist[e.u] || e.c==e.f) continue;
            cur[u]=i;
            int now_flow=augment(e.v,min(rest,e.c-e.f));
            rest-=now_flow;
            edges[j].f+=now_flow;
            edges[j^1].f-=now_flow;
            ok=true;
            if (!rest) return f-rest;
        }
        
        if (--num[dist[u]]==0) dist[s]=n;

        cur[u]=0;
        int d_min=n-1;
        for (auto i:e[u])
            if (edges[i].f<edges[i].c)d_min=min(d_min,dist[edges[i].v]);
        
        dist[u]=d_min+1;
        num[dist[u]]++;

        return f-rest;
    }

    long long maxflow(){
        bfs(s,t);
        long long f=0;
        while (dist[s]<n){
            f+=augment(s,INT_MAX);
            //printf("f=%lld\n",f);
        }
        return f;
    }
};

ISAP flow;
int main(){
    int n,m,s,t;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    flow.init(n,s,t);
    for (int i=0;i<m;++i){
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        flow.addedge(u,v,c);
    }
    printf("%lld",flow.maxflow());
}