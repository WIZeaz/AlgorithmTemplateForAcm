//link-cut-tree
#include<iostream>
#include<cstdio>
#include<set>
#include<cmath>
#define sci(a) scanf("%d",&a)
#define ll long long
using namespace std;
const int N=2e5+5;
const int INF=0x3f3f3f3f;

struct LCT{
	int f[N],c[N][2],v[N];int s[N];//父亲，儿子，值，子树值之和 
	int sta[N];//手工栈 
	bool r[N];//翻转标记 
	
	void ini(){
		
	}
	
	bool nroot(int x){
		return c[f[x]][0]==x||c[f[x]][1]==x;
	}
	
	void pushup(int x){
		int lson=c[x][0],rson=c[x][1];
		//s[x]=v[x]^s[lson]^s[rson];
	}
	
	void reverse(int x){
		int temp=c[x][0];
		c[x][0]=c[x][1];
		c[x][1]=temp;
		//
		r[x]^=1;
	}
	
	void pushdown(int x){
		if(r[x]){
			if(c[x][0]) reverse(c[x][0]);
			if(c[x][1]) reverse(c[x][1]);
			r[x]=0;
		}
	}	
	
	void rotate(int x){
		int y=f[x],z=f[y],k=(c[y][1]==x),w=c[x][!k];
		if(nroot(y)) c[z][c[z][1]==y]=x;
		c[x][!k]=y;c[y][k]=w;
		if(w) f[w]=y;
		f[y]=x;f[x]=z;
		pushup(y);
	}
	
	void splay(int x){
		int y=x,z=0;
		sta[++z]=y;
		while(nroot(y)) sta[++z]=y=f[y];
		while(z) pushdown(sta[z--]);
		while(nroot(x)){
			y=f[x];z=f[y];
			if(nroot(y)){
				if((c[z][1]==y)==(c[y][1]==x)) rotate(y);
				else rotate(x);
			}
			rotate(x);
		}
		pushup(x);
	}
	
	void access(int x){
		for(int y=0;x;x=f[y=x]){
			splay(x);c[x][1]=y;pushup(x);
		}
	}
	
	void makeroot(int x){
		access(x);splay(x);reverse(x);
	}
	
	int findroot(int x){
		access(x);splay(x);
		while(c[x][0]){
			pushdown(x);
			x=c[x][0];
		}
		splay(x);
		return x;
	}
	
	bool isconnected(int x,int y){
		makeroot(x);
		return findroot(y)==x;
	}
	
	void split(int x,int y){
		makeroot(x);access(y);splay(y);
	}
	
	void link(int x,int y){
		makeroot(x);
		if(findroot(y)!=x) {//有些题不用判断 
		//makeroot(y);少数模板有这句 
		f[x]=y;
		pushup(y);
		} 
	}
	
	void cut(int x,int y){
		makeroot(x);
		if(findroot(y)==x&&f[y]==x&&c[y][0]==0){
			f[y]=c[x][1]=0;
			pushup(x);
		}
	}
	
	void update(int x,int val){
		access(x);splay(x);v[x]=val;
		pushup(x);
	}
};

//洛谷p3690
LCT lct;
int n,m;

int main(){
	sci(n);sci(m);
	for(int i=1;i<=n;++i){
		int a;sci(a);
		lct.v[i]=lct.s[i]=a;
	}
	for(int i=0;i<m;++i){
		int a,b,c;
		sci(a);sci(b);sci(c);
		if(a==0){
			lct.split(b,c);
			printf("%d\n",lct.s[c]);
		}else if(a==1){
			lct.link(b,c);
		}else if(a==2){
			lct.cut(b,c);
		}else{
			lct.update(b,c);
		}
	}
}

