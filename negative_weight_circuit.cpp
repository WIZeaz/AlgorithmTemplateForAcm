//POJ-3259 spfa bfs �и�Ȩ��· 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define ll long long
using namespace std;
const int MAX=5e2+5;//�������ֵ 
const int INF=1e9;

struct pair_edge{
	int to,len;
	pair_edge(int a=0,int b=0):to(a),len(b) {}
};

vector<pair_edge>edge[MAX];
int t;//test cases
int num_point,num_positive_edge,num_negative_edge;//��������������������������������� 
int cnt[MAX];//��¼���㱻��ӵĴ��� 
int dis[MAX];//�����ľ���
 
bool spfa()
{
	queue<int>que;
	dis[1]=0;
	cnt[1]++;//����� 
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
				cnt[temp.to]++;//����� 
				if(cnt[temp.to]>=num_point) return true;//������ӳ���n�Σ�˵���и�Ȩ��·
			}
		}
	}
	//�޸�Ȩ��· 
	return false;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&num_point,&num_positive_edge,&num_negative_edge);
		
		//��ʼ��
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
			//���������Ĭ��Ϊ˫�� 
			edge[start].push_back(pair_edge(end,len));
			edge[end].push_back(pair_edge(start,len));
		}
		for(int i=0;i<num_negative_edge;++i)
		{
			scanf("%d%d%d",&start,&end,&len);
			//����ĸ���Ĭ��Ϊ����� 
			edge[start].push_back(pair_edge(end,-len));
		}
		
		if(spfa()) printf("YES\n");
		else printf("NO\n");
	}
}
