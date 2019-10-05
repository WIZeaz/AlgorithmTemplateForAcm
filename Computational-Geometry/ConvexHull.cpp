// 凸包，O(nlogn)
// 输入点跟点的个数，输出凸包点的个数

#include<bits/stdc++.h>
using namespace std;
#define ll long long

const double PI = acos(-1.0);
const double eps = 1e-8;
const int N = 50000;

inline int sgn(double x){
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	return 1;
}

struct Point{
	double x, y;
	Point(){};
	Point(double _x, double _y) : x(_x), y(_y){};
	Point operator+(const Point &a) const{
		return Point(x + a.x, y + a.y);
	}
	Point operator-(const Point &a) const{
		return Point(x - a.x, y - a.y);
	}
	double operator*(const Point &a) const{
		return x * a.x + y * a.y;
	}
	double operator^(const Point &a) const{
		return x * a.y - y * a.x;
	}
};

double dist(Point a, Point b){
	return sqrt((a - b) * (a - b));
}

Point a[N + 10], st[N + 10];

bool cmp(Point b, Point c){
	int cmp = sgn((b - a[1]) ^ (c - a[1]));
	if (cmp == 1) return true;
	if (cmp == 0 && sgn(dist(b, a[1]) - dist(c, a[1])) == -1) return true;
	return false;
}

int Graphm(Point a[], int n) {
	int k = 1, num;
	for (int i = 2; i <= n; i++)
		if (sgn(a[i].y - a[k].y) == -1 || (sgn(a[i].y - a[k].y) == 0 && sgn(a[i].x - a[k].x) == -1))
			k = i;

	swap(a[1], a[k]);
	sort(a + 2, a + 1 + n, cmp);

	if (n == 1){
		st[1] = a[1];
		return 1;
	}
	else if (n == 2){
		st[1] = a[1], st[2] = a[2];
		return 2;
	}
	else{
		st[1] = a[1], st[2] = a[2], num=2;
		for (int i = 3; i <= n; i++) {
			while (num > 1 && sgn((st[num] - st[num - 1]) ^ (a[i] - st[num - 1])) <= 0)
				num--;
			st[++num] = a[i];
		}
		return num;
	}
}