#include <cstdio>
#include <algorithm>
using namespace std;

#define maxn 100010
#define maxm 200010
#define maxlog 20
#define LL long long
#define max(a, b) (a>b?a:b)
#define min(a, b) (a<b?a:b)
int cnt = 2, n, m, head[maxn] = { 0 };
struct EDGE 
{
    int u, v, w, next;
    EDGE() {}
    EDGE(int _1, int _2, int _3, int _4) : u(_1), v(_2), w(_3), next(_4){}
} Edge[maxm];

void AddEdge(EDGE* Edge, int* head, int u, int v, int w) 
{
    Edge[cnt].u = u; Edge[cnt].v = v; Edge[cnt].w = w;
    Edge[cnt].next = head[u]; head[u] = cnt++;
    Edge[cnt].u = v; Edge[cnt].v = u; Edge[cnt].w = w;
    Edge[cnt].next = head[v]; head[v] = cnt++;
}

int dep[maxn], edoc, edo_inverse[maxm], extended_dfs_order[maxn];
int pdoc, pre_dfs_order[maxn], pro_dfs_order[maxn], pdo_inverse[maxn];
LL Dep[maxn], d;

void DFS(int u, int fa) 
{
    extended_dfs_order[u] = ++edoc; edo_inverse[edoc] = u;
    pre_dfs_order[u] = ++pdoc; pdo_inverse[pdoc] = u;
    // printf("%d: %d", u, pdoc);

    for (int e = head[u]; e; e = Edge[e].next)
    {
        if (Edge[e].v != fa)
        {
            dep[Edge[e].v] = dep[u] + 1;
            Dep[Edge[e].v] = Dep[u] + Edge[e].w;
            DFS(Edge[e].v, u);
            edo_inverse[++edoc] = u;
        }
    }
    pro_dfs_order[u] = pdoc;
}

int LCA[maxm][maxlog], Log[maxm];
void lca_init() 
{
    Log[0] = -1;
    for (int i = 1; i <= edoc; ++i)
    {
        LCA[i][0] = edo_inverse[i];
        Log[i] = Log[i >> 1] + 1;
    }
    for (int j = 1; (1 << j) <= edoc; ++j)
    {
        for (int i = 1; i + (1 << j) - 1 <= edoc; ++i)
        {
            int u = LCA[i][j - 1], v = LCA[i + (1 << j - 1)][j - 1];
            LCA[i][j] = (dep[u] < dep[v]) ? u : v;
        }
    }
}

int lca(int u, int v) 
{   /*extended_dfs_order vertex => extended dfs order, calculate lca under this*/
    int l = min(extended_dfs_order[u], extended_dfs_order[v]);
    int r = max(extended_dfs_order[u], extended_dfs_order[v]);
    int t = Log[r - l + 1];
    u = LCA[l][t]; v = LCA[r - (1 << t) + 1][t];
    return dep[u] < dep[v] ? u : v;
}

LL calc(int u, int v) 
{
    // printf("%d %d %d\n", u, v, Dep[u] + Dep[v] - (Dep[lca(u, v)] << 1));
    return Dep[u] + Dep[v] - (Dep[lca(u, v)] << 1);
}

struct NODE 
{
    bool enable;
    int A, B; LL Len;
    NODE() {}
    NODE(int _1, int _2, LL _3, bool _4) : A(_1), B(_2), Len(_3), enable(_4) {}
} Node[maxn << 2];

void update_distance(NODE& o, NODE lc, NODE rc) 
{
    o.Len = -1;
    if (!lc.enable && !rc.enable) { o.Len = 0; o.enable = false; return; }
    if (!lc.enable) { o = rc; return; }
    if (!rc.enable) { o = lc; return; }
    o.enable = true;
    if (o.Len < lc.Len) o.Len = lc.Len, o.A = lc.A, o.B = lc.B;
    if (o.Len < rc.Len) o.Len = rc.Len, o.A = rc.A, o.B = rc.B;
    d = calc(lc.A, rc.A);
    if (o.Len < d) o.Len = d, o.A = lc.A, o.B = rc.A;
    d = calc(lc.A, rc.B);
    if (o.Len < d) o.Len = d, o.A = lc.A, o.B = rc.B;
    d = calc(lc.B, rc.A);
    if (o.Len < d) o.Len = d, o.A = lc.B, o.B = rc.A;
    d = calc(lc.B, rc.B);
    if (o.Len < d) o.Len = d, o.A = lc.B, o.B = rc.B;
}

void build(int L, int R, int o) 
{
    if (L == R) Node[o] = NODE(pdo_inverse[L], pdo_inverse[R], 0, 1);
    else 
    {
        int M = L + R >> 1, lc = o << 1, rc = lc | 1;
        build(L, M, lc); build(M + 1, R, rc);
        update_distance(Node[o], Node[lc], Node[rc]);
        Node[o].enable = true;
    }
    // printf("%d seg[%d, %d]: %d %d %lld\n", o, L, R, Node[o].A, Node[o].B, Node[o].Len);
}

void update_status(int o, int L, int R, int ql, int qr, bool v) 
{
    if (ql <= L && R <= qr) Node[o].enable = v;
    else 
    {
        int M = L + R >> 1, lc = o << 1, rc = lc | 1;
        if (ql <= M) update_status(lc, L, M, ql, qr, v);
        if (qr > M) update_status(rc, M + 1, R, ql, qr, v);
        update_distance(Node[o], Node[lc], Node[rc]);
    }
}

