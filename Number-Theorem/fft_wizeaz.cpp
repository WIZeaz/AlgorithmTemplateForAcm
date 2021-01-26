#include <bits/stdc++.h>
using namespace std;
namespace FFT{
    using fComp=complex<double>;
    const int maxn=3000000;
    const double PI2=6.283185307;
    fComp cpxA[maxn],cpxB[maxn],cpxC[maxn];
    int revBit[maxn];
    
    void _init_rev(int len){
        revBit[0]=0;
        int halflen=len>>1;
        for (int i=1;i<len;++i){
            revBit[i]=(revBit[i>>1]>>1) |(1&i?halflen:0);
            //if (i&1) rev[i]|=1<<len;
        }
    }
    void DFT(fComp x[],int len,int rev){

        for (int i=0;i<len;++i)
            if (i<revBit[i]) swap(x[i],x[revBit[i]]);
        for (int k=2;k<=len;k<<=1){
            // fComp base=exp(fComp(0,rev*2.0*PI/k));
            fComp base(cos(PI2/k),rev*sin(PI2/k));
            int half=k>>1;
            for (int i=0;i<len;i+=k){
                fComp w(1,0);
                for (int j=i;j<i+half;++j){
                    fComp a=x[j];
                    fComp b=x[j+half];
                    x[j]=a+w*b;
                    x[j+half]=a-w*b;
                    w*=base;
                }
            }
        }

        if (rev==-1){
            for (int i=0;i<len;++i) x[i]/=len;
        }
    }

    void poly_mul(int a[],int lena,int b[],int lenb,int c[]){
        int lenc=1;
        while (lenc<lena+lenb-1) lenc<<=1;

        _init_rev(lenc);

        for (int i=0;i<lena;++i) cpxA[i]=fComp(a[i],0);
        for (int i=lena;i<lenc;++i) cpxA[i]=fComp(0,0);
        for (int i=0;i<lenb;++i) cpxB[i]=fComp(b[i],0);
        for (int i=lenb;i<lenc;++i) cpxB[i]=fComp(0,0);

        DFT(cpxA,lenc,1);
        DFT(cpxB,lenc,1); 

        for(int i=0;i<lenc;++i) cpxC[i]=cpxA[i]*cpxB[i];

        DFT(cpxC,lenc,-1);

        for (int i=0;i<lenc;++i) c[i]=int(cpxC[i].real()+0.5);
    }
}
int a[2000001],b[2000001];
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=0;i<=n;++i) scanf("%d",&a[i]);
    for (int i=0;i<=m;++i) scanf("%d",&b[i]);
    FFT::poly_mul(a,n+1,b,m+1,a);

    for (int i=0;i<=n+m;++i) printf("%d ",a[i]);
}