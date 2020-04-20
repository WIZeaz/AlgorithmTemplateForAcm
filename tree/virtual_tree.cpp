#include <bits/stdc++.h>
using namespace std;


//Graph
struct edge{
    int v,next;
    edge(){}
    edge(int _v,int _next){v=_v; next=_next;}
};
void addedge(int u,int v,int w){
}
vector< pair<int,int> > edges[300001];
vector<int> new_edges[300001];


//LCA
//Maximum of digits
#define MAXD 19
int f[300001][MAXD+1];
int depth[300001];
int val[300001][MAXD+1];
//get DFN
int dfn[300001];
int timestamp=0;
//when invoke you must assure x equal to father
void lca_init(int x,int father,int d,int w){
    depth[x]=d;
    f[x][0]=father;
    val[x][0]=w;
    dfn[x]=++timestamp;
    for (int i=1;(1<<i)<=d;++i){
        f[x][i]=f[f[x][i-1]][i-1];
        val[x][i]=min(val[x][i-1],val[f[x][i-1]][i-1]);
    }
    for (auto t:edges[x]){
        int v=t.first;
        int w=t.second;
        if (v==father) continue;
        lca_init(v,x,d+1,w);
    }
}
int LCA(int u,int v){
    if (depth[u]>depth[v]) swap(u,v);
    int len=depth[v]-depth[u];
    for (int i=0;(1<<i)<=len;++i)
        if ((1<<i)&len) v=f[v][i];
    for (int i=MAXD;i>=0;--i)
        if (f[u][i]!=f[v][i]){u=f[u][i]; v=f[v][i];}
    if (u==v) return u;
    return f[u][0];
}
int getW(int u,int v){
    int len=depth[v]-depth[u];
    int rnt=INT_MAX;
    for (int i=0;(1<<i)<=len;++i)
        if ((1<<i)&len){
            rnt=min(rnt,val[v][i]);
            v=f[v][i];
        }
    return rnt;
}




bool c[300001];
namespace virtual_tree{
    int sta[300001];
    int top=0;
    bool cmp(int u,int v){
        return dfn[u]<dfn[v];
    }
    void build(vector<int>& cp,vector<int> edges[]){
        sort(cp.begin(),cp.end(),cmp);
        top=0;
        sta[top++]=1;
        edges[1].clear();
        c[1]=false;
        for (auto v:cp){
            int f=LCA(sta[top-1],v);
            if (top>1 && f!=sta[top-1]){
                while (top>1 && dfn[f]<dfn[sta[top-2]]){
                    edges[sta[top-2]].push_back(sta[top-1]);
                    --top;
                }
                if (top>1 && f==sta[top-2]){
                    edges[sta[top-2]].push_back(sta[top-1]);
                    --top;
                } else {
                    edges[f].clear();
                    c[f]=false;
                    edges[f].push_back(sta[top-1]);
                    --top;
                    sta[top++]=f;
                }
            }
            sta[top++]=v;
            edges[v].clear();
            c[v]=true;
        }
        while (top>1){
            edges[sta[top-2]].push_back(sta[top-1]);
            --top;
        }
    }
}
void traverse(int u){
    cout<<u<<": ";
    for (auto v:new_edges[u]){
        cout<<v<<" ";
    }
    cout<<endl;
    for (auto v:new_edges[u]){
        traverse(v);
    }
}
long long dp[300001];
void solve(int u){
    dp[u]=0;
    for (auto v:new_edges[u]){
        solve(v);
        if (c[v]) dp[u]+=getW(u,v);
        else dp[u]+=min((long long)getW(u,v),dp[v]);
    }
}
int main(){
    int n,m,v;
    scanf("%d",&n);
    for (int i=0;i<n-1;++i){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        edges[u].push_back(make_pair(v,w));
        edges[v].push_back(make_pair(u,w));
    }
    lca_init(1,1,0,0);
    scanf("%d",&m);
    vector<int> cp; //critical point
    while (m--){
        int k;
        scanf("%d",&k);
        cp.clear();
        for (int i=0;i<k;++i){
            int t;
            scanf("%d",&t);
            cp.push_back(t);
        }
        virtual_tree::build(cp,new_edges);
        //traverse(1);
        solve(1);
        printf("%lld\n",dp[1]);
    }
}