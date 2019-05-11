// 半平面交算法，O(nlogn)
// 用于解决求多边形的核的问题
// 也可解决多边形面积交的问题，将多边形拆成边，求半平面交即可
// 求多边形内的区域，使得从区域内的任意一点都可看到该多边形的任意一点
// 即连线线段在该多边形的内部
// 例题 poj-3335

// 输入n个按顺序的点，输出其半平面交

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

const double PI = acos(-1.0);
const double eps = 1e-8;
const int N = 200;

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
Point point[N + 10]; // 答案(半平面交的点)
Line line[N + 10], q[2 * N + 10];
int n, ans; // 半平面交点的个数

double dist(Point a, Point b)
{
    return sqrt((a - b) * (a - b));
}

double getangle(Line a)
{
    return atan2(a.e.y - a.s.y, a.e.x - a.s.x);
}

bool cmp(Line a, Line b)
{
    double A = getangle(a), B = getangle(b);
    if (sgn(A - B) == 0)
        return sgn((a.e - a.s) ^ (b.e - a.s)) > 0;
    return sgn(A - B) == -1;
}

void halfplane()
{
    ans = -1;
    sort(line + 1, line + 1 + n, cmp);
    int cnt = 0;
    for (int i = 1; i < n; i++)
        if (sgn(getangle(line[i]) - getangle(line[i + 1])))
            line[++cnt] = line[i];
    line[++cnt] = line[n];
    int l = 1, r = 0;
    for (int i = 1; i <= cnt; i++)
    {
        while (l < r && sgn(((q[r] & q[r - 1]).second - line[i].s) ^ (line[i].e - line[i].s)) == 1)
            r--;
        while (l < r && sgn(((q[l] & q[l + 1]).second - line[i].s) ^ (line[i].e - line[i].s)) == 1)
            l++;
        q[++r] = line[i];
    }
    while (l < r && sgn(((q[r] & q[r - 1]).second - q[l].s) ^ (q[l].e - q[l].s)) == 1)
        r--;
    while (l < r && sgn(((q[l] & q[l + 1]).second - q[r].s) ^ (q[r].e - q[r].s)) == 1)
        l++;

    if (r - l <= 1)
        return;
    for (int i = l, o = 1; i < r; i++, o++)
        point[o] = (q[i] & q[i + 1]).second;
    point[r - l + 1] = (q[l] & q[r]).second;
    ans = r - l + 1;
}

// 判断点的顺序，计算面积<0，则顺序为逆时针时返回true
bool judge()
{
    double pend = 0;
    for (int i = 2; i < n; i++)
    {
        pend += ((point[i] - point[1]) ^ (point[i + 1] - point[1]));
    }
    return pend < 0;
}

int main()
{
    while (scanf("%d", &n) && n)
    {
        for (int i = 1; i <= n; i++)
            scanf("%lf%lf", &point[i].x, &point[i].y);
        if (judge())
        {
            for (int i = 1; i < n; i++)
                line[i] = Line(point[i + 1], point[i]);
            line[n] = Line(point[1], point[n]);
        }
        else
        {
            for (int i = 1; i < n; i++)
                line[i] = Line(point[i], point[i + 1]);
            line[n] = Line(point[n], point[1]);
        }

        halfplane();
        if (ans != -1)
            printf("1\n");
        else
            printf("0\n");
    }
}
