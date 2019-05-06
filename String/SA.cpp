#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define STRMAXLEN 1000010
int rnk[STRMAXLEN];
int buckets[STRMAXLEN];
int sa[STRMAXLEN]; //the number of rank i number
int tsa[STRMAXLEN];
int bucketSort(int len,int charnum,int k){
    for (int i=0;i<=charnum;++i) buckets[i]=0;
    for (int i=0;i<len;++i) buckets[rnk[i]]++;
    for (int i=1;i<=charnum;++i) buckets[i]+=buckets[i-1];
    for (int i=len-1;i>=0;--i) sa[--buckets[rnk[tsa[i]]]]=tsa[i];
    swap(tsa,rnk); //sheng shu zu
    charnum=1;
    rnk[sa[0]]=1;
    for (int i=1;i<len;++i){
        if (tsa[sa[i]]!=tsa[sa[i-1]]) ++charnum;
        else if ((sa[i]+k>=len) != (sa[i-1]+k>=len)) ++charnum;
        else if ((sa[i]+k<len && sa[i-1]+k<len) && tsa[sa[i]+k]!=tsa[sa[i-1]+k]) ++charnum;
        rnk[sa[i]]=charnum;
    }
    return charnum;
}
void SuffixSort(char str[]){
    int len=strlen(str);
    for (int i=0;i<len;++i){
        rnk[i]=int(str[i]);
        tsa[i]=i;
    }
    int charnum=bucketSort(len,256,0);
    for (int k=1;k<len && charnum<len;k<<=1){
        int t=0;
        for (int i=0;i<k;++i) tsa[t++]=len-k+i;
        for (int i=0;i<len;++i) if (sa[i]-k>=0) tsa[t++]=sa[i]-k;
        charnum=bucketSort(len,charnum,k);
    }
}
char str[STRMAXLEN];
int main()
{
    scanf("%s",str);
    SuffixSort(str);
    int len=strlen(str);
    for (int i=0;i<len;++i) 
        printf("%d ",sa[i]+1);
}