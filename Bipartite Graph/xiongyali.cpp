// 二分图最大匹配
// 邻接矩阵 O(VE)
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
inline int read() {
    int input=0,v=1;
    char c=getchar();
    while((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-')v=-1,c=getchar();
    while(c>='0'&&c<='9')input=input*10+c-'0',c=getchar();
    return v*input;
}

const int N=510;
int link[N],n,m;
bool used[N];
vector<int>w[N];

inline bool dfs(int x) {
    for(int i=0; i<w[x].size(); i++)
        if(!used[w[x][i]]) {
            used[w[x][i]]=true;
            if(link[w[x][i]]==-1||dfs(link[w[x][i]])) {
                link[w[x][i]]=x;
                return true;
            }
        }
    return false;
}

inline int solve() {
    memset(link,-1,sizeof link);
    int ans=0;
    for(int i=1; i<=n; i++) {
        memset(used,false,sizeof used);
        if(dfs(i))ans++;
    }
    return ans;
}

int main() {
    int t=read();
    while(t--) {
        n=read(),m=read();
        for(int i=1;i<=n;i++)w[i].clear();
        for(int i=1; i<=n; i++) {
            int x=read();
            for(int o=1; o<=x; o++) {
                int y=read();
                w[i].push_back(y);
            }
        }
        if(solve()==n)printf("YES\n");
        else printf("NO\n");
        for(int i=1;i<=n;i++)
            printf("%d ",link[i]);
    }
}

