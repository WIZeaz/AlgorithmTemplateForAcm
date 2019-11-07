#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#define ll long long
using namespace std;
const int N=5e3+5;
const int M=N+N;

struct edge{
	int to;bool flag;//割边标记 
	edge(int a=0,bool b=false){
		to=a;flag=b;
	}
};
vector<edge>e[N];
int top[N],self[N];
int index=1;
int sta[N];
int stacnt=0;
int colorval[N];//点的所在边双连通分量编号(from 1) 
int color=0;

void tarjan(int now,int from){
	self[now]=top[now]=index++;
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
			if(top[to]>self[now]){
				e[now][i].flag=true;//割边 
			}
		}else top[now]=min(top[now],self[to]);
	}
	if(top[now]==self[now]){
		color++;//染色 
		do{
			stacnt--;
			colorval[sta[stacnt]]=color;
		}while(stacnt>0&&sta[stacnt]!=now);
	}
}

int n,m;
void ini(){
	index=1;
	stacnt=0;
	color=0;
	for(int i=0;i<=n;++i){
		e[i].clear();
		self[i]=0;
		top[i]=0;
	}
}

int main(){

	/*for(int i=1;i<=n;++i){
		if(self[i]==0) tarjan(i,0);
	}*/
	
}
