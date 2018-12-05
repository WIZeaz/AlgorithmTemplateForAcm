//FFT
#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
//#include<complex>
#include<cmath>
using namespace std;
//����������
const int MAX=3e5+10;//ȫ�ֱ���maxlen������
const double PI=acos(-1);//����PI

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

//(ȫ����������ÿ��case��Ҫ����)
cpx ratio_a[MAX],ratio_b[MAX];//A,B����ʽ��ϵ����������ʽ
int la,lb;//A,B����ʽ������
int maxlen;//���ڵ���la+lb-1�ĵ�һ��2����������
int reverse[MAX];//�洢0~maxlen-1���������Ķ����Ƶ��ú��ֵ������ֱ�Ӳ�ѯ

//���reverse���飬��֪����û�и��õİ취����
void getreverse() {
	//int total=maxlen>>1;//log(2)(total) ��Ϊ0~maxlen-1�ڵ����Ķ�����λ��
	int bit=0,cmp=maxlen;
	while(cmp>1)cmp>>=1,bit++;
	for(int i=0; i<maxlen; i++)
		reverse[i]=(reverse[i>>1]>>1)|((i&1)<<(bit-1));
}

//FFT���壬arrayΪҪ����DFT����ɢ����Ҷ�任����IDFT����ɢ����Ҷ���任�������飬dftΪ1��DFT��-1��IDFT
void fft(cpx *array,int dft) {
	//�����±껥Ϊ���õ�����Ԫ��
	for(int i=0; i<maxlen; ++i) {
		int temp=reverse[i];
		if(temp<=i) continue;
		cpx tempp=array[i];
		array[i]=array[temp];
		array[temp]=tempp;
	}
	//�����������������Ӳ���Ϊ1��ʼ
	for(int step=1; step<maxlen; step<<=1) {
		cpx atom(cos(PI/step),dft*sin(PI/step));//���㵥λ����atom����2*step��Ϊ��
		for(int start=0; start<maxlen; start+=step+step) {
			cpx atoms=cpx(1,0);//��λ������0�η�
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
	//��ΪIDFT��ÿһ�����maxlen
	if(dft==-1)
		for(int i=0; i<maxlen; ++i) array[i]=array[i]/maxlen;
}

//����׼����ratio_a��ratio_b������
void solve() {
	//��ȡmaxlen��ֵ
	maxlen=1;
	while(maxlen<la+lb-1) maxlen<<=1;

	//��ȡreverse����
	getreverse();

	//��A��B����ʽ��չ�����ϵ����Ϊ��
	for(int i=la; i<maxlen; ++i) ratio_a[i]=cpx(0,0);
	for(int i=lb; i<maxlen; ++i) ratio_b[i]=cpx(0,0);

	fft(ratio_a,1);
	fft(ratio_b,1);//�ֱ���������˶���ʽDFT
	for(int i=0; i<maxlen; ++i) ratio_a[i]=ratio_a[i]*ratio_b[i]; //�ڵ��ʾ������������ʽ�Ļ�
	fft(ratio_a,-1);//IDFT�������ʾ���Ķ���ʽ֮��ת��Ϊϵ����ʾ����ϵ���浽ratio_a������
}

//�Գ��������˷�Ϊ��
char number[MAX];//���ʼ�ַ���
int inians[MAX];//��ʼ��
int finalans[MAX];//���մ�
int ans[MAX];
int main() {
	while(~scanf("%s",number)) {
		la=strlen(number);//���la
		for(int i=0; i<la; ++i)  //���������ֵ�ÿһλת��Ϊ�������ߵ�
			ratio_a[la-i-1]=cpx(number[i]-'0',0);

		scanf("%s",number);
		lb=strlen(number);
		for(int i=0; i<lb; ++i)
			ratio_b[lb-i-1]=cpx(number[i]-'0',0);

		//����FFT
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
