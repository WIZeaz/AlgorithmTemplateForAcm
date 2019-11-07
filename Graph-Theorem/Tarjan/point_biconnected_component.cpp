#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#define ll long long
using namespace std;
const int N=1e4+5;
const int M=1e5+5;

struct edge{
	int to;bool flag;//割边标记 
	edge(int a=0,bool b=false){
		to=a;flag=b;
	} 
}; 
vector<edge>e[N];
vector<int>group[N+N];//点双连通分量集合 
bool iscut[N];//该点是否是割点 
int top[N],self[N];
int index=1;
int sta[N];
int stacnt=0;
int color=0;

int n,m;

void ini(){
	index=1;
	stacnt=0;
	color=0;
	for(int i=0;i<=n;++i){
		e[i].clear();
		self[i]=0;
		top[i]=0;
		iscut[i]=false;
	}
	for(int i=0;i<=n+n;++i){
		group[i].clear();
	}
}

void tarjan(int now,int from){
	self[now]=top[now]=index++;
	//孤立点(此点被考虑为一个分量，未认为它是割点)
	if(e[now].size()==0){
		color++;
		group[color].push_back(now);
		return;
	}
	sta[stacnt++]=now;
	bool first=false;
	for(int i=0;i<e[now].size();++i){
		edge temp=e[now][i]; 
		int to=temp.to;
		if(to==from&&!first){
			first=true;
			continue;
		}
		if(self[to]==0){
			tarjan(to,now);
			top[now]=min(top[now],top[to]);
			if(top[to]>=self[now]){//出现点双通
				if(from!=0||i!=0) iscut[now]=true;//判断割点
				if(top[to]>self[now]) e[now][i].flag=true;//出现割边(也即两点一线)
				//若两点一线不属于点双连通分量，stacnt--,continue 
				color++;
				int y;
				do{
					stacnt--;
					y=sta[stacnt];
					group[color].push_back(y);
				}while(to!=y);
				group[color].push_back(now);
			}
		}else top[now]=min(top[now],self[to]);
	}
}
int main(){
	/*for(int i=1;i<=n;++i){
		if(self[i]==0) tarjan(i,0);
	}*/
}
