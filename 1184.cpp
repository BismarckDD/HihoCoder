#include<cstdio>
#include<iostream>
using namespace std;
const int MAXN = 20001;
const int MAXM = 200001;
int dfn[MAXN] = { 0 }, low[MAXN] = { 0 }, group[MAXN] = { 0 };
int stack[MAXN], top = 0;
int ecnt = 0, deep = 0;
int bridgeCnt = 0;
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

void tarjan(int u, int fu) //Undirected Edge BiConnected Component
{
    int v;
    dfn[u] = low[u] = ++deep;
    stack[++top] = u;
    for (int e = head[u]; e != -1; e = Edge[e].next) 
    {
        v = Edge[e].v;
        if (v == fu) continue;
        if (!dfn[v]) 
        {
            tarjan(v, u);
            low[u] = low[u] < low[v] ? low[u] : low[v];
            if (dfn[u] < low[v]) 
            {
                ++bridgeCnt;
            }
        }
        else 
            low[u] = low[u] < dfn[v] ? low[u] : dfn[v];
    }

    if (low[u] == dfn[u])
    {
        int temp = top, minu = u;
        do {
            minu = stack[temp] < minu ? stack[temp] : minu;
        } while (u != stack[temp--] && temp!=0);
        do {
            v = stack[top--];
            group[v] = minu;
        } while (top!=0 && u != v);
    }
}

int main()
{
    int n, m, a, b;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        group[i] = i;
        head[i] = -1;
    }
    while(m--)
    {
        scanf("%d %d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    tarjan(1, 1);
    printf("%d\n", bridgeCnt+1);
    for (int i = 1; i <= n; ++i)
        if (i != n)
            printf("%d ", group[i]);
        else
            printf("%d\n", group[i]);
    return 0;
}
