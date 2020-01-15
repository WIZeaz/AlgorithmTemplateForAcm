#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXSTRLEN 15000000
int maxlen=0;
char ch[2*MAXSTRLEN+3];
int p[2*MAXSTRLEN+3];
void manacher(char str[],int len){
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
        j=min(p[2*id-i],mx-i);
        while (ch[i-j]==ch[i+j]) ++j;
        p[i]=j;
        if (i+p[i]>mx) {id=i; mx=i+p[i];}
        maxlen=max(maxlen,p[i]-1);
    }
}
char str[MAXSTRLEN+1];
int main(){
    scanf("%s",str);
    maxlen=0;
    int len=strlen(str);
    manacher(str,len);
    printf("%d",maxlen);
}