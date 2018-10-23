#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;
int Next[5001];
void getNext(const char s2[],int Next[])
{
    int len=strlen(s2);
    int j=0;
    Next[0]=Next[1]=0;
    for (int i=1;i<len;i++){
		while (j>0 && s2[j]!=s2[i]) j=Next[j];
		if (s2[j]==s2[i]) ++j;
		Next[i+1]=j;
	}
}
int kmp(const char s1[],const char s2[],const int Next[])
{
    int ans=0;
    int j=0;
    int len=strlen(s1);
    int tlen=strlen(s2);
    for (int i=0;i<len;i++){
		while (j>0 && s2[j]!=s1[i]) j=Next[j];
		if (s2[j]==s1[i]) ++j;
		if (j==tlen){
            //dosomething here
            ++ans;
            j=0;
        }
	}
    return ans;
}
int main()
{
	string a,b;
	cin.sync_with_stdio(false);
	while (cin>>a){
		if (a=="#") return 0;
		cin>>b;
        getNext(b.c_str(),Next);
		cout<<kmp(a.c_str(),b.c_str(),Next)<<endl;
	}
}