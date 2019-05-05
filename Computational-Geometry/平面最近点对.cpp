// 求平面内最近的点对，O(nlognlogn)
// 分治算法
// 例题 poj-1007

// 输入n个点，输出最近距离

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

const double PI = acos(-1.0);
const double eps = 1e-8;
const double INF = 1e18;
const int N = 100010;

inline int sgn(double x)
{
    if (fabs(x) < eps)
        return 0;
    if (x < 0)
        return -1;
    return 1;
}

struct Point
{
    double x, y;
    Point(){};
    Point(double _x, double _y) : x(_x), y(_y){};
    Point operator+(const Point &a) const
    {
        return Point(x + a.x, y + a.y);
    }
    Point operator-(const Point &a) const
    {
        return Point(x - a.x, y - a.y);
    }
    double operator*(const Point &a) const
    {
        return x * a.x + y * a.y;
    }
    double operator^(const Point &a) const
    {
        return x * a.y - y * a.x;
    }
};

struct Line
{
    Point s, e;
    Line(){};
    Line(Point _s, Point _e)
    {
        s = _s, e = _e;
    }
    // 两直线相交   0代表重合  1代表平行  2代表相交
    pair<int, Point> operator&(const Line &a) const
    {
        Point res = s;
        if (sgn((s - e) ^ (a.s - a.e)) == 0)
        {
            if (sgn((s - a.e) ^ (a.s - a.e)) == 0)
                return make_pair(0, res);
            return make_pair(1, res);
        }
        double t = ((s - a.s) ^ (a.s - a.e)) / ((s - e) ^ (a.s - a.e));
        res.x += (e.x - s.x) * t;
        res.y += (e.y - s.y) * t;
        return make_pair(2, res);
    }
    // 两线段相交   0代表不相交  1代表相交（不穿过） 2代表相交（穿过） 3代表重合（有复数个交点）
    pair<int, Point> operator^(const Line &a) const
    {
        Point res = s;
        double cmp1 = sgn((a.s - s) ^ (a.e - s)) * sgn((a.s - e) ^ (a.e - e));
        double cmp2 = sgn((s - a.s) ^ (e - a.s)) * sgn((s - a.e) ^ (e - a.e));
        if (cmp1 == 1 || cmp2 == 1)
            return make_pair(0, res);

        if (sgn((a.s - a.e) ^ (s - e)) == 0)
            if (max(a.s.x, a.e.x) >= min(s.x, e.x) && max(s.x, e.x) >= min(a.s.x, a.e.x) &&
                max(a.s.y, a.e.y) >= min(s.y, e.y) && max(s.y, e.y) >= min(a.s.y, a.e.y))
                return make_pair(3, res);
            else
                return make_pair(0, res);

        double t = ((s - a.s) ^ (a.s - a.e)) / ((s - e) ^ (a.s - a.e));
        res.x += (e.x - s.x) * t;
        res.y += (e.y - s.y) * t;
        if (cmp1 + cmp2 == -2)
            return make_pair(2, res);
        else
            return make_pair(1, res);
    }
};
Point point[N + 10], cmp[N + 10];

double dist(Point a, Point b)
{
    return sqrt((a - b) * (a - b));
}

double getangle(Line a)
{
    return atan2(a.e.y - a.s.y, a.e.x - a.s.x);
}

bool cmpx(Point a, Point b)
{
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

bool cmpy(Point a, Point b)
{
    return a.y < b.y;
}

double nearest_point(int l, int r)
{
    if (l == r)
        return INF;
    else if (l + 1 == r)
        return dist(point[l], point[r]);

    int mid = (l + r) >> 1;
    double d1 = nearest_point(l, mid);
    double d2 = nearest_point(mid + 1, r);
    double d = min(d1, d2);

    int cnt = 0;
    for (int i = l; i <= r; i++)
        if (fabs(point[mid].x - point[i].x) <= d)
            cmp[++cnt] = point[i];
    sort(cmp + 1, cmp + 1 + cnt, cmpy);
    for (int i = 1; i <= cnt; i++)
        for (int o = i + 1; o <= cnt && cmp[o].y - cmp[i].y < d; o++)
            d = min(d, dist(cmp[i], cmp[o]));
    return d;
}

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        for (int i = 1; i <= n; i++)
            scanf("%lf %lf", &point[i].x, &point[i].y);

        sort(point + 1, point + 1 + n, cmpx);
        if (n == 1)
            printf("0.00\n");
        else
            printf("%.2lf\n", nearest_point(1, n) / 2);
    }
}
