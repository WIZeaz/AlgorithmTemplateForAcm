//FFT
#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
//#include<complex>
#include<cmath>
using namespace std;
//（定义区）
const int MAX=3e5+10;//全局变量maxlen的上限
const double PI=acos(-1);//定义PI

//复数定义
typedef struct cpx {
	double r,i;
	cpx() {}
	cpx(double a,double b):r(a),i(b) {}
	inline cpx operator *(const cpx &a)const {
		return cpx(r*a.r-i*a.i,r*a.i+i*a.r);
	}
	inline cpx operator +(const cpx &a)const {
		return cpx(r+a.r,i+a.i);
	}
	inline cpx operator -(const cpx &a)const {
		return cpx(r-a.r,i-a.i);
	}
	inline cpx operator /(const int &a)const {
		return cpx(r/a,i/a);
	}
	inline double real() {
		return r;
	}
} cpx;

//(全局数据区，每个case都要更新)
cpx ratio_a[MAX],ratio_b[MAX];//A,B多项式的系数，复数形式
int la,lb;//A,B多项式的项数
int maxlen;//大于等于la+lb-1的第一个2的整数次幂
int Reverse[MAX];//存储0~maxlen-1内所有数的二进制倒置后的值，方便直接查询

//获得reverse数组，不知道有没有更好的办法。。
void getreverse() {
	//int total=maxlen>>1;//log(2)(total) 即为0~maxlen-1内的数的二进制位数
	int bit=0,cmp=maxlen;
	while(cmp>1)cmp>>=1,bit++;
	for(int i=0; i<maxlen; i++)
		Reverse[i]=(Reverse[i>>1]>>1)|((i&1)<<(bit-1));
}

//FFT主体，array为要进行DFT（离散傅里叶变换）或IDFT（离散傅里叶反变换）的数组，dft为1：DFT，-1：IDFT
void fft(cpx *array,int dft) {
	//交换下标互为倒置的数组元素
	for(int i=0; i<maxlen; ++i) {
		int temp=Reverse[i];
		if(temp<=i) continue;
		cpx tempp=array[i];
		array[i]=array[temp];
		array[temp]=tempp;
	}
	//蝴蝶操作，倍增，从步长为1开始
	for(int step=1; step<maxlen; step<<=1) {
		cpx atom(cos(PI/step),dft*sin(PI/step));//计算单位复根atom（以2*step）为底
		for(int start=0; start<maxlen; start+=step+step) {
			cpx atoms=cpx(1,0);//单位复根的0次方
			for(int j=start; j<start+step; ++j) {
				//B[j]=L[j]+atoms*R[j]
				//B[n/2+j]=L[j]-atoms*R[j]
				cpx L=array[j],R=atoms*array[j+step];
				array[j]=L+R;
				array[j+step]=L-R;
				atoms=atoms*atom;
			}
		}
	}
	//若为IDFT，每一项除以maxlen
	if(dft==-1)
		for(int i=0; i<maxlen; ++i) array[i]=array[i]/maxlen;
}

//需先准备好ratio_a和ratio_b的意义
void solve() {
	//获取maxlen的值
	maxlen=1;
	while(maxlen<la+lb-1) maxlen<<=1;

	//获取reverse数组
	getreverse();

	//将A，B多项式扩展的项的系数置为零
	for(int i=la; i<maxlen; ++i) ratio_a[i]=cpx(0,0);
	for(int i=lb; i<maxlen; ++i) ratio_b[i]=cpx(0,0);

	fft(ratio_a,1);
	fft(ratio_b,1);//分别对两个待乘多项式DFT
	for(int i=0; i<maxlen; ++i) ratio_a[i]=ratio_a[i]*ratio_b[i]; //在点表示法下求两多项式的积
	fft(ratio_a,-1);//IDFT，将点表示法的多项式之积转换为系数表示法，系数存到ratio_a数组中
}

//以超大整数乘法为例
char number[MAX];//存初始字符串
int inians[MAX];//初始答案
int finalans[MAX];//最终答案
int ans[MAX];
int main() {
	while(~scanf("%s",number)) {
		la=strlen(number);//获得la
		for(int i=0; i<la; ++i)  //将输入数字的每一位转换为复数并颠倒
			ratio_a[la-i-1]=cpx(number[i]-'0',0);

		scanf("%s",number);
		lb=strlen(number);
		for(int i=0; i<lb; ++i)
			ratio_b[lb-i-1]=cpx(number[i]-'0',0);

		//进行FFT
		solve();

		int pre=0;
		int cnt=0,ojbk=0;
		for(int i=0; i<maxlen; i++)
			ans[++cnt]=int(ratio_a[i].real()+0.5);
		for(int i=1; i<=cnt; i++) {
			pre+=ans[i];
			ans[i]=pre%10;
			pre/=10;
		}
		while(pre)ans[++cnt]=pre%10,pre/=10;
		while(cnt&&!ans[cnt])cnt--;
		if(!cnt)printf("0");
		else for(int i=cnt; i>=1; i--)printf("%d",ans[i]);

		printf("\n");
	}
}
