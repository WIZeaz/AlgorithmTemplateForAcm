// 二分图匹配 Hopcroft-Carp
// O(sqrt(n)*E)

#include<vector>
#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

inline int read() {
    int input=0,v=1;
    char c=getchar();
    while((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-')v=-1,c=getchar();
    while(c>='0'&&c<='9')input=input*10+c-'0',c=getchar();
    return v*input;
}

const int N=50010;
const int inf=0x3f3f3f3f;

vector<int>w[N];
int n,m,dis;
int dx[N],dy[N];// 记录增广路的距离
int mx[N],my[N];// 左右两集合匹配的点的编号
bool used[N];

inline bool bfs() {
    queue<int>q;
    dis=inf;
    memset(dx,-1,sizeof dx);
    memset(dy,-1,sizeof dy);
    for(int i=1; i<=n; i++)
        if(mx[i]==-1) {
            q.push(i);
            dx[i]=0;
        }
    while(!q.empty()) {
        int x=q.front();
        q.pop();
        if(dx[x]>dis)break;
        for(int i=0; i<w[x].size(); i++) {
            int v=w[x][i];
            if(dy[v]==-1) {
                dy[v]=dx[x]+1;////?
                if(my[v]==-1)dis=dy[v];
                else {
                    dx[my[v]]=dy[v]+1;
                    q.push(my[v]);
                }
            }
        }
    }
    return dis!=inf;
}

inline bool dfs(int x) {
    for(int i=0; i<w[x].size(); i++) {
        int v=w[x][i];
        if(!used[v]&&dy[v]==dx[x]+1) {
            used[v]=true;
            if(my[v]!=-1&&dy[v]==dis)continue;
            if(my[v]==-1||dfs(my[v])) {
                my[v]=x,mx[x]=v;
                return true;
            }
        }
    }
    return false;
}

inline int solve() {
    int ans=0;
    memset(mx,-1,sizeof mx);
    memset(my,-1,sizeof my);
    while(bfs()) {
        memset(used,false,sizeof used);
        for(int i=1; i<=n; i++)
            if(mx[i]==-1&&dfs(i))ans++;
    }
    return ans;
}

int main() {
    n=read(),m=read();
    int p=read();
    //for(int i=1; i<=n; i++)w[i].clear();
    for(int i=1; i<=p; i++) {
        int x=read(),y=read();
        w[x].push_back(y);
    }
    printf("%d\n",solve());
}
