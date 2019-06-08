#include<cstdio>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<vector>
#include<deque>
#include<string>
#include<cstring>
#define ll long long
#define unll unsigned long long
const int N=1e5+5e2+50;//最大点数
const int M=1e5+5e3+50;//最大边数
const ll MOD=1e9+7;
const int INF=0x3f3f3f3f;//INF
const double Exp=1e-8;
const double PI=acos(-1);
using namespace std;

struct edge{
	int to,flow,cost,next;
};
edge e[M];
int ecnt;//记录所用边的数量
int head[N];//用链表的形式保存边
int dis[N];//记录点到起点或终点的距离
int pre[N],predge[N];//spfa过程中记录前驱点和前驱边
bool vis[N];
int s,t;//起点终点
int ans=0;//最终费用

void ini(){
	ecnt=0;
	memset(head,-1,sizeof(head));
	ans=0;
}
//建单向边
void add(int from,int to,int flow,int cost){
	e[ecnt].to=to;e[ecnt].flow=flow;e[ecnt].cost=cost;e[ecnt].next=head[from];
	head[from]=ecnt++;
	e[ecnt].to=from;e[ecnt].flow=0;e[ecnt].cost=-cost;e[ecnt].next=head[to];
	head[to]=ecnt++;
}
//单路增广，从终点到起点，或从起点到终点
bool spfa(){
	memset(vis,false,sizeof(vis));
	for(int i=0;i<=N;++i) dis[i]=INF;
	deque<int>que;que.push_back(t);vis[t]=true;
	dis[t]=0;
	while(!que.empty()){
		int now=que.front();que.pop_front();
		vis[now]=false;
		for(int i=head[now];i!=-1;i=e[i].next){
			int to=e[i].to;
			if(e[i^1].flow>0&&dis[to]>dis[now]-e[i].cost){
				pre[to]=now;predge[to]=i^1;
				dis[to]=dis[now]-e[i].cost;
				if(!vis[to]){
					vis[to]=true;
					//SLF优化
					if(que.size()>0&&dis[que.front()]>dis[to]) que.push_front(to);
					else que.push_back(to);
				}
			}
		}
	}
	return dis[s]<INF;
}
//在找到的增广路上更新
void update(){
	int now=s;int small=INF;
	//找到流量small
	do{
		if(small>e[predge[now]].flow) small=e[predge[now]].flow;
		now=pre[now];
	}while(now!=t);
	now=s;
	//更新边权和答案
	do{
		e[predge[now]].flow-=small;e[predge[now]^1].flow+=small;
		ans+=e[predge[now]].cost*small;
		now=pre[now];
	}while(now!=t);
}
//MCMF
void mcmf(){
	while(spfa()){
		//if(dis[s]>0) break;
		//上句注释适用于GDCPC2019A题，即求（将费用转为负值之后的）最小费用，但不需要最大流
		//即dis[s]>0时，累积费用将从减小趋势转为增加趋势，也即dis[s]是递增的。
		update();
	}
	//ans=-ans;
	//也只适用于GDCPC2019A题
	printf("%d\n",ans);
}
//建图
void build(){

}
int main(){
	//input
	build();
	mcmf();
}
