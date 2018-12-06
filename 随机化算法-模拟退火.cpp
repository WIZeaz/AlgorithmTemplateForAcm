// poj2420 模拟退火
// 题意：找n个点的费马点（与其他点的距离之和最小）
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<cstring>
#include<queue>
#include<map>
using namespace std;
#define ll long long
#define ull unsigned long long
#define up(i,a,b) for(int i=(a);i<=(b);i++)
#define down(i,a,b) for(int i=(a);i>=(b);i--)
#define mem(x,y) memset(x,(y),sizeof x)
#define ff first
#define ss second
#define pa(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sc(a) scanf("%d",&a)
#define scl(a) scanf("%I64d",&a)
#define scs(a) scanf("%s",a)
#define pr(a,b) printf("%d%c",a,b)
#define prl(a,b) printf("%lld%c",a,b)
#define PQ priority_queue
#define ld long double

typedef pair<double,double>pdd;
typedef map<int,int> mii;

pdd a[10010];
ld pre,cur;
int dd[4][2]= {0,1,0,-1,1,0,-1,0};
int w[10010]= {0};

inline ld dis(pdd a,pdd b) {
	return sqrt((a.ff-b.ff)*(a.ff-b.ff)+(a.ss-b.ss)*(a.ss-b.ss));
}

inline ld cal(int n,pdd aa) {
	ld ans=0;
	up(i,1,n)ans+=dis(aa,a[i]);
	return ans;
}

inline void solve(int n) {
	double t=100,t_min=1e-14;
	const double delta=0.98;

	pre=cal(n,a[1]);// 初始状态的值
	pdd pp=a[1];// 初始状态的点

	// 当温度（波动范围）大于0（1e-14）时，继续退火
	while(t>t_min) {
		// 新的状态的值
		double x=pp.ff+(rand()*2-RAND_MAX)*t,y=pp.ss+(rand()*2-RAND_MAX)*t;
		// 新的状态的点
		ld cur=cal(n,pa(x,y));

		// 如果更优，则更新结果
		if(cur-pre<0)pre=cur,pp=pa(x,y);
		// 否则以一定的概率接受这个新的状态
		else if(exp((pre-cur)/t)*RAND_MAX>=rand())pre=cur,pp=pa(x,y);

		// 温度（波动范围）下降
		t*=delta;
	}

	printf("%.0Lf\n",pre);
}

int main() {
	int n;
	while(~scanf("%d",&n)) {
		for(int i=1; i<=n; i++)scanf("%lf%lf",&a[i].ff,&a[i].ss);
		solve(n);
	}
}
