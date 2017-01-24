#include <cstdio>
#include <cstring>
#define maxn 1010
int T, n, m;
bool vis[maxn] = { 0 };
int head[maxn] = { 0 }, match[maxn], cnt = 0, ans;
struct EDGE { int v, next; }Edge[maxn << 4];
void AddEdge(int u, int v)
{
    Edge[cnt].next = head[u], Edge[cnt].v = v, head[u] = cnt++;
    Edge[cnt].next = head[v], Edge[cnt].v = u, head[v] = cnt++;
}

bool DFS(int u)
{
    for (int e = head[u]; e != -1; e = Edge[e].next)
    {
        int v = Edge[e].v;
        if (vis[v]) continue;
        vis[v] = true;
        if (!match[v] || DFS(match[v]))
        {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

int Hungarian()
{
    int ans = 0;
    memset(match, 0, sizeof(match));
    for (int i = 1; i <= n; ++i)
    {
        if (!match[i])
        {
            memset(vis, 0, sizeof(vis));
            if (DFS(i)) ++ans;
        }
    }
    return ans;
}
int main()
{
    int u, v;
    memset(match, 0, sizeof(match));
    memset(head, -1, sizeof(head));
    cnt = 0;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d %d", &u, &v);
        AddEdge(u, v);
    }
    printf("%d\n", Hungarian());
    return 0;
}

int q[maxn], prev[maxn], front = 0, rear = 0;

int HungarianBFS()
{
    int ans = 0;
    memset(match, 0, sizeof(match));
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; ++i)
    {
        if (!match[i])
        {
            while(front != rear) ++front;
            q[rear++] = i;
            prev[i] = -1;
            bool flag = false;
            while (front != rear && !flag)
            {
                int u = q[front++];
                for (int e = head[u]; e != -1 && !flag; e = Edge[e].next)
                {
                    int v = Edge[e].v;
                    if (vis[v]) continue;
                    vis[v] = true;
                    q[front++] = match[v];
                    if (match[v]) prev[match[v]] = u;
                    else
                    {
                        flag = true;
                        int d = u, e = v;
                        while (d != -1)
                        {
                            int t = match[d];
                            match[d] = e;
                            match[e] = d;
                            d = prev[d];
                            e = t;
                        }
                    }
                }
            }
            if(match[i]) ++ans;
        }
    }
    return ans;
}
