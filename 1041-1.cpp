#include <cstdio>
#include <bitset>
using namespace std;

#define maxn 110
bitset<maxn> map[maxn];
bitset<maxn> sub[maxn];
bitset<maxn> vis;
int n, m, seq[maxn], t;
bool flag = true;
void PREDFS(int u, int fa)
{
    sub[u][u] = true;
    for (int i = 1; i <= n; ++i)
    {
        if (map[u][i] && i != fa)
        {
            PREDFS(i, u);
            sub[u] |= sub[i];
        }
    }
}

void DFS(int u, int fa)
{
    vis[u] = true;
    if (u == seq[t]) ++t;
    if (t == m + 1)
    {
        flag = true;
        return;
    }
    while (t <= m && !flag)
    {
        int tmp = t;
        for (int i = 1; i < map[u].size() && !flag; ++i)
        {
            if (map[u][i] && sub[i][seq[t]] && !vis[i])
            {
                DFS(i, u);
                break;
            }
        }
        if (tmp == t) break;
    }
}

int main() 
{
    int T, u, v;

    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 0; i <= n; ++i)
        {
            map[i].reset();
            sub[i].reset();
        }
        vis.reset();
        for (int i = 1; i < n; ++i)
        {
            scanf("%d %d", &u, &v);
            map[u][v] = true;
            map[v][u] = true;
        }
        scanf("%d", &m);
        for (int i = 1; i <= m; ++i) scanf("%d", &seq[i]);
        PREDFS(1, 0);
        flag = false;
        t = 1;
        DFS(1, 0);
        printf("%s\n", flag ? "YES" : "NO");
    }
    return 0;
}