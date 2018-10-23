// 稠密图中较优
// 例题 洛谷P3366 https://www.luogu.org/problemnew/show/P3366
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int M=300000;
const int N=10000;

int num=0,dis[N],head[N],vis[N],sum=0,cnt=0;
struct edge{
    int next,v,w;
    edge(){};
    edge(int a,int b,int c):next(a),v(b),w(c){};
}e[M*2+10];

// 放进优先队列中的结构，以边权升序排序
struct node{
    int a,b;
    node(){};
    node(int aa,int bb):a(aa),b(bb){};
    bool operator <(const node &x)const{
        return a>x.a;
    }
};

inline int read(){
    int input=0,v=1;
    char c=getchar();
    while((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-')v=-1,c=getchar();
    while(c>='0'&&c<='9')input=input*10+c-'0',c=getchar();
    return v*input;
}

inline void addedge(int a,int b,int c){
    e[++num]=edge(head[a],b,c);
    head[a]=num;
}

// 像dij+堆优化那样
inline void prim(int n){
    priority_queue<node>pq;
    dis[1]=0;/////
    
    pq.push(node(0,1));
    while(!pq.empty()&&cnt<n){
        node x=pq.top();
        pq.pop();
        if(vis[x.b])continue;
        vis[x.b]++;
        cnt++;
        sum+=x.a;
        for(int i=head[x.b];i!=-1;i=e[i].next)    
            if(dis[e[i].v]>e[i].w){
                dis[e[i].v]=e[i].w;
                pq.push(node(dis[e[i].v],e[i].v));
            }
        
    }
}
int main(){
    memset(head,-1,sizeof head);
    memset(dis,0x3f,sizeof dis);
    memset(vis,0,sizeof vis);
    num=sum=cnt=0;

    int n=read(),m=read();
    for(int i=1;i<=m;i++){
        int a=read(),b=read(),c=read();
        addedge(a,b,c);
        addedge(b,a,c);
    }

    prim(n);
    if(cnt==n)printf("%d\n",sum);// 最小生成树存在，并输出值
    else printf("orz\n");// 最小生成树不存在

    return 0;
}