#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 20001;
const int MAXM = 200001;
int dfn[MAXN] = { 0 }, low[MAXN] = { 0 };
int ecnt = 0, deep = 0;
int cutEdge = 0, cutVertex = 0;
pair<int, int> CutEdge[MAXM];
int CutVertex[MAXN];
bool vis[MAXN] = { false };
struct EDGE
{
    int v, next;
    EDGE() { v = next = 0; }
};
EDGE Edge[MAXM];
int head[MAXN];
void addEdge(int u, int v)
{
    Edge[ecnt].v = v;
    Edge[ecnt].next = head[u];
    head[u] = ecnt++;
}

void tarjan(int u, int fu) //Directed Edge Strong Connected Component
{
    int v,children = 0;
    dfn[u] = low[u] = ++deep;
    for (int e = head[u]; e != -1; e = Edge[e].next)
    {
        v = Edge[e].v;
        if (!dfn[v])
        {
            ++children;
            tarjan(v, u);
            low[u] = low[u] < low[v] ? low[u] : low[v];
            if (fu == -1 && children > 1 && !vis[u])
                CutVertex[cutVertex++] = u, vis[u] = true;
            if (fu != -1 && dfn[u] <= low[v] && !vis[u])
                CutVertex[cutVertex++] = u, vis[u] = true;
            if (dfn[u] < low[v])
                CutEdge[cutEdge++] = u < v ? pair<int, int>(u, v) : pair<int, int>(v, u);

        }
        else if ( v != fu) //Directed Graph must judge instack, Undirected Graph must judge father
            low[u] = low[u] < dfn[v] ? low[u] : dfn[v];
    }
}
bool cmp(pair<int, int> a, pair<int, int> b)
{
    if (a.first == b.first)
        return a.second < b.second;
    else
        return a.first < b.first;
}
int main()
{
    int n, m, a, b;
    memset(head, -1, sizeof(head));
    scanf("%d %d", &n, &m);
    while(m--)
    {
        scanf("%d %d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i, -1);
    sort(CutVertex, CutVertex + cutVertex);
    sort(CutEdge, CutEdge + cutEdge, cmp);
    if (cutVertex == 0)
        printf("Null\n");
    else
    {
        for (int i = 0; i < cutVertex; ++i)
            if (i != cutVertex - 1)
                printf("%d ", CutVertex[i]);
            else
                printf("%d\n", CutVertex[i]);
    }
    for (int i = 0; i < cutEdge; ++i)
        printf("%d %d\n", CutEdge[i].first, CutEdge[i].second);
    return 0;
}
