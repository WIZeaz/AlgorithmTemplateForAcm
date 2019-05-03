// 半平面交算法，O(nlogn)
// 用于解决求多边形的核的问题
// 求多边形内的区域，使得从区域内的任意一点都可看到该多边形的任意一点
// 即连线线段在该多边形的内部
// 例题 poj-3335

// 输入n个按顺序的点，输出其半平面交

const double PI = acos(-1.0);
const double eps = 1e-8;
const int N = 200;

Point point[N + 10]; // 答案(半平面交的点)
Line line[N + 10], q[2 * N + 10];
int n, ans; // 半平面交点的个数

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
    for (int i = l; i < r; i++)
        point[i] = (q[i] & q[i + 1]).second;
    point[r] = (q[l] & q[r]).second;
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
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
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
            printf("YES\n");
        else
            printf("NO\n");
    }
}
