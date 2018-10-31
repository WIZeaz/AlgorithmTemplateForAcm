#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define N 100000
int Next[1000],ex[1000];
void exkmp(char s1[],char s2[],int Next[],int ex[]){
    int i,j,k;
    int len1=strlen(s1);
    int len2=strlen(s2);
    i=0; j=0; k=-1;
    while (i<len1){
        if (k==-1){
            k=0; j=0;
            while (s1[i+k]==s2[j+k] && i+k<len1 && j+k<len2) ++k;
            ex[i]=k;
        } else if (Next[j]<k){
            ex[i]=Next[j];
        } else if (Next[j]>k){
            ex[i]=k;
        } else {
            j=0;
            while (s1[i+k]==s2[j+k] && i+k<len1 && j+k<len2) ++k;
            ex[i]=k;
        }
        ++i; ++j; --k;
    }
    ex[len1]=0;
}
int main()
{
    char s1[1000],s2[1000];
    scanf("%s%s",s1,s2);
    Next[0]=0;
    exkmp(s2+1,s2,Next,Next+1);
    exkmp(s1,s2,Next,ex);
    int len=strlen(s1);
    for (int i=0;i<len;++i) cout<<ex[i]<<' ';
}