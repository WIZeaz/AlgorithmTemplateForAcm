/*
MO's Algorithm
离线算法
单次询问效率sqrt(n)
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
struct segment {
	int l, r, id;
	static int len;
	bool operator < (const segment& b) const{
		if (l / len != b.l / len) return l / segment::len < b.l / segment::len;
		else {
			//optimize 
			if ((l / len) & 1) return r < b.r; 
			else return r > b.r;
		}
	}
};
int a[30001]; //origin input data
segment query[200001]; //store the query
int ans[200001];  //store the answer
int num[1000001]; //update array
int segment::len = 1;
int main()
{
	int n,q;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	scanf("%d", &q);	
	segment::len = (int) sqrt(n); //length of block
	for (int i = 0; i < q; ++i) {
		scanf("%d%d", &query[i].l, &query[i].r);
		query[i].id = i;
	}
	//sort
	sort(query, query + q);
	int nowl, nowr, nowans;
	memset(num, 0, sizeof(num));
	nowl = 0;
	nowr = 0;
	nowans = 0;
	for (int i = 0; i < q; ++i) {
		//move to new query segment
		//l+1
		while (nowl < query[i].l) {
			--num[a[nowl]];
			if (num[a[nowl]] == 0) --nowans;
			++nowl;
		}
		//l-1
		while (nowl > query[i].l) {
			++num[a[nowl - 1]];
			if (num[a[nowl - 1]] == 1) ++nowans;
			--nowl;
		}
		//r+1
		while (nowr < query[i].r) {
			++num[a[nowr + 1]];
			if (num[a[nowr + 1]] == 1) ++nowans;
			++nowr;
		}
		//r-1
		while (nowr > query[i].r) {
			--num[a[nowr]];
			if (num[a[nowr]] == 0) --nowans;
			--nowr;
		}
		ans[query[i].id] = nowans;
	}
	for (int i = 0; i < q; ++i)
		printf("%d\n", ans[i]);
}