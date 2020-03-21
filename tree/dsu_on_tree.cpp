//template from CF600E
#include <bits/stdc++.h>
using namespace std;
vector<int> edges[200001];
#define addedge(u,v) edges[u].push_back(v)
struct node{
    int color,size,hson,dep;
} nodes[500001];
void dfs(int x,int f,int d){
    nodes[x].size=1; nodes[x].hson=0; nodes[x].dep=d;
    for (auto v:edges[x]){
        if (v==f) continue;
        dfs(v,x,d+1);
        nodes[x].size+=nodes[v].size;
        if (nodes[v].size>nodes[nodes[x].hson].size) nodes[x].hson=v;
    }
}
int color[100001];
int Max=0;
long long sum=0;
long long ans[100001];
void countColor(int c){
    color[c]++;
    if (color[c]>Max){Max=color[c]; sum=0;}
    if (color[c]==Max) {sum+=c;}
}
void countSubtree(int x,int f){
    countColor(nodes[x].color);
    for (auto v:edges[x]){
        if (v==f) continue;
        countSubtree(v,x);
    }
}
void solve(int x,int f){
    for (auto v:edges[x]){
        if (v==f || v==nodes[x].hson) continue;
        solve(v,x);
        sum=0; memset(color,0,sizeof(color)); Max=0;
    }
    if (nodes[x].hson!=0) solve(nodes[x].hson,x);
    countColor(nodes[x].color);
    for (auto v:edges[x]){
        if (v==f || v==nodes[x].hson) continue;
        countSubtree(v,x);
    }
    ans[x]=sum;
}
int main(){
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;++i){
        scanf("%d",&nodes[i].color);
    }
    for (int i=0;i<n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,1,0);
    solve(1,1);
    for (int i=1;i<=n;++i) printf("%lld ",ans[i]);
}