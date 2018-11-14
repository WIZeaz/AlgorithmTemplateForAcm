// KM算法 二分图最佳匹配(最大权值)
// O(N*M)
// 若要求最小权值，则边权取反，最后结果也取反
// 邻接矩阵建图

#include<vector>
#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

inline int read() {
	int input=0,v=1;
	char c=getchar();
	while((c<'0'||c>'9')&&c!='-')c=getchar();
	if(c=='-')v=-1,c=getchar();
	while(c>='0'&&c<='9')input=input*10+c-'0',c=getchar();
	return v*input;
}

const int N=510;
const int inf=0x3f3f3f3f;

int n,m;
int link[N],lx[N],ly[N],slack[N],w[N][N];
// link:匹配  lx,ly:期望值  slack:松弛  w:存图
bool visx[N],visy[N];

inline bool dfs(int x) {
	visx[x]=true;
	for(int i=1; i<=m; i++) {
		if(visy[i])continue;

		int cmp=lx[x]+ly[i]-w[x][i];
		if(!cmp) {
			visy[i]=true;
			if(link[i]==-1||dfs(link[i])) {
				link[i]=x;
				return true;
			}
		} else if(slack[i]>cmp)slack[i]=cmp;
	}
	return false;
}

inline int km() {
	int ans=0;
	memset(link,-1,sizeof link);
	memset(ly,0,sizeof ly);
	for(int i=1; i<=n; i++) {
		lx[i]=-inf;
		for(int o=1; o<=m; o++)
			if(w[i][o]>lx[i])lx[i]=w[i][o];
	}
	for(int i=1; i<=n; i++) {
		for(int o=1; o<=m; o++)slack[o]=inf;
		while(1) {
			memset(visx,false,sizeof visx);
			memset(visy,false,sizeof visy);
			if(dfs(i))break;

			int d=inf;
			for(int o=1; o<=m; o++)
				if(!visy[o]&&d>slack[o])d=slack[o];
			for(int o=1; o<=n; o++)
				if(visx[o])lx[o]-=d;// 匹配过，期望值减少
			for(int o=1; o<=m; o++)
				if(visy[o])ly[o]+=d;// 匹配过，期望值增加
				else slack[o]-=d;
		}
	}

	for(int i=1; i<=m; i++)
		if(link[i]!=-1)ans+=w[link[i]][i];
	return ans;
}

int main() {
	int t=read();
	while(t--) {
		n=read(),m=read();
		memset(w,0x80,sizeof w);// 0x80 -> -128
		for(int i=1; i<=m; i++) {
			int x=read(),y=read(),z=read();
			w[x][y]=max(w[x][y],-z);
		}
		m=n;// 如果匹配的两个点集大小相等，那么要赋值m=n
		printf("%d\n",-km());// 求最小权匹配
	}
}
