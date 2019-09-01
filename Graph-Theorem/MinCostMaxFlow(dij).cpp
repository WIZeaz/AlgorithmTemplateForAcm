// hdu6611  2019多校第三场I
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 5020;
const int MAXM = 200010;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> pii;
struct edge
{
    int to, cap, cost, rev; // rev为反向边
    edge(){};
    edge(int _to, int _cap, int _cost, int _rev) : to(_to), cap(_cap), cost(_cost), rev(_rev){};
};
int N; // 顶点数
vector<edge> G[MAXN];
int dist[MAXN], h[MAXN];
int prevv[MAXN], preve[MAXN];

void init(int n)
{
    N = n;
    for (int i = 0; i <= N; i++)
        G[i].clear();
}

void addedge(int from, int to, int cap, int cost)
{
    G[from].push_back(edge(to, cap, cost, G[to].size()));
    G[to].push_back(edge(from, 0, -cost, G[from].size() - 1));
}

// 求s到t流量为f的最小费用流
// 不能再增广时返回-1
int MinCost(int s, int t, int &f)
{
    int res = 0;
    fill(h, h + N + 1, 0);
    while (f > 0)
    {
        priority_queue<pii, vector<pii>, greater<pii>> que;
        fill(dist, dist + N + 1, INF);
        dist[s] = 0;
        que.push(make_pair(0, s));
        while (!que.empty())
        {
            pii p = que.top();
            que.pop();
            int v = p.second;
            if (dist[v] < p.first)
                continue;
            for (int i = 0; i < G[v].size(); i++)
            {
                edge &e = G[v][i];
                if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to])
                {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v, preve[e.to] = i;
                    que.push(make_pair(dist[e.to], e.to));
                }
            }
        }

        if (dist[t] == INF)
            return -1;

        for (int v = 1; v <= N; v++)
            h[v] += dist[v];

        int d = f;
        for (int v = t; v != s; v = prevv[v])
            d = min(d, G[prevv[v]][preve[v]].cap);
        f -= d;
        res += d * h[t];
        for (int v = t; v != s; v = prevv[v])
        {
            edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}

int main()
{
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    init(n);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w, c;
        scanf("%d%d%d%d", &u, &v, &w, &c);
        addedge(u, v, w, c);
    }

    int f = 1e9;
    int ans = MinCost(s, t, f);
    f = 1e9 - f;
    printf("%d %d\n", f, ans);
}
