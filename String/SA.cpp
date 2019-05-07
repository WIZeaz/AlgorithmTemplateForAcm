#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define STRMAXLEN 1000010
int rnk[STRMAXLEN];
int buckets[STRMAXLEN];
int sa[STRMAXLEN]; //the number of rank i number,start from 1
int tsa[STRMAXLEN];
int height[STRMAXLEN];
int bucketSort(int len,int charnum,int k){
    for (int i=0;i<=charnum;++i) buckets[i]=0;
    for (int i=0;i<len;++i) buckets[rnk[i]]++;
    for (int i=1;i<=charnum;++i) buckets[i]+=buckets[i-1];
    for (int i=len;i>=1;--i) sa[buckets[rnk[tsa[i]]]--]=tsa[i];
    swap(tsa,rnk); //sheng shu zu
    charnum=1;
    rnk[sa[1]]=1;
    for (int i=2;i<=len;++i){
        if (tsa[sa[i]]!=tsa[sa[i-1]]) ++charnum;
        else if ((sa[i]+k>=len) != (sa[i-1]+k>=len)) ++charnum;
        else if ((sa[i]+k<len && sa[i-1]+k<len) && tsa[sa[i]+k]!=tsa[sa[i-1]+k]) ++charnum;
        rnk[sa[i]]=charnum;
    }
    return charnum;
}
void SuffixSort(char str[],int len){
    for (int i=0;i<len;++i){
        rnk[i]=int(str[i]);
        tsa[i+1]=i;
    }
    int charnum=bucketSort(len,256,0);
    for (int k=1;k<len && charnum<len;k<<=1){
        int t=0;
        for (int i=0;i<k;++i) tsa[++t]=len-k+i;
        for (int i=1;i<=len;++i) if (sa[i]-k>=0) tsa[++t]=sa[i]-k;
        charnum=bucketSort(len,charnum,k);
    }
}
void getHeight(char str[],int len){
    int j=0;
    for (int i=0;i<len;++i){
        if (rnk[i]-1>0) while (str[i+j]==str[sa[rnk[i]-1]+j]) ++j;
        height[rnk[i]]=j;
        if (j>0) --j;
    }
}
char str[STRMAXLEN];
int main()
{
    scanf("%s",str);
    int len=strlen(str);
    SuffixSort(str,len);
    for (int i=1;i<=len;++i) 
        printf("%d ",sa[i]+1);
}