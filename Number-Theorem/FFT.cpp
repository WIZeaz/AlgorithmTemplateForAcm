#include<bits/stdc++.h>
using namespace std;

const int N=1400000;
const double PI=acos(-1.0);

struct cpx {
	double x,y;
	cpx() {}
	cpx(double _x,double _y):x(_x),y(_y) {}
	cpx operator+(const cpx &b)const{
		return cpx(x+b.x,y+b.y);
	}
	cpx operator-(const cpx &b)const{
		return cpx(x-b.x,y-b.y);
	}
	cpx operator*(const cpx &b)const{
		return cpx(x*b.x-y*b.y,x*b.y+y*b.x);
	}
	cpx operator/(const int &b)const{
		return cpx(x/b,y/b);
	}
};

int rev[2*N+10];
void getrev(int len){
	int bit=0;
	while((1<<bit)<len)bit++;
	for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
}

void fft(cpx x[],int len,int opt){
	for(int i=0;i<len;i++)
		if(i<rev[i])swap(x[i],x[rev[i]]);
	for(int mid=1;mid<len;mid<<=1){
		cpx tmp(cos(PI/mid),opt*sin(PI/mid));
		for(int i=0,add=mid<<1;i<len;i+=add){
			cpx base(1,0);
			for(int j=i;j<i+mid;j++,base=base*tmp){
				cpx a=x[j],b=base*x[j+mid];
				x[j]=a+b,x[j+mid]=a-b;
			}
		}
	}

	if(opt==-1)
		for(int i=0;i<len;i++)x[i]=x[i]/len;
}

cpx ffta[2*N+10],fftb[2*N+10];
int solve(int a[],int b[],int lena,int lenb){
	int len=1;
	while(len<lena+lenb)len<<=1;
	getrev(len);
	
	for(int i=0;i<lena;i++)ffta[i]=cpx(a[i],0);
	for(int i=lena;i<len;i++)ffta[i]=cpx(0,0);
	for(int i=0;i<lenb;i++)fftb[i]=cpx(b[i],0);
	for(int i=lenb;i<len;i++)fftb[i]=cpx(0,0);

	fft(ffta,len,1),fft(fftb,len,1);
	for(int i=0;i<len;i++)ffta[i]=ffta[i]*fftb[i];
	fft(ffta,len,-1);
	return len;
}

char s1[N+10],s2[N+10];
int a[N+10],b[N+10],ans[2*N+10];
// 下标从0开始
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++)scanf("%d",&a[i]);
	for(int i=0;i<=m;i++)scanf("%d",&b[i]);

	int len=solve(a,b,n+1,m+1),pre=0;

	for(int i=0;i<=n+m;i++){
		ans[i]=int(ffta[i].x+0.5);
		printf("%d ",ans[i]);
	}
}
