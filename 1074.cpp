#include<cstdio>
#include<algorithm>
#define maxn 100010
#define maxnlog 18
#define max(a, b) (a>b?a:b)
#define min(a, b) (a<b?a:b)
// LOG[max] => LOG[maxnlog] TLA*2 
int LOG[maxn], st_max[maxn][maxnlog], st_min[maxn][maxnlog];
int a[maxn], pos[maxn], rank[maxn], ans[maxn], cnt = 0, n;
void rmq_init()
{
    LOG[0] = -1;
    for (int i = 1; i <= n; ++i)
    {
        LOG[i] = LOG[i >> 1] + 1;
        st_max[i][0] = rank[i];
        st_min[i][0] = rank[i];
    }
    for (int j = 1; (1 << j) <= n; ++j)
    {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
        {
            st_max[i][j] = max(st_max[i][j - 1], st_max[i + (1 << j - 1)][j - 1]);
            st_min[i][j] = min(st_min[i][j - 1], st_min[i + (1 << j - 1)][j - 1]);
        }
    }
}

int rmq_max(int i, int j)
{
    int l = j - i + 1;
    int r = LOG[l];
    return max(st_max[i][r], st_max[j - (1 << r) + 1][r]);
}

int rmq_min(int i, int j)
{
    int l = j - i + 1;
    int r = LOG[l];
    return min(st_min[i][r], st_min[j - (1 << r) + 1][r]);
}

void func(int& st, int& ed, bool& leftright, bool& maxmin)
{
    if (st == ed) return;
    int m, p;
    m = maxmin ? rmq_max(st, ed) : rmq_min(st, ed);
    p = pos[m];
    ans[cnt++] = p;
    leftright ? ed = p : st = p;
    maxmin = !maxmin;
}

void func_helper(int st, int ed)
{
    int mmax = rmq_max(1, n);
    int mmin = rmq_min(1, n);
    int pos1 = pos[mmax];
    int pos2 = pos[mmin];
    ans[cnt++] = pos1;
    ans[cnt++] = pos2;
    bool flag1, flag2;
    if (pos1 < pos2)
    {
        flag1 = true, flag2 = false;
        while (st != pos1) func(st, pos1, flag1, flag2);
        flag1 = false, flag2 = true;
        while (ed != pos2) func(pos2, ed, flag1, flag2);
    }
    else
    {
        flag1 = false, flag2 = false;
        while (ed != pos1) func(pos1, ed, flag1, flag2);
        flag1 = true, flag2 = true;
        while (st != pos2) func(st, pos2, flag1, flag2);
    }
}

bool cmp(int i, int j)
{
    return a[i] < a[j];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        pos[i] = i;
    }
    std::sort(pos + 1, pos + n + 1, cmp);
    for (int i = 1; i <= n; ++i) rank[pos[i]] = i;
    rmq_init();
    /* for (int i = 1; i <= n; ++i)
        printf("%d %d %d\n", a[i], rank[i], pos[i]);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < maxnlog; ++j)
            printf("%d ", st_max[i][j]);
        printf("\n");
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < maxnlog; ++j)
            printf("%d ", st_min[i][j]);
        printf("\n");
    } */
    func_helper(1, n);
    std::sort(ans, ans + cnt);
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; ++i) printf("%d%c", ans[i], i < cnt - 1 ? ' ' : '\n');
    return 0;
}