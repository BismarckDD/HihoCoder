#include <cstdio>
#include <cstring>
#define maxn 1010
int s[maxn], s1[maxn], s2[maxn];
int n, size1, size2;

bool flag[500010];
int primes[41540];
int cnt, head[maxn], to[maxn], next[maxn];
void AddEdge(int u, int v) 
{
    to[cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt++;
}

int match[maxn];
bool used[maxn];
bool dfs(int u) 
{
    for (int i = head[u]; ~i; i = next[i])
    {
        int v = to[i];
        if (used[v]) continue;
        used[v] = true;
        if (match[v] == -1 || dfs(match[v])) 
        {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}

void div() 
{
    int tmp, cnt;
    for (int i = 1; i <= n; ++i) 
    {
        tmp = s[i], cnt = 0;
        for (int j = 0; primes[j] <= tmp; ++j)
        {
            while (tmp % primes[j] == 0) 
            {
                ++cnt;
                tmp /= primes[j];
            }
        }
        (cnt & 1) ? s1[size1++] = s[i] : s2[size2++] = s[i];
    }
}

void init() 
{
    size1 = size2 = 0;
    cnt = 0;
    memset(head, -1, sizeof(head));
    memset(match, -1, sizeof(match));
}

int main()
{
    for (int i = 2; i <= 708; ++i) 
        for (int j = i + i; j <= 500000; j += i) 
            flag[j] = true;
    for (int i = 2, cnt = 0; i <= 500000; i++)
        if (!flag[i]) primes[cnt++] = i;

    int T, Case = 1;
    scanf("%d", &T);
    while (T--)
    {
        init();
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &s[i]);
        div();
        for (int i = 0; i < size1; ++i) 
            for (int j = 0; j < size2; ++j) 
                if (s1[i] % s2[j] == 0 && !flag[s1[i] / s2[j]]) 
                    AddEdge(i, j);
                else if (s2[j] % s1[i] == 0 && !flag[s2[j] / s1[i]]) 
                    AddEdge(i, j);

        // Hungarian Algorithm to calculate max match
        int maxmatch = 0;
        for (int i = 0; i < size1; ++i) 
        {
            memset(used, 0, sizeof(used));
            if (dfs(i)) ++maxmatch;
        }
        printf("Case #%d: %d\n", Case++, n - maxmatch);
    }
   
    return 0;
}