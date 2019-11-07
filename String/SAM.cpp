/*
Suffix-Automation author:WIZeaz
luogu3804
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define STRMAXLEN 5000000
struct SAM{
    struct node{
        int parent,next[26],len;
        int cnt;
    };
    node tr[STRMAXLEN];
    int sz[STRMAXLEN];
    int rnk[STRMAXLEN];
    int last=0;
    int num=0;
    void init(){
        last=0;
        num=0;
        tr[0].parent=-1;
    }
    void add(char ch){
        int p=last;
        int t=ch-'a';
        int now=++num;
        tr[now].len=tr[last].len+1;
        tr[now].cnt=1;
        while (p!=-1 && tr[p].next[t]==0){
            tr[p].next[t]=now; 
            p=tr[p].parent;
        }
        if (p!=-1){
            int q=tr[p].next[t];
            if (tr[p].len+1==tr[q].len){
                tr[num].parent=q;
            } else {
                tr[++num].parent=tr[q].parent;
                memcpy(tr[num].next,tr[q].next,sizeof(tr[num].next));
                tr[num].len=tr[p].len+1;
                while (p!=-1 && tr[p].next[t]==q){
                    tr[p].next[t]=num;
                    p=tr[p].parent;
                }
                tr[now].parent=tr[q].parent=num;
            }
        } else tr[now].parent=0;
        last=now;
    }
    void solve(){
        //依赖排序，可以按这个顺序dp
        for (int i=0;i<=num;++i) sz[i]=0;
        for (int i=0;i<=num;++i) sz[tr[i].len]++;
        for (int i=1;i<=num;++i) sz[i]+=sz[i-1];
        for (int i=0;i<=num;++i) rnk[--sz[tr[i].len]]=i;
        for (int i=num;i>=1;--i){
            tr[tr[rnk[i]].parent].cnt+=tr[rnk[i]].cnt;
        }
    }
    long long getAns(){
        long long ans=0;
        solve();
        for (int i=1;i<=num;++i)
            if (tr[i].cnt!=1){
                ans=max(ans,(long long)tr[i].cnt*(long long)tr[i].len);
            }
        return ans;
    }
};
SAM sam;
char str[2000001];
int main(){
    scanf("%s",str);
    sam.init();
    int len=strlen(str);
    for (int i=0;i<len;++i) sam.add(str[i]);
    printf("%lld",sam.getAns());
}