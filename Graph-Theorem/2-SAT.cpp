#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
#define NODEN 2000010
#define ROADM 2000010
struct path{
    int v,next;
    path(int _v,int _next) {v=_v; next=_next;}
    path(){}
} rds[ROADM];
int num;
int list[NODEN];
void addedge(int u,int v){
    ++num;
    rds[num]=path(v,list[u]);
    list[u]=num;
}
int dfn[ROADM],low[ROADM],cnt;
bool inStack[ROADM];
stack<int> st;
int color[ROADM];
int cnum=0;
void tarjan(int x){
    ++cnt;
    dfn[x]=cnt;
    low[x]=cnt;
    inStack[x]=true;
    st.push(x);
    for (int t=list[x];t!=0;t=rds[t].next){
        int v=rds[t].v;
        if (!dfn[v]){
            tarjan(v);
            low[x]=min(low[x],low[v]);
        } else if (inStack[v]) low[x]=min(low[x],low[v]);
    }
    if (dfn[x]==low[x]){
        while (st.top()!=x){
            color[st.top()]=cnum;
            inStack[st.top()]=false;
            st.pop();
        }
        color[st.top()]=cnum;
        inStack[st.top()]=false;
        st.pop();
        ++cnum;
    }
}
void solve(int n){
    memset(dfn,0,sizeof(dfn)); 
    memset(low,0,sizeof(low));
    memset(color,0,sizeof(color));
    cnum=0; cnt=0;
    for (int i=0;i<2*n;++i) 
        if (!dfn[i]) tarjan(i);
    for (int i=0;i<2*n;i+=2)
        if (color[i]==color[i|1]) {printf("IMPOSSIBLE\n"); return;}
    
    printf("POSSIBLE\n");
    for (int i=0;i<2*n;i+=2)
        if (color[i]<color[i|1]) printf("0 ");
        else printf("1 ");
    printf("\n");
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    num=0;
    memset(list,0,sizeof(list));
    for (int i=0;i<m;++i){
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        --a; --c;
        a<<=1; c<<=1;
        addedge(a|(1-b),c|d);
        addedge(c|(1-d),a|b);
    }
    solve(n);
}