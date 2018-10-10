// 稀疏图中较优
// 例题 洛谷P3366 https://www.luogu.org/problemnew/show/P3366
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int M=300000;
const int N=10000;

int f[M],ans=0,tot=0;
struct edge{
    int next,v,w;
    edge(){};
    edge(int a,int b,int c):next(a),v(b),w(c){};
}e[M+10];

inline int read(){
    int input=0,v=1;
    char c=getchar();
    while((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-')v=-1,c=getchar();
    while(c>='0'&&c<='9')input=input*10+c-'0',c=getchar();
    return v*input;
}

inline int find(int x){
    if(f[x]==x)return x;
    return f[x]=find(f[x]);
}

bool cmp(edge a,edge b){
    return a.w<b.w;
}

inline void Kruakal(int n,int m){
    for(int i=1;i<=m;i++){
        int u=find(e[i].next);
        int v=find(e[i].v);
        if(u==v)continue;//判断在不在同一个并查集里面，在就下一个循环
        ans+=e[i].w;
        f[u]=v;
        tot++;
        if(tot==n-1)break;
    }
}

int main(){
    int n=read(),m=read();

    for(int i=1;i<=n;i++)f[i]=i;//
    ans=tot=0;// 初始化

    for(int i=1;i<=m;i++){
        e[i].next=read();
        e[i].v=read();
        e[i].w=read();
    }

    // 贪心思想，把所有边按边权排序
    sort(e+1,e+1+m,cmp);

    Kruakal(n,m);
    if(tot==n-1)printf("%d\n",ans);// 最小生成树存在，并输出值
    else printf("orz\n");// 最小生成树不存在

    return 0;
}