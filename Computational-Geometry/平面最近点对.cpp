// 求平面内最近的点对，O(nlognlogn)
// 分治算法
// 例题 poj-1007

// 输入n个点，输出最近距离

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
