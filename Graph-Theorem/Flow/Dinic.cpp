#include <bits/stdc++.h>
using namespace std;

struct Dinic{
    struct Edge{
        int u,v,c,f;
    };
    
    static const int _num_v=1000;

    vector<Edge> edges;
    vector<int> e[_num_v];
    bool vis[_num_v];
    int dist[_num_v];
    int cur[_num_v];
    int n,s,t;
    void init(int _n,int _s,int _t){
        n=_n; s=_s; t=_t;
        edges.clear();
        for (int i=1;i<=_n;++i) e[i].clear();
    }
    void addedge(int u,int v,int c){
        edges.push_back({u,v,c,0});
        edges.push_back({v,u,0,0});
        int num=edges.size();
        e[u].push_back(num-2);
        e[v].push_back(num-1);
    }

    bool bfs(){
        fill(dist+1,dist+1+n,n);
        fill(vis+1,vis+1+n,0);
        queue<int> que;
        que.push(s);
        vis[s]=true;
        dist[s]=0;
        while (!que.empty()){
            int u=que.front();
            que.pop();
            for (auto i:e[u]){
                Edge &e=edges[i];
                if (vis[e.v] || e.c==e.f) continue;
                dist[e.v]=dist[u]+1;
                vis[e.v]=true;
                que.push(e.v);
            }
        }
        return dist[t]<n;
    }
    
    int augment(int u,int f){
        if (u==t) return f;
        
        int rest=f;
        int len=e[u].size();
        //printf("augment(%d,%d) len=%d\n",u,f,len);
        for (int i=cur[u];i<len;++i){
            int &j=e[u][i];
            Edge &e=edges[j];
            if (dist[e.u]+1!=dist[e.v] || e.c==e.f) continue;
            cur[u]=i;
            int now_flow=augment(e.v,min(rest,e.c-e.f));
            rest-=now_flow;
            edges[j].f+=now_flow;
            edges[j^1].f-=now_flow;
            if (!rest) return f-rest;
        }
        return f-rest;
    }

    long long maxflow(){
        long long f=0;
        while (bfs()){
            fill(cur+1,cur+1+n,0);
            f+=augment(s,INT_MAX);
            //printf("f=%lld\n",f);
        }
        return f;
    }
};

Dinic flow;
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