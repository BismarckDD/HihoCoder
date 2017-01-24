#include <cstdio>
#include <cstring>
#define maxn 100010
int head[maxn] = { 0 }, cnt = 0, in[maxn] = { 0 }, queue[maxn];
struct EDGE { int v, next; }Edge[maxn << 3];
int T, n, m, ans;
void AddEdge(int u, int v)
{
    Edge[cnt].v = v, Edge[cnt].next = head[u], head[u] = cnt++;
}
void TopSort()
{
    int front = 0, rear = 0;
    ans = 0;
    for (int i = 1; i <= n; ++i) if (!in[i]) queue[rear++] = i;
    while (front != rear)
    {
        int u = queue[front++];
        ++ans;
        for (int e = head[u]; e != -1; e = Edge[e].next)
        {
            int v = Edge[e].v;
            --in[v];
            if (!in[v]) queue[rear++] = v;
        }
    }
}
int main()
{
    int u, v;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &n, &m);
        memset(head, -1, sizeof(head));
        memset(in, 0, sizeof(in));
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d %d", &u, &v);
            AddEdge(u, v);
            ++in[v];
        }
        TopSort();
        printf("%s\n", ans == n ? "Correct" : "Wrong");
    }
    return 0;
}