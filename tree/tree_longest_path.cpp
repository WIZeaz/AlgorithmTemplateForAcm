#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
vector<int> rds[20001];
int furthest=0;
int furthest_u=0;
void dfs(int u,int f,int d){
    if (d>furthest){
        furthest_u=u;
        furthest=d;
    }
    for (auto v:rds[u]){
        if (v==f) continue;
        dfs(v,u,d+1);
    }
}
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0;i<n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        rds[u].push_back(v);
        rds[v].push_back(u);
    }
    dfs(1,0,0);
    dfs(furthest_u,0,0);
    printf("%d",furthest);
}