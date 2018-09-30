#include <iostream>
#include <cstring>
using namespace std;
#define MatrixN 2
//Change MatrixN to change the size of matrix
struct matrix{
    int arr[MatrixN][MatrixN];
    matrix(){memset(arr,0,sizeof(arr));}
    static matrix unit(){
        matrix tmp;
        for (int i=0;i<MatrixN;++i)
            tmp.arr[i][i]=1;
        return tmp;
    }
    matrix set(const int b[MatrixN][MatrixN]){
        memcpy(arr,b,sizeof(arr));
    }
    matrix operator * (const matrix &b) const{
        matrix tmp;
        for (int i=0;i<MatrixN;++i)
            for (int j=0;j<MatrixN;++j)
                for (int k=0;k<MatrixN;++k)
                    tmp.arr[i][j]+=arr[i][k]*b.arr[k][j];
        return tmp;
    }
};
template<typename T> 
T QuickPower(T x,int y,T unit) //unit*x=x
{
    if (y==0) return unit;
    T tmp=x;
    T ans=unit;
    while (y>0){
        if (y&1) ans=ans*tmp;
        tmp=tmp*tmp;
        y=y>>1;
    }
    return ans;
}
int main()
{
    //use Fibonacci Sequence for example.
    int y;
    int init[2][2]={{0,1},{1,1}};
    while (cin>>y){
        matrix tmp;
        tmp.set(init);
        tmp=QuickPower(tmp,y-1,matrix::unit());
        int ans=0;
        for (int i=0;i<2;++i) ans+=tmp.arr[0][i];
        cout<<ans<<endl;
    }
}
