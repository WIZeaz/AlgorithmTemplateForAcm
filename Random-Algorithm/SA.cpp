// poj2420 模拟退火
// 题意：找n个点的费马点（与其他点的距离之和最小）
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

pair<double,double> a[10010];
long double pre,cur;
int dd[4][2]= {0,1,0,-1,1,0,-1,0};
int w[10010]= {0};

inline long double dis(pair<double,double> a,pair<double,double> b) {
	return sqrt((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}

inline long double cal(int n,pair<double,double> aa) {
	long double ans=0;
	for(int i=1;i<=n;i++)ans+=dis(aa,a[i]);
	return ans;
}

inline void solve(int n) {
	double t=100,t_min=1e-14;
	const double delta=0.98;

	pre=cal(n,a[1]);// 初始状态的值
	pair<double,double> pp=a[1];// 初始状态的点

	// 当温度（波动范围）大于0（1e-14）时，继续退火
	while(t>t_min) {
		// 新的状态的值
		double x=pp.first+(rand()*2-RAND_MAX)*t,y=pp.second+(rand()*2-RAND_MAX)*t;
		// 新的状态的点
		long double cur=cal(n,make_pair(x,y));

		// 如果更优，则更新结果
		if(cur-pre<0)pre=cur,pp=make_pair(x,y);
		// 否则以一定的概率接受这个新的状态
		else if(exp((pre-cur)/t)*RAND_MAX>=rand())pre=cur,pp=make_pair(x,y);

		// 温度（波动范围）下降
		t*=delta;
	}
	printf("%d\n",int(pre+0.5));
}

int main() {
	int n;
	while(~scanf("%d",&n)) {
		for(int i=1; i<=n; i++)scanf("%lf%lf",&a[i].first,&a[i].second);
		solve(n);
	}
}
