#include<bits/stdc++.h>
namespace lp{
	// 求min{ B_i * X }
	// 约束： A_ij * X_j >= C_i
	const int N=1010,M=10010;
	const double INF=1e18;
	const double eps=1e-8;
	int n,m;
	double a[M][N],b[M],c[N],v;

	void pivot(int l,int e){
		b[l]/=a[l][e];
		for(int j=1;j<=n;j++)if(j!=e)a[l][j]/=a[l][e];
		a[l][e]=1.0/a[l][e];
		for(int i=1;i<=m;i++)
			if(i!=l&&fabs(a[i][e])>0){
				b[i]-=a[i][e]*b[l];
				for(int j=1;j<=n;j++)
					if(j!=e)a[i][j]-=a[i][e]*a[l][j];
				a[i][e]*=-a[l][e];
			}
		v+=c[e]*b[l];
		for(int j=1;j<=n;j++)if(j!=e)c[j]-=c[e]*a[l][j];
		c[e]*=-a[l][e];
	}
	double simplex(){
		v=0;
		while(1){
			int e=-1,l=-1;
			for(int i=1;i<=n;i++)if(c[i]>eps){e=i;break;}
			if(e==-1)return v;
			double t=INF;
			for(int i=1;i<=m;i++)
				if(a[i][e]>eps&&t>b[i]/a[i][e]){
					t=b[i]/a[i][e];
					l=i;
				}
			if(l==-1)return INF;
			pivot(l,e);
		}
	}
	void read(){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%lf",&c[i]);
		for(int i=1;i<=m;i++){
			int l,r;
			scanf("%d%d%lf",&l,&r,&b[i]);
			for(int j=l;j<=r;j++)a[i][j]=1;
		}
	}
};