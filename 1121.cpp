#include <cstdio>
#include <cstring>
#define maxn 10010
int T, n, m;
int color[maxn] = { 0 };
int head[maxn] = { 0 }, cnt = 0;
struct EDGE { int v, next; }Edge[maxn<<3];
void AddEdge(int u, int v)
{
    Edge[cnt].next = head[u], Edge[cnt].v = v, head[u] = cnt++;
    Edge[cnt].next = head[v], Edge[cnt].v = u, head[v] = cnt++;
}

bool DFS(int u, int c)
{
    bool flag = true;
    color[u] = c;
    for (int e = head[u]; e != -1 && flag; e = Edge[e].next)
    {
        int v = Edge[e].v;
        if (color[v] == color[u]) return false;
        if (color[v] != -1) continue;
        flag &= DFS(v, c ^ 0x1);
    }
    return flag;
}
int main()
{
    int u, v;
    scanf("%d", &T);
    while (T--)
    {
        memset(color, -1, sizeof(color));
        memset(head, -1, sizeof(head));
        cnt = 0;
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d %d", &u, &v);
            AddEdge(u, v);
        }
        bool flag = true;
        for(int i = 1; i <= n; ++i)
            if (color[i] == -1)
                flag &= DFS(i, 0);
        printf("%s\n", flag ? "Correct" : "Wrong");
        
    }
    return 0;
}
