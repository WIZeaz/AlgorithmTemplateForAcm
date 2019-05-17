#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;
#define N 100000
struct trie{
    struct node{
        int k[26];
        int c;
    };
    node tr[N];
    int vernum=0;
    int roots[N];
    int num;
    void clear(){
        memset(tr,0,sizeof(tr));
        memset(roots,0,sizeof(roots));
        vernum=0;
        num=0;
    }
    void insert(char ch[],int version){
        int len=strlen(ch);
        roots[++vernum]=++num;
        int now=num;
        int now2=roots[version];
        tr[now]=tr[now2];
        for (int i=0;i<len;++i){
            int t=ch[i]-'a';
            ++num;
            tr[now].k[t]=num;
            if (tr[now2].k[t]){ tr[num]=tr[tr[now2].k[t]]; }
            tr[num].c+=1;
           now=tr[now].k[t]; now2=tr[now2].k[t]; 
        }
    }
    bool query(char ch[],int l,int r){
        int len=strlen(ch);
        int nowr=roots[r];
        int nowl=roots[l-1];
        for (int i=0;i<len;++i){
            int t=ch[i]-'a';
            if (tr[tr[nowr].k[t]].c-tr[tr[nowl].k[t]].c<=0) return false;
            nowr=tr[nowr].k[t]; nowl=tr[nowl].k[t];   
        }
        return true;
    }
};
trie map;
int main()
{
    string a,b;
    char ch[1000];
    map.clear();
    while (cin>>a){
        scanf("%s",ch);
        if (a=="insert") map.insert(ch,map.vernum);
        else if (a=="query"){
            int l,r;
            cin>>l>>r;
            cout<<(map.query(ch,l,r)?"true\n":"false\n");
        }
    }
}