#include<cstdio>
#include<cmath>
#include<iostream>
#include<queue>
#include<cstring>
#define ll long long
#define unll unsigned long long
const int N=2e2+5;
const int M=1e3+5;//点数 
const ll MOD=1e9+7;
const int INF=1e9+7;//一个上限 
const double Exp=1e-8;
const double PI=acos(-1);
using namespace std;
//边的结构定义 
struct Pair{
	int to,flow,next;
};
Pair e[M*M*2];//边结构数组 
int cnt;//实际使用的边的数量
int head[M];
int cur[M];//当前弧优化所用 
int s,t;//源点汇点 
int dis[M];//记录点的分层信息
int discnt[M];//记录同层的点个数 

//与HDU4292有关的数据 
int f,d,n;
int fcnt[N],dcnt[N];
char ch[N];

//初始化 
void ini(){
	memset(head,-1,sizeof(head));
	cnt=0;	
	
	s=0,t=f+d+n+n+1;
}
//添加一条正向边，同时添加对应反向边
void add(int from,int to,int flow){
	e[cnt].to=to;e[cnt].flow=flow;e[cnt].next=head[from];
	head[from]=cnt++;
	e[cnt].to=from;e[cnt].flow=0;e[cnt].next=head[to];
	head[to]=cnt++;
}
//从汇点到源点构建初始分层图信息 
void bfs(){
	memset(dis,-1,sizeof(dis));
	memset(discnt,0,sizeof(discnt));
	dis[t]=0;
	queue<int>que;que.push(t);
	while(!que.empty()){
		int now=que.front();que.pop();
		for(int i=head[now];i!=-1;i=e[i].next){
			int to=e[i].to;
			if(dis[to]!=-1) continue;
			dis[to]=dis[now]+1;que.push(to);
			discnt[dis[to]]++;
		}
	}
}
//多路增广，u为当前点，limit为从汇点到达u的路径上的容量最小值 
int dfs(int u,int limit){
	if(u==t) return limit;
	int flow=0;//记录u点开始各方向的流量和 
	for(int &i=cur[u];i!=-1;i=e[i].next){
		int to=e[i].to;
		if(e[i].flow>0&&dis[to]==dis[u]-1){
			int res=dfs(to,min(limit,e[i].flow));
			if(res==0) continue;
			e[i].flow-=res;e[i^1].flow+=res;
			flow+=res;limit-=res;
			if(limit==0) return flow;//流量瓶颈在u点之前的路径上 
		}
	}
	//u点各方向的路径已走完，增加u点层数 
	discnt[dis[u]]--;
	if(discnt[dis[u]]==0) dis[s]=t+1;//出现层数间隔，算法结束 
	dis[u]++;
	discnt[dis[u]]++;
	return flow;
}
//ISAP 
void isap(){
	int ans=0;
	bfs();
	while(dis[s]<=t){
		for(int i=s;i<=t;++i) cur[i]=head[i];//当前弧优化 
		ans+=dfs(s,INF);
	}
	printf("%d\n",ans);
}
int main(){
	while(~scanf("%d%d%d",&n,&f,&d)){
		
		ini();
		
/*		HDU4292
		for(int i=1;i<=f;++i) scanf("%d",&fcnt[i]);
		for(int i=1;i<=d;++i) scanf("%d",&dcnt[i]);
		for(int i=1;i<=f;++i){
			add(s,i,fcnt[i]);
		}
		for(int i=f+1;i<=f+d;++i){
			add(i,t,dcnt[i-f]);
		}
		int total=f+d;
		for(int i=1;i<=n;++i){
			scanf("%s",ch+1);
			for(int j=1;j<=f;++j){
				if(ch[j]=='Y'){
					add(j,total+i,1);
				}
			}
			add(total+i,total+i+n,1);
		}
		for(int i=1;i<=n;++i){
			scanf("%s",ch+1);
			for(int j=1;j<=d;++j){
				if(ch[j]=='Y'){
					add(total+n+i,f+j,1);
				}
			}
		}
*/
		isap();
	}
}