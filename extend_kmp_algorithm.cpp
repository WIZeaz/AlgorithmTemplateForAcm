//o(m+n)
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#define ll long long
using namespace std;

const int MAX_PATTERN=1e6+5;//模式串最大长度
const int MAX_MATCH=1e4+5;//匹配串最大长度

char pattern[MAX_PATTERN];//模式串
int extend[MAX_PATTERN];//模式串的extend数组

char match[MAX_MATCH];//匹配串
int Next[MAX_MATCH];//匹配串的next数组

int len_pattern,len_match;//模式串长度，匹配串长度

//获取模式串和匹配串的长度 
void get_both_len(){
	len_pattern=strlen(pattern);
	len_match=strlen(match);
}

//得到Next数组 
void getnext(){
	Next[0]=len_match;//第零位直接求得

	int i=0,j=1;
	for(;j<len_match&&match[i]==match[j];i++,j++){}//找出从匹配串的第1位开始，与从其第0位开始的最大匹配长度
	int pos_ini=1;//得到最大匹配长度的起始位置
	Next[pos_ini]=i;

	for(int k=2;k<len_match;++k)
	{
		if(Next[k-pos_ini]+k<pos_ini+Next[pos_ini]) Next[k]=Next[k-pos_ini];//不需要继续匹配即可得next[k]
		else
		{
			int begin=Next[pos_ini]+pos_ini;//从稍早时匹配的最大位置开始继续匹配
			if(k>pos_ini+Next[pos_ini]-1) begin=k;//若k已超过“稍早时匹配的最大位置”，就从k本身开始匹配

			i=0;
			for(;begin+i<len_match&&match[begin+i]==match[begin-k+i];++i){}
			Next[k]=begin-k+i;
			pos_ini=k;//更新得到最大匹配位置的起点
		}
	}
}

//结构与函数getnext几乎完全相同
void getextend(){
	getnext();

	int i=0,j=0;
	for(;i<len_pattern&&j<len_match&&pattern[i]==match[j];++i,++j){}
	extend[0]=i;
	int pos_ini=0;

	for(i=1;i<len_pattern;++i)
	{
		if(Next[i-pos_ini]+i<pos_ini+extend[pos_ini]) extend[i]=Next[i-pos_ini];
		else
		{
			int begin=pos_ini+extend[pos_ini];
			if(i>pos_ini+extend[pos_ini]-1) begin=i;

			j=0;
			for(;begin+j<len_pattern&&begin-i+j<len_match&&pattern[begin+j]==match[begin-i+j];j++){}
			extend[i]=begin-i+j;
			pos_ini=i;
		}
	}
}

//输入两个串后可直接执行 
void do_all(){
	get_both_len();
	getextend();
}


int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%s %s",match,pattern);
		do_all();
		
		//
	}
} 
