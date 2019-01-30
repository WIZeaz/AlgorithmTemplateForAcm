#include <iostream>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

//dijkstra
#define N 2000
#define INF 0x7f7f7f7f
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
vector<PathNode> list[N+1];
int dis[N+1];
priority_queue<PathNode> v;
bool vis[N+1];
void dijkstra(int s)
{
    memset(vis,false,sizeof(vis)); 
    memset(dis,127,sizeof(dis));
    dis[s]=0;
    v=priority_queue<PathNode>();
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

int main()
{
    int n,m,s,t;
    while (~scanf("%d%d",&n,&m)){
        for (int i=0;i<n;++i) list[i].clear();
        for (int i=0;i<m;++i){
            int a,b,x;
            scanf("%d%d%d",&a,&b,&x);
            list[a].push_back(PathNode(b,x));
            list[b].push_back(PathNode(a,x));
        }
        scanf("%d%d",&s,&t);
        dijkstra(s);
        if (dis[t]==INF) printf("-1\n");
        else printf("%d\n",dis[t]);
    } 
    return 0;
}
