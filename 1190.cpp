#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int MAXN = 20001;
const int MAXM = 200001;
int dfn[MAXN] = { 0 }, low[MAXN] = { 0 };
int stackEdge[MAXM], top = 0;
int id[MAXM >> 1], idn = 0;
int ecnt = 0, deep = 0, ecnt1 = 0, scc = 0;
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

void group(int &st)
{
    int temp = top;
    int t = 200001, ee;
    while(st!=temp)
    {
        ee = stackEdge[--temp];
        t = t < ee ? t : ee;
    }

    temp = top;
    while(st!=temp) 
    {
        ee = stackEdge[--temp];
        id[ee + 1] = t + 1;
    }
    top = st;
    ++idn;
}

void tarjan(int u, int fu)
{
    int v, children = 0, st;
    dfn[u] = low[u] = ++deep;
    for (int e = head[u]; e != -1; e = Edge[e].next)
    {
        v = Edge[e].v;
        if (!dfn[v])
        {
            st = top;
            ++children;
            stackEdge[top++] = e >> 1;
            //cout << top << "," << (e >> 1)+1 << ",a" << endl;
            tarjan(v, u);
            low[u] = low[u] < low[v] ? low[u] : low[v];
            if (dfn[u] <= low[v])
                group(st);

        }
        else if (dfn[v] < dfn[u] && v != fu) 
        {
            stackEdge[top++] = e >> 1;
            //cout << top << "," << (e >> 1)+1 <<",b"<< endl;
            low[u] = low[u] < dfn[v] ? low[u] : dfn[v];
        }
    }
}

int main()
{
    int n, m, a, b;
    memset(head, -1, sizeof(head));
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d %d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i, -1);
    printf("%d\n", idn);
    for (int i = 1; i <= m; ++i)
    {
        if (i != m)
            printf("%d ", id[i]);
        else
            printf("%d\n", id[i]);
    }
    return 0;
}
