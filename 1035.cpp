#include <cstdio>
#include <cstring>
#define LLMAX ~(1LL<<63)
#define LLMIN (1LL<<63)
#define maxn 1000010
#define max(a, b) (a>b?a:b)
#define min(a, b) (a<b?a:b)

typedef long long ll;
int n, m, head[maxn] = { 0 }, cnt = 2;
bool vip[maxn] = { 0 };
ll dp[maxn][5] = { 0 };
struct EDGE
{
    int v, w1, w2, next;
}Edge[maxn<<1];
void AddEdge(int u, int v, int w1, int w2)
{
    Edge[cnt].next = head[u], Edge[cnt].v = v, Edge[cnt].w1 = w1, Edge[cnt].w2 = w2, head[u] = cnt++;
    Edge[cnt].next = head[v], Edge[cnt].v = u, Edge[cnt].w1 = w1, Edge[cnt].w2 = w2, head[v] = cnt++;
}

ll DFS2(int u, int fa, int s)
{
    if (dp[u][s] != -1) return dp[u][s];
    dp[u][0] = dp[u][1] = dp[u][2] = dp[u][3] = dp[u][4] = 0;
    ll t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0, t1s = 0, t2s = 0, cn = 0;
    ll t41 = 0, t42 = 0, t411 = LLMAX, t412 = 0, t421 = LLMAX, t422 = 0, t41key = -1, t42key = -2;
    for (int e = head[u]; e; e = Edge[e].next)
    {
        int v = Edge[e].v;
        if (v == fa) continue;
        DFS2(v, u, 0);
        if (!vip[v]) continue; else vip[u] |= vip[v];
        t0 = min(t0, dp[v][0] - Edge[e].w1 - dp[v][1]);
        t1 = (Edge[e].w1 << 1) + dp[v][1];
        t2 = min((Edge[e].w1 << 1) + dp[v][1], (Edge[e].w2 << 1) + dp[v][2]);
        t3 = min(t3, dp[v][3] + Edge[e].w1 + Edge[e].w2 - t2);
        t4 = min(t4, dp[v][0] + Edge[e].w1 - t2);
        t4 = min(t4, dp[v][4] + Edge[e].w2 - t2);
        t1s += t1, t2s += t2;
        t41 = Edge[e].w1 + Edge[e].w2 + dp[v][3] - t2;
        t42 = Edge[e].w1 + dp[v][0] - t2;
        if (t41 < t411) { t412 = t411, t411 = t41, t41key = v; }
        else t412 = min(t412, t41);
        if (t42 < t421) { t422 = t421, t421 = t42, t42key = v; }
        else t422 = min(t422, t42);
        ++cn;
    }
    if(cn>1) t4 = t41key == t42key ? min(min(t4, t412 + t421), min(t4, t411 + t422)) : min(t4, t411 + t421);
    dp[u][0] = t1s + t0;
    dp[u][1] = t1s;
    dp[u][2] = t2s;
    dp[u][3] = t2s + t3;
    dp[u][4] = t2s + t4;
    // dp[u][4] = min(dp[u][4], dp[u][3]);
    return dp[u][s];
}
int main()
{
    int u, v, w1, w2;
    //printf("%lld %lld\n", LLMAX, LLMIN);
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        scanf("%d %d %d %d", &u, &v, &w1, &w2);
        AddEdge(u, v, w1, w2);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &v);
        vip[v] = true;
    }
    memset(dp, -1, sizeof(dp));
    printf("%lld\n", min(DFS2(1, 0, 0), DFS2(1, 0, 4)));
    /* for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= 4; ++j)
            printf("%4lld%c", dp[i][j], j == 4 ? '\n' : ' ');
    } */
    return 0;
}