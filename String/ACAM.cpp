/*
AC自动机 多模式匹配算法
By:WIZeaz
O(m)建图
O(n)查询转移
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;
#define N 300000
struct ACAM_node{
    int k[26];
    int fail;
    int sum;
};
struct ACAM{
    ACAM_node tr[N];
    int num;
    void clear(){
        memset(tr,0,sizeof(tr));
        num=0;
    }
    void insert(char ch[]){
        int len=strlen(ch);
        int now=0;
        for (int i=0;i<len;++i){
            int t=ch[i]-'a';
            if (tr[now].k[t]==0){
                ++num;
                tr[now].k[t]=num;
            }
            now=tr[now].k[t];
        }
        ++tr[now].sum;
    }
    void build(){
        int que[N];
        int q,p;
        p=0; q=0;
        for (int i=0;i<26;++i)
            if (tr[0].k[i]!=0){
                tr[tr[0].k[i]].fail=0;
                que[q]=tr[0].k[i];
                ++q;
            }
        
        while (p<q){
            int now=que[p];
            ++p;
            for (int i=0;i<26;++i){
                if (tr[now].k[i]!=0){
                    tr[tr[now].k[i]].fail=tr[tr[now].fail].k[i];
                    que[q]=tr[now].k[i];
                    ++q;
                } else {
                    tr[now].k[i]=tr[tr[now].fail].k[i];
                }
            }
        }
    }
    int query(char ch[]){
        int len=strlen(ch);
        int now=0;
        int ans=0;
        for (int i=0;i<len;++i){
            int t=ch[i]-'a';
            now=tr[now].k[t];
            int tmp=now;
            while (tr[tmp].sum>=0){
                ans+=tr[tmp].sum;
                tr[tmp].sum=-1;
                tmp=tr[tmp].fail;
            }
        }
        return ans;
    }
};
ACAM map;
char ch[1500000];
int main()
{
    int T;
    scanf("%d",&T);
    while (T--){
        map.clear();
        int n;
        scanf("%d",&n);
        for (int i=0;i<n;++i){
            scanf("%s",ch);
            map.insert(ch);
        }
        map.build();
        scanf("%s",ch);
        printf("%d\n",map.query(ch));
    }
    return 0;
}