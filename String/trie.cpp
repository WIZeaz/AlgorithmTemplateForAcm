#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;
#define N 100000
struct trie_node{
    int k[26];
   // int c;
};
struct trie{
    trie_node tr[N];
    int num;
    void clear(){
        memset(tr,0,sizeof(tr));
        num=0;
    }
    void insert(char ch[]){
        int len=strlen(ch);
        int now=0;
        for (int i=0;i<len;++i){
            int t=ch[i]-'0';
            if (tr[now].k[t]==0){
                ++num;
                tr[now].k[t]=num;
            }
            now=tr[now].k[t];
        }
    }
    bool query(char ch[]){
        int len=strlen(ch);
        int now=0;
        for (int i=0;i<len;++i){
            int t=ch[i]-'0';
            if (tr[now].k[t]==0) return false;
            now=tr[now].k[t];
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
        if (a=="insert") map.insert(ch);
        else if (a=="query") cout<<(map.query(ch)?"true\n":"false\n");
    }
}