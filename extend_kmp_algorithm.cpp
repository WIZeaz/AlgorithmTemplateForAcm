//o(m+n)
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#define ll long long
using namespace std;

const int MAX_PATTERN=1e6+5;//ģʽ����󳤶�
const int MAX_MATCH=1e4+5;//ƥ�䴮��󳤶�

char pattern[MAX_PATTERN];//ģʽ��
int extend[MAX_PATTERN];//ģʽ����extend����

char match[MAX_MATCH];//ƥ�䴮
int Next[MAX_MATCH];//ƥ�䴮��next����

int len_pattern,len_match;//ģʽ�����ȣ�ƥ�䴮����

//��ȡģʽ����ƥ�䴮�ĳ��� 
void get_both_len(){
	len_pattern=strlen(pattern);
	len_match=strlen(match);
}

//�õ�Next���� 
void getnext(){
	Next[0]=len_match;//����λֱ�����

	int i=0,j=1;
	for(;j<len_match&&match[i]==match[j];i++,j++){}//�ҳ���ƥ�䴮�ĵ�1λ��ʼ��������0λ��ʼ�����ƥ�䳤��
	int pos_ini=1;//�õ����ƥ�䳤�ȵ���ʼλ��
	Next[pos_ini]=i;

	for(int k=2;k<len_match;++k)
	{
		if(Next[k-pos_ini]+k<pos_ini+Next[pos_ini]) Next[k]=Next[k-pos_ini];//����Ҫ����ƥ�伴�ɵ�next[k]
		else
		{
			int begin=Next[pos_ini]+pos_ini;//������ʱƥ������λ�ÿ�ʼ����ƥ��
			if(k>pos_ini+Next[pos_ini]-1) begin=k;//��k�ѳ���������ʱƥ������λ�á����ʹ�k����ʼƥ��

			i=0;
			for(;begin+i<len_match&&match[begin+i]==match[begin-k+i];++i){}
			Next[k]=begin-k+i;
			pos_ini=k;//���µõ����ƥ��λ�õ����
		}
	}
}

//�ṹ�뺯��getnext������ȫ��ͬ
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

//�������������ֱ��ִ�� 
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
