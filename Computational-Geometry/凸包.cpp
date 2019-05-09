// 凸包，O(nlogn)
// 输入点跟点的个数，输出凸包点的个数

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
#define ll long long

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

double dist(Point a, Point b)
{
    return sqrt((a - b) * (a - b));
}

Point a[N + 10], stack[N + 10];

bool cmp(Point b, Point c)
{
    double cmp = (b.y - a[1].y) * (c.x - a[1].x) - (c.y - a[1].y) * (b.x - a[1].x);
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

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &a[i].x, &a[i].y);
    int num = Graphm(a, n);

    double ans = 0;
    for (int i = 2; i < num; i++)
        ans += ((stack[i] - stack[1]) ^ (stack[i + 1] - stack[1])) / 2.0;
    int anss = ans / 50.0;
    printf("%d\n", anss);
}
