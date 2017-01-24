#include <cstdio>
#include <cstring>
#define maxn 100010
#define mod 142857
int head[maxn], cnt = 0, in[maxn], sum[maxn], queue[maxn];
struct EDGE { int v, next; }Edge[maxn << 3];
int n, m, K, ans;
void AddEdge(int u, int v)
{
    Edge[cnt].v = v, Edge[cnt].next = head[u], head[u] = cnt++;
}
void TopSort()
{
    int front = 0, rear = 0;
    for (int i = 1; i <= n; ++i) if (!in[i]) queue[rear++] = i;
    while (front != rear)
    {
        int u = queue[front++];
        for (int e = head[u]; e != -1; e = Edge[e].next)
        {
            int v = Edge[e].v;
            sum[v] += sum[u];
            sum[v] %= mod;
            --in[v];
            if (!in[v]) queue[rear++] = v;
        }
    }
}
int main()
{
    int u, v, t;
    scanf("%d %d %d", &n, &m, &K);
    memset(head, -1, sizeof(head));
    memset(in, 0, sizeof(in));
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= K; ++i)
    {
        scanf("%d", &t);
        sum[t] = 1;
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d %d", &u, &v);
        AddEdge(u, v);
        ++in[v];
    }
    TopSort();
    for (int i = 1; i <= n; ++i)
    {
        ans += sum[i];
        ans %= mod;
    }
    printf("%d\n", ans);
    return 0;
}