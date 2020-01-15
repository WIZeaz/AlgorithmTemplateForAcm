#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> a;
int main(){
    scanf("%d",&n);
    a.clear();
    for (int i=0;i<n;++i){
        int t;
        scanf("%d",&t);
        a.push_back(t);
    }
    int l=0;
    int r=n-1;
    while (l<r){
        int mid=l+r>>1;
        if (a[mid]<a[mid+1]) l=mid+1;
        else r=mid;
    }
    printf("%d\n",a[r]);
}