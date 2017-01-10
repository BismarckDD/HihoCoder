#include <cstdio>
#include <cstring>
const int MAXN = 100001;
int head[MAXN], dis[MAXN], dep[MAXN], seq[MAXN << 1], fap[MAXN]; 
int cnt, cntSeq, n, m, u, v, w;

struct EDGE
{
    int v, w, next;
} Edge[MAXN<<1];

void AddEdge(int u, int v, int w)
{
    Edge[cnt].next = head[u];
    Edge[cnt].v = v;
    Edge[cnt].w = w;
    head[u] = cnt++;
    Edge[cnt].next = head[v];
    Edge[cnt].v = u;
    Edge[cnt].w = w;
    head[v] = cnt++;
}

void init()
{
    cnt = cntSeq = 0;
    memset(head, -1, sizeof(head));
}

void DFS(int u, int p)
{
    seq[cntSeq++] = u;
    for (int e = head[u]; e != -1; e = Edge[e].next)
    {
        if (Edge[e].v != p) 
        {
            dis[Edge[e].v] = dis[u] + Edge[e].w;
            DFS(Edge[e].v, u);
        }
    }
}

int findMaxDis(int& d)
{
    int kv = 0;
    d = 0;
    for (int i = 1; i <= n; ++i)
    {
        printf(" %d", dis[i]);
        if (d < dis[i])
        {
            d = dis[i];
            kv = i;
        }
    }
    printf("\n");
    return kv;
}

/*int main()
{
    init();
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        scanf("%d %d %d", &u, &v, &w);
        AddEdge(u, v, w);
    }
    dis[1] = 0, DFS(1, -1);
    int kv, d;
    kv = findMaxDis(d);
    dis[kv] = 0, DFS(kv, -1);
    kv = findMaxDis(d);
    printf("%d %d\n", kv, d);
    return 0;
}*/
