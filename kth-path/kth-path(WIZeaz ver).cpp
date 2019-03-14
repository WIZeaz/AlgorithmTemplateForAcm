#include <iostream>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

//dijkstra
#define N 2000
#define INF 0x3f3f3f3f
struct PathNode{
    int to,val;
    PathNode(){}
    PathNode(int _to,int _val){
        to=_to; val=_val;
    }
    bool operator < (const PathNode& b) const{
        return val>b.val;
    }
};
vector<PathNode> list[N+1],list2[N+1];
int dis[N+1];
bool vis[N+1];
void dijkstra(int s)
{
    priority_queue<PathNode> v;
    memset(vis,false,sizeof(vis)); 
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    v.push(PathNode(s,0));
    while (!v.empty()){
        PathNode tmp=v.top();
        v.pop();
        if (vis[tmp.to]) continue;
        vis[tmp.to]=true;
        int len=list[tmp.to].size();
        for (int i=0;i<len;++i)
            if (!vis[list[tmp.to][i].to] && dis[tmp.to]+list[tmp.to][i].val<dis[list[tmp.to][i].to]){
                dis[list[tmp.to][i].to]=dis[tmp.to]+list[tmp.to][i].val;
                v.push(PathNode(list[tmp.to][i].to,dis[list[tmp.to][i].to]));
            }
    }
}
//dijkstra

//astar
struct SearchNode{
    int x,dis,totdis;
    SearchNode();
    SearchNode(int _x,int _dis,int _totdis):x(_x),dis(_dis),totdis(_totdis){}
    bool operator < (const SearchNode& b) const{
        return totdis>b.totdis;
    }
};
int cnt[N+1];
int kpath(int s,int t,int k){
    if (dis[s]==INF) return -1;
    memset(cnt,0,sizeof(cnt));
    if (s==t) ++k;

    priority_queue<SearchNode> que;
    que.push(SearchNode(s,0,dis[s]));

    while (!que.empty()){
        SearchNode tmp=que.top();
        que.pop();
        ++cnt[tmp.x];
        if (cnt[t]==k) return tmp.totdis;
        if (cnt[tmp.x]>k) continue;
        for (int i=0;i<list2[tmp.x].size();++i){
            int to=list2[tmp.x][i].to;
            que.push(SearchNode(to,tmp.dis+list2[tmp.x][i].val,tmp.dis+list2[tmp.x][i].val+dis[to]));
        }
    }
    return -1;
}
//astar
int main()
{
    int n,m,s,t,k;
    while (~scanf("%d%d",&n,&m)){
        for (int i=0;i<=n;++i){
            list[i].clear();
            list2[i].clear();
        }
        for (int i=0;i<m;++i){
                int a,b,x;
                scanf("%d%d%d",&a,&b,&x);
                list[b].push_back(PathNode(a,x));
                list2[a].push_back(PathNode(b,x));
        }
        scanf("%d%d%d",&s,&t,&k);
        dijkstra(t);
        printf("%d\n",kpath(s,t,k));
    }
     return 0;
}