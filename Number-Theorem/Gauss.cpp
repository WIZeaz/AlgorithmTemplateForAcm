#include<bits/stdc++.h>
// 高斯消元，从网上copy的板子
// 用来找规律
#define N 205
using namespace std;
const double eps=1e-8;
double a[N][N],del;
bool gauss(int n) {
	for(int i=1; i<=n; i++) {
		int k=i;
		for(int j=i+1; j<=n; j++)
			if(fabs(a[j][i])>fabs(a[k][i]))k=j;
		if(fabs(del=a[k][i])<eps) return 0;
		if (i!=k) for(int j=i; j<=n+1; j++) swap(a[i][j],a[k][j]);
		for(int j=i; j<=n+1; j++) a[i][j]/=del;
		for(k=1; k<=n; k++)
			if(k!=i) {
				del=a[k][i];
				for(int j=i; j<=n+1; j++)a[k][j]-=a[i][j]*del;
			}
	}
	return 1;
}
int main() {
	int n;
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n+1; j++)scanf("%lf",&a[i][j]);
	if(!gauss(n)) puts("No Solution");
	else for(int i=1; i<=n; i++)printf("%.2lf\n",a[i][n+1]);
	return 0;
}
