#include <cstdio>

#define maxn 110
#define maxm 210
#define loglen 9
#define max(a, b) (a>b?a:b)
#define min(a, b) (a<b?a:b)
int head[maxn] = { 0 }, cnt = 2, n, m;
int seq[maxn], inorder[maxm], dfsorder[maxn], clo = 0, dep[maxn] = { 0 };
int LOG[maxm], st[maxm][loglen];

void lca_init()
{
    LOG[0] = -1;
    for (int i = 1; i <= clo; ++i) st[i][0] = inorder[i], LOG[i] = LOG[i >> 1] + 1;
    for (int j = 1; (1<<j) <= clo; ++j)
        for (int i = 1; i + (1 << (j - 1)) - 1 <= clo; ++i)
            st[i][j] = dep[st[i][j - 1]] < dep[st[i + (1 << (j - 1))][j - 1]] ?
                        st[i][j - 1] :
                        st[i + (1 << (j - 1))][j - 1];
    /* for (int i = 1; i <= clo; ++i)
    {
        for (int j = 0; j < loglen; ++j)
            printf("%d ", st[i][j]);
        printf("\n");
    } */
}

int lca(int i, int j)
{
    int a = min(dfsorder[i], dfsorder[j]);
    int b = max(dfsorder[i], dfsorder[j]);
    int l = b - a + 1;
    int logl = LOG[l];
    return dep[st[a][logl]] < dep[st[b - (1 << logl) + 1][logl]] ? 
                st[a][logl] : 
                st[b - (1 << logl) + 1][logl];
}
struct EDGE
{
    int v, next;
} Edge[maxm];
void AddEdge(int u, int v)
{
    Edge[cnt].v = v, Edge[cnt].next = head[u], head[u] = cnt++;
    Edge[cnt].v = u, Edge[cnt].next = head[v], head[v] = cnt++;
}
void DFS(int u, int fa)
{
    inorder[++clo] = u; dfsorder[u] = clo;
    dep[u] = dep[fa] + 1;
    for (int e = head[u]; e; e = Edge[e].next)
    {
        if (Edge[e].v != fa)
        {
            DFS(Edge[e].v, u);
            inorder[++clo] = u;
        }
    }
}
int main()
{
    int T, u, v;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        clo = 0, cnt = 2, dep[0] = 0;
        for (int i = 1; i <= n; ++i) head[i] = 0;
        for (int i = 1; i < n; ++i) scanf("%d %d", &u, &v), AddEdge(u, v);
        scanf("%d", &m);
        for (int i = 1; i <= m; ++i) scanf("%d", &seq[i]);
        DFS(1, 0);
        lca_init();
        // for (int i = 1; i <= n; ++i) printf("%d%c", dfsorder[i], i == n ? '\n' : ' ');
        bool flag = true;
        for (int i = 1; i <= m - 1 && flag; ++i)
        {
            int pp = -1;
            for (int j = i + 1; j <= m && flag; ++j)
            {
                //printf("%d %d %d\n", seq[i], seq[j], lca(seq[i], seq[j]));
                int tlca = lca(seq[i], seq[j]);
                if (tlca == seq[j]) { flag = false; break; }
                if (pp == -1)
                {
                    pp = tlca;
                }
                else if (pp != tlca)
                {
                    if (lca(pp, tlca) != tlca) { flag = false; break; }
                    pp = tlca;
                }
            }
        }
        printf("%s\n", flag ? "YES" : "NO");
    }
    return 0;
}