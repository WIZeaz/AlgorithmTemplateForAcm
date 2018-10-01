//POJ-3259 spfa bfs 判负权回路 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define ll long long
using namespace std;
const int MAX=5e2+5;//点数最大值 
const int INF=1e9;

struct pair_edge{
	int to,len;
	pair_edge(int a=0,int b=0):to(a),len(b) {}
};

vector<pair_edge>edge[MAX];
int t;//test cases
int num_point,num_positive_edge,num_negative_edge;//点数，正边数，负边数（视情况而定） 
int cnt[MAX];//记录各点被入队的次数 
int dis[MAX];//到起点的距离
 
bool spfa()
{
	queue<int>que;
	dis[1]=0;
	cnt[1]++;//被入队 
	que.push(1);
	
	while(!que.empty())
	{
		int from=que.front(); 
		que.pop();
		
		int l=edge[from].size();
		for(int i=0;i<l;++i)
		{
			pair_edge temp=edge[from][i];
			if(dis[temp.to]>dis[from]+temp.len)
			{
				dis[temp.to]=dis[from]+temp.len;
				que.push(temp.to);
				cnt[temp.to]++;//被入队 
				if(cnt[temp.to]>=num_point) return true;//若被入队超过n次，说明有负权回路
			}
		}
	}
	//无负权回路 
	return false;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&num_point,&num_positive_edge,&num_negative_edge);
		
		//初始化
		for(int i=1;i<=num_point;++i)
		{
			dis[i]=INF;
			edge[i].clear();
			cnt[i]=0;
		}
		
		int start,end,len;
		for(int i=0;i<num_positive_edge;++i)
		{
			scanf("%d%d%d",&start,&end,&len);
			//此题的正边默认为双向 
			edge[start].push_back(pair_edge(end,len));
			edge[end].push_back(pair_edge(start,len));
		}
		for(int i=0;i<num_negative_edge;++i)
		{
			scanf("%d%d%d",&start,&end,&len);
			//此题的负边默认为单向边 
			edge[start].push_back(pair_edge(end,-len));
		}
		
		if(spfa()) printf("YES\n");
		else printf("NO\n");
	}
}
