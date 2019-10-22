#include<bits/stdc++.h>
using namespace std;

struct node{
	double l,r,h;
	int add;
	node(){}
	node(double _l,double _r,double _h,int _add):l(_l),r(_r),h(_h),add(_add){}
};

double x[2200],sum[2200<<2];
node q[2200];
int mark[2200<<2];

void pushup(int n,int left,int right){
	if(mark[n])sum[n]=x[right+1]-x[left];
	else if(left==right)sum[n]=0;
	else sum[n]=sum[n<<1]+sum[n<<1|1];
}

void pushdown(int n){
	mark[n<<1]+=mark[n],mark[n<<1|1]+=mark[n];
	mark[n]=0;
}

void update(int l,int r,int add,int n,int left,int right){
	if(l<=left&&right<=r){
		mark[n]+=add;
		pushup(n,left,right);
		return;
	}
	int mid=left+right>>1;
	if(l<=mid)update(l,r,add,n<<1,left,mid);
	if(mid<r)update(l,r,add,n<<1|1,mid+1,right);
	pushup(n,left,right);
}

int main(){
	int kase=1,n;
	while(~scanf("%d",&n)&&n){
		for(int i=1;i<=n;i++){
			double a,b,c,d;
			scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
			x[2*i-1]=a;x[2*i]=c;
			q[2*i-1]=node(a,c,b,1);
			q[2*i]=node(a,c,d,-1);
		}
		sort(x+1,x+1+2*n);
		sort(q+1,q+1+2*n,[&](node a,node b){
			return a.h<b.h;
		});
		int cnt=1;
		for(int i=2;i<=2*n;i++)
			if(x[i-1]!=x[i])x[++cnt]=x[i];
		double ans=0;
		q[2*n+1].h=q[2*n].h;
		for(int i=1;i<=2*n;i++){
			int l=lower_bound(x+1,x+1+cnt,q[i].l)-x;
			int r=lower_bound(x+1,x+1+cnt,q[i].r)-x-1;
			update(l,r,q[i].add,1,1,cnt);
			ans+=sum[1]*(q[i+1].h-q[i].h);
		}
		printf("%lf\n",ans);
	}
}