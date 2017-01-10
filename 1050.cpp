#include <cstdio>
#define maxn 100010
#define maxm 200010
int cnt = 2, n, head[maxn] = { 0 }, dep[maxn];

struct EDGE
{
    int u, v, next;
    EDGE() {}
} Edge[maxm];

void AddEdge(int u, int v)
{
    Edge[cnt].u = u; Edge[cnt].v = v;
    Edge[cnt].next = head[u]; head[u] = cnt++;
    Edge[cnt].u = v; Edge[cnt].v = u;
    Edge[cnt].next = head[v]; head[v] = cnt++;
}

void DFS(int u, int fa)
{
    for (int e = head[u]; e; e = Edge[e].next)
    {
        if (Edge[e].v != fa)
        {
            dep[Edge[e].v] = dep[u] + 1;
            DFS(Edge[e].v, u);
        }
    }
}

/* Therory: (a, b) is a longest path from a, assume (u, v) is the diameter of the tree,
            then, b must be either u or v. Then DFS twice will get the diameter.
Calculate the diameter of a tree: DFS twice.
    1 round DFS, select an arbitrary start point.
    2 round DFS, select the start point that has the max depth in the first round DFS.
*/
int main()
{
    int u, v, st, maxdep = 0;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        scanf("%d %d", &u, &v);
        AddEdge(u, v);
    }
    DFS(1, 0);
    for (int i = 1; i <= n; ++i) if (dep[i] > maxdep) { maxdep = dep[i]; st = i; }
    dep[st] = 0, maxdep = 0;
    DFS(st, 0);
    for (int i = 1; i <= n; ++i) if (dep[i] > maxdep) { maxdep = dep[i];}
    printf("%d\n", maxdep);
    return 0;
}
