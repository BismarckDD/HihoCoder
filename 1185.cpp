#include<cstdio>
#include<iostream>
#include<set>
#include<cstring>
using namespace std;
const int MAXN = 20001;
const int MAXM = 200001;
int dfn[MAXN] = { 0 }, low[MAXN] = { 0 }, group[MAXN] = { 0 }, weight[MAXN] = { 0 };
int stack[MAXN], top = 0;
bool instack[MAXN] = { false };
int ecnt = 0, deep = 0, ecnt1 = 0, scc = 0;
long long ans = 0, num[MAXN] = { 0 };
struct EDGE
{
    int v, next;
    EDGE() { v = next = 0; }
};
EDGE Edge[MAXM],Edge1[MAXN];
int head[MAXN],head1[MAXN];
void addEdge(int u, int v)
{
    Edge[ecnt].v = v;
    Edge[ecnt].next = head[u];
    head[u] = ecnt++;
}
void addEdge1(int u, int v)
{
    Edge1[ecnt1].v = v;
    Edge1[ecnt1].next = head1[u];
    head1[u] = ecnt1++;
}
void tarjan(int u, int fu) //Directed Edge Strong Connected Component
{
    int v;
    group[u] = u;
    dfn[u] = low[u] = ++deep;
    stack[++top] = u;
    instack[u] = true;
    for (int e = head[u]; e != -1; e = Edge[e].next)
    {
        v = Edge[e].v;
        //if (v == fu) continue; //Undirected Graph must judge father
        if (!dfn[v])
        {
            tarjan(v, u);
            low[u] = low[u] < low[v] ? low[u] : low[v];
        }
        else if (instack[v]) //Directed Graph must judge instack
            low[u] = low[u] < dfn[v] ? low[u] : dfn[v];
    }

    if (dfn[u] == low[u])
    {
        ++scc;
        do {
            v = stack[top--];
            instack[v] = false;
            group[v] = scc;
            num[scc] += weight[v];
        } while (top!= 0 && u != v);
    }
}

void rebuild(int n)
{
    int u, v;
    set<pair<int, int>> s;
    for (int i = 1; i <= n; i++)
    {
        u = group[i];
        for (int e = head[i]; e != -1; e = Edge[e].next)
        {
            v = Edge[e].v;
            v = group[v];
            if (u != v && s.find(pair<int, int>(u, v)) == s.end())
            {
                //printf("%d %d\n", u, v);
                addEdge1(u, v);
                s.insert(pair<int, int>(u, v));
            }
        }
    }
}

void dfs(int u, long long now)
{
    if (ans < now) ans = now;
    for (int e = head1[u]; e != -1; e = Edge1[e].next)
    {
        int v = Edge1[e].v;
        //printf("%d\n", v);
        dfs(v, now + num[v]);
    }
}

int main()
{
    int n, m, a, b;
    memset(head, -1, sizeof(head));
    memset(head1, -1, sizeof(head1));
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &weight[i]);
    while(m--)
    {
        scanf("%d %d", &a, &b);
        addEdge(a, b);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i, -1);

    rebuild(n);
    dfs(group[1],num[group[1]]);
    printf("%lld\n", ans);
    return 0;
}
