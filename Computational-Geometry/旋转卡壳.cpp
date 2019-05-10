// 旋转卡壳算法，O(n)
// 用于解决求多边形直径/平面最远点对
// 例题 poj-2187

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

const double PI = acos(-1.0);
const double eps = 1e-8;
const int N = 50000;

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

Point point[N + 10], stack[N + 10]; // 答案(半平面交的点)

double dist(Point a, Point b)
{
    return (a - b) * (a - b);
}

bool cmp(Point b, Point c)
{
    double cmp = (b.y - point[1].y) * (c.x - point[1].x) - (c.y - point[1].y) * (b.x - point[1].x);
    if (!cmp)
        return b.x < c.x;
    return cmp < 0;
}

int Graphm(Point a[], int n)
{
    int k = 1, num;
    for (int i = 2; i <= n; i++)
        if (a[i].y < a[k].y || (a[i].y == a[k].y && a[i].x < a[k].x))
            k = i;

    swap(a[1], a[k]);
    sort(a + 2, a + 1 + n, cmp);

    if (n == 1)
    {
        num = 1;
        stack[1] = a[1];
        return 1;
    }
    else if (n == 2)
    {
        num = 2;
        stack[1] = a[1], stack[2] = a[2];
        return 2;
    }
    else
    {
        stack[1] = a[1];
        stack[2] = a[2];
        num = 2;
        for (int i = 3; i <= n; i++)
        {
            while (num > 1 && sgn((stack[num] - stack[num - 1]) ^ (a[i] - stack[num - 1])) <= 0)
                num--;
            stack[++num] = a[i];
        }
        return num;
    }
}

double rotating_calipers(Point p[], int n)
{
    if (n == 2)
        return dist(p[0], p[1]);
    double ans = 0;
    Point v;
    int cur = 1;
    for (int i = 0; i < n; i++)
    {
        v = p[i] - p[(i + 1) % n];
        while (fabs(v ^ (p[cur] - p[(i + 1) % n])) < fabs(v ^ (p[(cur + 1) % n] - p[(i + 1) % n])))
            cur = (cur + 1) % n;
        ans = max(ans, max(dist(p[i], p[cur]), dist(p[i + 1], p[cur])));
    }
    return ans;
}

int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        for (int i = 1; i <= n; i++)
            scanf("%lf %lf", &point[i].x, &point[i].y);
        int num = Graphm(point, n);
        printf("%d\n", (int)rotating_calipers(stack + 1, num));
    }
}
