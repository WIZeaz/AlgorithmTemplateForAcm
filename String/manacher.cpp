#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXSTRLEN 15000000
int maxlen=0;
char ch[2*MAXSTRLEN+3];
int p[2*MAXSTRLEN+3];
void manacher(char str[]){
    int len=strlen(str);
    for (int i=0;i<len;++i){
        ch[2*i+1]='#';
        ch[2*i+2]=str[i];
    }
    ch[0]='$';
    ch[2*len+1]='#';
    ch[2*len+2]='\0';
    len=len*2+2;
    p[0]=p[1]=1;
    int id,mx;
    id=1; mx=2;
    for (int i=2;i<len;++i){
        int j;
        if (i<mx) j=min(p[2*id-i],mx-i);
        else j=1;
        while (ch[i-j]==ch[i+j]) ++j;
        p[i]=j;
        if (j+p[j]>mx) {id=j; mx=j+p[j];}
        maxlen=max(maxlen,p[i]-1);
    }
}
char str[MAXSTRLEN+1];
int main(){
    scanf("%s",str);
    maxlen=0;
    manacher(str);
    printf("%d",maxlen);
}