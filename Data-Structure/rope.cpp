#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;
rope<int> *a[1000001];
//erase
int main()
{
    int n,m;
    int num=0;
    scanf("%d%d",&n,&m);
    a[0]=new rope<int>();
    for (int i=0;i<n;++i) {
        int t;
        scanf("%d",&t);
        a[0]->push_back(t);
    }
    for (int i=0;i<m;++i){
        int v,op,loc;
        scanf("%d%d%d",&v,&op,&loc);
        ++num;
        a[num]=new rope<int>(*a[v]);
        if (op==1){
            int val;
            scanf("%d",&val);
            a[num]->replace(loc-1,val);
        } else {
            printf("%d\n",a[v]->at(loc-1));
        }
    }
}