NODE query(int o, int L, int R, int ql, int qr) 
{
    // if (ql > R || qr < L) return NODE(0, 0, -1, 0);
    if (ql <= L && R <= qr) return Node[o];
    int M = L + R >> 1, lc = o << 1, rc = lc | 1;
    NODE tmp1(0, 0, -1, 0), tmp2(0, 0, -1, 0), ans(0, 0, -1, 0);
    if (ql <= M) tmp1 = query(lc, L, M, ql, qr);
    if (qr > M)  tmp2 = query(rc, M + 1, R, ql, qr);
    update_distance(ans, tmp1, tmp2);
    //  printf("[%d, %d] %d %d %d %lld(%d)\nans: %lld\n", L, R, o, ql, qr, Node[o].Len, Node[o].enable, ans.Len);
    return ans;
}

bool cmp(int u, int v) { return extended_dfs_order[u] < extended_dfs_order[v]; }
int ps[maxn], cp, cpi, vis[maxn];
bool flag[maxn];

struct VTree 
{
    int head[maxn] = { 0 };
    EDGE Edge[maxm];
    LL dist[maxm], ans = 0;
    void clear() { cnt = 2, ans = 0; }

    void cal(int u, int fa) 
    {
        for (int e = head[u]; e; e = Edge[e].next) 
            if (Edge[e].v != fa)
                cal(Edge[e].v, u);
        if (flag[u]) 
        {
            NODE tmp = query(1, 1, n, pre_dfs_order[u], pro_dfs_order[u]); flag[u] = false;
            if (tmp.enable) ans += tmp.Len;
            //  printf("at %d tmp: %lld [%d, %d]\n", u, tmp.Len, pre_dfs_order[u], pro_dfs_order[u]);
            update_status(1, 1, n, pre_dfs_order[u], pro_dfs_order[u], 0);
        }
    }

    void rec(int u, int fa) 
    {
        for (int e = head[u]; e; e = Edge[e].next)
            if (Edge[e].v != fa)
                rec(Edge[e].v, u);
        update_status(1, 1, n, pre_dfs_order[u], pro_dfs_order[u], 1);
        head[u] = 0;
    }
} vt;

int main() 
{
    int u, v, w, q, _lca, cpi, cp, e;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) 
    {
        scanf("%d %d %d", &u, &v, &w);
        AddEdge(Edge, head, u, v, w);
    }
    DFS(1, 0);
    lca_init();
    /* printf("Edge:\n");
    // for (int i = 1; i < cnt; ++i) printf("%d %d %d\n", Edge[i].u, Edge[i].v, Edge[i].w);
    // printf("head:\n");
    // for (int i = 1; i <= n; ++i) printf("%d\n", head[i]);
    printf("edoc: %d\n", edoc);
    for(int i = 1; i <= edoc; ++i)
        for (int j = 0; j <= 3; ++j)
            printf("%d%c", LCA[i][j], j < 3 ? ' ' : '\n');
    printf("pre_dfs_order:\n");
    for (int i = 1; i <= n; ++i) printf("%d%c", pre_dfs_order[i], i < n ? ' ' : '\n');
    printf("pro_dfs_order:\n");
    for (int i = 1; i <= n; ++i) printf("%d%c", pro_dfs_order[i], i < n ? ' ' : '\n');
    printf("pdo_inverse:\n");
    for (int i = 1; i <= n; ++i) printf("%d%c", pdo_inverse[i], i < n ? ' ' : '\n');
    printf("extended_dfs_order:\n");
    for(int i = 1; i <= n; ++i) printf("%d%c", extended_dfs_order[i], i < n ? ' ' : '\n'); */
    build(1, n, 1);
    scanf("%d", &q);
    while (q--) 
    {
        scanf("%d", &cpi); 
        for (cp = 1; cp <= cpi; ++cp)
        {
            scanf("%d", &e);
            e = e << 1;
            u = dep[Edge[e].u] < dep[Edge[e].v] ? Edge[e].v : Edge[e].u;
            // printf("u:%d\n", u);
            ps[cp] = u;
            vis[u] = q + 1;
            flag[u] = true;
        }
        vis[1] = q + 1, ps[cp] = 1, flag[1] = true; ++cpi;
        // printf("cp:%d\n", cp);
        sort(ps + 1, ps + cpi + 1, cmp); /*sort according to dfs order*/
        for (int i = 1; i < cpi; ++i) 
        {
            _lca = lca(ps[i], ps[i + 1]);
            // printf("_lca:%d %d %d\n", psi[i], psi[i + 1], _lca);
            if (vis[_lca] != q + 1) vis[_lca] = q + 1, ps[++cp] = _lca;
        }
        // printf("cp:%d\n", cp);
        sort(ps + 1, ps + cp + 1, cmp);
        vt.clear();
        for (int i = 1; i < cp; ++i) 
        {
            u = ps[i], v = ps[i + 1], _lca = lca(u, v);
            // printf("_lca:%d %d %d\n", u, v, _lca);
            AddEdge(vt.Edge, vt.head, _lca, v, Dep[v] - Dep[_lca]);
        }

        // for (int i = 2; i < cnt; ++i) printf("%d %d %d\n", vt.Edge[i].u, vt.Edge[i].v, vt.Edge[i].w);
        vt.cal(1, 0);   // delete and calculate result.
        vt.rec(1, 0);  // recover the delete.
        printf("%lld\n", vt.ans);
    }
    return 0;
}
