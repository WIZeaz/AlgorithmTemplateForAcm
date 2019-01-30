#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
long long d[20][10000];
long long query(int l,int r){
    int t=log2(r-l+1);
    return max(d[t][l],d[t][r-(1<<t)+1]);
}
void init(long long a[],int len){
    for (int i=0;i<len;++i){
        d[0][i]=a[i];
    }
    int t=1;
    for (int i=1;t<=len;++i){
        for (int j=0;j+t<len;++j)
            d[i][j]=max(d[i-1][j],d[i-1][j+t]);
        t<<=1;
    }
}
int main()
{
    int n;
    long long a[10000];
    cin>>n;
    for (int i=0;i<n;++i) cin>>a[i];
    init(a,n);
    int l,r;
    while (cin>>l>>r){
        cout<<query(l,r)<<endl;
    }
}