/*
AC自动机 多模式匹配算法
By:WIZeaz
O(m)建图
O(n)查询转移
输入多模式串
输出各个模式串匹配的次数
fail树加速
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
using namespace std;
#define N 500000

struct edge{
    int v,next;
    edge(){}
    edge(int _v,int _next){v=_v; next=_next;}
} rds[500001];
int head[500001];
int ecnt=0;
void addedge(int u,int v){
    rds[++ecnt]=edge(v,head[u]);
    head[u]=ecnt;
}


struct ACAM_node{
    int k[26];
    int fail;
    vector<int> no;
    int cnt;
};
int cnt[300001];
struct ACAM{
    ACAM_node tr[N];
    int num;
    void clear(){
        memset(tr,0,sizeof(tr));
        num=0;
    }
    void insert(char ch[],int no){
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
        tr[now].no.push_back(no);
    }
    void build(){
        queue<int> que;
        for (int i=0;i<26;++i)
            if (tr[0].k[i]){
                tr[tr[0].k[i]].fail=0;
                que.push(tr[0].k[i]);
            }
        
        while (!que.empty()){
            int now=que.front();
            que.pop();
            for (int i=0;i<26;++i){
                if (tr[now].k[i]){
                    tr[tr[now].k[i]].fail=tr[tr[now].fail].k[i];
                    que.push(tr[now].k[i]);
                } else {
                    tr[now].k[i]=tr[tr[now].fail].k[i];
                }
            }
        }
    }
    void query(char ch[]){
        int len=strlen(ch);
        int now=0;
        int ans=0;
        for (int i=0;i<len;++i){
            int t=ch[i]-'a';
            now=tr[now].k[t];
            tr[now].cnt++;
        }
        getSons();
        dfs(0);
    }
    void getSons(){
        for (int i=1;i<=num;++i)
            addedge(tr[i].fail,i);
    }
    int dfs(int x){
        for (int i=head[x];i!=0;i=rds[i].next){
            int v=rds[i].v;
            tr[x].cnt+=dfs(v);
        }
        for (auto no:tr[x].no){
            cnt[no]+=tr[x].cnt;
        }
        return tr[x].cnt;
    }
};
ACAM map;
char ch[5000000];
int main()
{
    map.clear();
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        scanf("%s",ch);
        map.insert(ch,i+1);
    }
    map.build();
    scanf("%s",ch);
    map.query(ch);
    for (int i=1;i<=n;++i) printf("%d\n",cnt[i]);
    return 0;
}