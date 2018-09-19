//ACM-ICPC 2018 沈阳赛区网络预赛 D. Made In Heaven 第k短路 A_star*算法 启发式搜索
//从终点开始，反向找出所有点到终点的最短距离，以此作为启发的条件
//然后从起点开始类spfa且不加松弛地搜索（可以找出所有路径？），将此点到起点的距离和此点到终点的最短距离
//的和加入堆中，这样，最短的路径一定在前面（额。。。） 
//不可能有这样的情况，即次短的路径在堆中，而最短的路径不在堆中，或后入堆（？） 

//仅能找出第k短路的长度，还不能打印出具体路径 
#include<iostream>
#include<cstdio>
#include<memory.h>
#include<vector>
#include<queue>

using namespace std;
const int MAX=1e3+5;//最大点数 
const int INF=1e8;//不可能到达的大值 

int num_point,num_edge,start,end,k_th;//点数，边数，起点，终点，k 
long long t;
bool flag[MAX];//用于迪杰斯特拉中标记已找到最短距离的点 
int cnt;//记录终点出堆的次数 
long long dis_dij[MAX];//保存迪杰斯特拉得到的结果 

struct pair_edge{//存边的结构 
	int to;//目的点的标号 
	long long len;//到目的的距离； 
	pair_edge(int t=0,long long l=0):to(t),len(l) {}
};

struct pair_dij{//加入堆中的结构，此堆用于优化迪杰斯特拉 
	int point_index;//当前点的标号；
	long long dis;//到起始点的距离； 
	pair_dij(int a=0,long long b=0):point_index(a),dis(b) {} 
	friend bool operator < (pair_dij a,pair_dij b)
	{
		return a.dis>b.dis;//按距离从小到大排序 
	}
};

struct pair_astar{//Astar算法的堆中使用的结构 
	int point_index;
	long long dis;//到起始点的距离 
	pair_astar(int a=0,long long b=0):point_index(a),dis(b) {}
	friend bool operator < (pair_astar a,pair_astar b)
	{
		return (a.dis+dis_dij[a.point_index]>b.dis+dis_dij[b.point_index]);//到起点的dis+到终点的最短dis 从小到大 
	}
};

vector<pair_edge>edge[MAX];//Astar函数中使用 
vector<pair_edge>edge_opposite[MAX];//迪杰斯特拉中使用，方向与输入的边相反，即从终点到起点 

void dij()//堆优化的迪杰斯特拉（邻接表） 
{
	fill(dis_dij+1,dis_dij+num_point+1,INF);
	memset(flag,false,sizeof(flag));
	priority_queue<pair_dij>que;
	 
	dis_dij[end]=0;//从终点到起点 
	que.push(pair_dij(end,0));
	pair_dij qtop;
	
	while(!que.empty())
	{
		qtop=que.top(),que.pop();
		int index=qtop.point_index;
		int dis=qtop.dis;
		
		if(flag[index]) continue;
		flag[index]=true;
		
		int l=edge_opposite[index].size();
		for(int i=0;i<l;++i)
		{
			pair_edge tempedge=edge_opposite[index][i];
			int to=tempedge.to;
			long long len=tempedge.len;
			
			if(flag[to]) continue;
			if(dis_dij[to]>dis_dij[index]+len)
			{
				dis_dij[to]=dis_dij[index]+len;
				que.push(pair_dij(to,dis_dij[to]));
			}
		}
	}
}

bool astar()//astar算法主体 
{
	cnt=0;
	priority_queue<pair_astar>que;
	que.push(pair_astar(start,0));
	pair_astar qtop;
	
	while(!que.empty())
	{
		qtop=que.top(),que.pop();
		int index=qtop.point_index;
		long long dis=qtop.dis;
		
		if(index==end) ++cnt; 
		if(cnt==k_th)//终点第k次出堆，即第k短路 
		{
			return true;
		}
		
		int l=edge[index].size();
		for(int i=0;i<l;++i)
		{
			que.push(pair_astar(edge[index][i].to,qtop.dis+edge[index][i].len));//统统入堆 
		}
	}
	
	//无第k短路 
	return false; 
}

int main()
{
	while(~scanf("%d%d",&num_point,&num_edge))
	{
		//建图
		
		dij();//倒着迪杰斯特拉 
		//dis_dij[start]==INF,起点与终点是否有路径？ 
		astar();
	}
	return 0;
}
