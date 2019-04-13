#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
struct path{
    int v,next;
    path(int _v,int _next) {v=_v; next=_next;}
    path(){}
} rds[100001];
int num;
int list[1001];
void addedge(int u,int v){
    ++num;
    rds[num]=path(v,list[u]);
    list[u]=num;
}
void exclude(int u,int v){
    addedge(u,v^1);
    addedge(v,u^1);
}
int dfn[1001],low[1001],cnt;
bool inStack[1001];
stack<int> st;
int f[1001];
bool select[1001];
bool tarjan(int x){
    ++cnt;
    dfn[x]=cnt;
    low[x]=cnt;
    inStack[x]=true;
    st.push(x);
    bool del=false;
    for (int t=list[x];t!=0;t=rds[t].next){
        int v=rds[t].v;
        if (!dfn[v]){
            del=del || tarjan(v);
            low[x]=min(low[x],low[v]);
        } else if (inStack[v]) low[x]=min(low[x],low[v]);
    }
    if (select[x^1]) del=true;
    if (dfn[x]==low[x]){
        if (!del) select[x]=true;
        while (st.top()!=x){
            f[st.top()]=x;
            select[st.top()]=select[x];
            inStack[st.top()]=false;
            st.pop();
        }
        f[st.top()]=x;
        inStack[st.top()]=false;
        st.pop();
    }
    return del;
}
int main()
{
    int n,m;
    while (~scanf("%d%d",&n,&m)){
        if (n==0 && m==0) return 0;
        memset(list,0,sizeof(list));
        num=0;
        for (int i=0;i<m;++i){
            int u,v;
            char ch1[10],ch2[10];
            scanf("%d%s%d%s",&u,ch1,&v,ch2);
            u*=2; v*=2;
            if (ch1[0]=='h') u=u^1;
            if (ch2[0]=='h') v=v^1;
            exclude(u,v);
        }
        addedge(0,1);
        cnt=0;
        memset(dfn,0,sizeof(dfn));
        memset(inStack,0,sizeof(inStack));
        memset(select,false,sizeof(select));
        while (!st.empty()) st.pop();
        
        for (int i=0;i<2*n;++i) f[i]=i;
        for (int i=0;i<2*n;++i)
            if (!dfn[i]) tarjan(i);
        bool flag=true;
        for (int i=0;i<2*n;i+=2)
            if (f[i]==f[i^1]) {flag=false; break;}
        if (flag){
            for (int i=2;i<2*n;i+=2){
                if (select[i]) printf("%dh ",i/2);
                else printf("%dw ",i/2);
            }
            printf("\n");
        } else printf("bad luck\n");
    }
}