#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define BASE_N 62
struct linear_base{
    long long vec[BASE_N+1];
    int n,m;
    bool worked;
    void clear(){
        memset(vec,0,sizeof(vec));
        n=m=0;
        worked=false;
    }
    bool add(long long x){
        ++n;
        for (int i=BASE_N;i>=0;--i)
            if (x&(1LL<<i)){
                if (!vec[i]) {vec[i]=x; ++m; return true;}
                x^=vec[i];
            }
        return false;
    }
    long long max(){
        long long ans=0;
        for (int i=BASE_N;i>=0;--i)
            if (ans^vec[i]>ans) ans=ans^vec[i];
        return ans;
    }
    long long min(){
        for (int i=0;i<=BASE_N;++i)
            if (vec[i]) return vec[i];
    }
    void merge(const linear_base& b){
        for (int i=0;i<=BASE_N;++i)
            if (b.vec[i]) add(b.vec[i]);
    }
    void work(){
        if (worked) return;
        for (int i=1;i<=BASE_N;++i)
            for (int j=0;j<i;++j)
                if (vec[i] & (1LL<<i)) vec[i]^=vec[j];
        worked=true;
    }
    long long findkth(long long k){  //kth small
        if (m<n) --k;
        if (k<1) return 0;
        work();
        long long ans=0;
        for (int i=0;i<=BASE_N;++i)
            if (vec[i]){
                if (k&1) ans^=vec[i];
                k>>=1;
            }
        if (k>0) return -1;
        return ans;
    }
    bool test(long long x){
        for (int i=BASE_N;i>=0;--i)
            if (x&(1LL<<i)){
                if (vec[i]) x^=vec[i];
                else return true; 
            }
        return false;
    }
    linear_base operator & (linear_base& b) const {
        linear_base ans;
        linear_base tmp=*this;
        linear_base r;
        ans.clear();
        for (int i=0;i<=BASE_N;++i) r.vec[i]=1LL<<i;
        for (int j=0;j<=BASE_N;++j)
            if (b.vec[j]){
                long long x=b.vec[j];
                long long k=0;
                for (int i=BASE_N;i>=0;--i)
                    if (x & (1LL<<i)){
                        if (!tmp.vec[i]){
                            tmp.vec[i]=x;
                            r.vec[i]=k;
                            break;
                        }
                        x^=tmp.vec[i];
                        k^=r.vec[i];
                    }
                if (!x){
                    for (int i=0;i<=BASE_N;++i)
                        if (k & (1LL<<i)) x^=tmp.vec[i];
                    ans.add(x);
                }
            }
        return ans;
    }
};
linear_base a,b;
int main(){
    /*int T;
    scanf("%d",&T);
    for (int C=1;C<=T;++C){
        l.clear();
        int n,q;
        scanf("%d",&n);
        for (int i=0;i<n;++i){
            long long t;
            scanf("%lld",&t);
            l.add(t);
        }
        scanf("%d",&q);
        printf("Case #%d:\n",C);
        while (q--){
            long long k;
            scanf("%lld",&k);
            printf("%lld\n",l.findkth(k));
        }
    }*/
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        long long t;
        scanf("%lld",&t);
        a.add(t);
    }
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        long long t;
        scanf("%lld",&t);
        b.add(t);
    }
    linear_base c=a&b;
    for (int i=BASE_N;i>=0;--i)
        if (c.vec[i]) printf("%lld\n",c.vec[i]);
}