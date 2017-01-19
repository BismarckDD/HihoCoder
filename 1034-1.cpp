#include <cstdio>

#define maxn 100010
#define MOD 1000000007
#define LL long long
#define ULL unsigned long long
int sum[maxn << 2], time[maxn << 2] = { 0 };
int n, m, maxm[maxn], rege[maxn];
int t, l, r;
LL ans = 0;

void build(int o, int L, int R)
{
    if (L == R) 
    {
        scanf("%d %d %d", &sum[o], &maxm[L], &rege[L]);
        return;
    }
    int M = (L + R) >> 1, lc = o << 1, rc = lc | 1;
    build(lc, L, M);
    build(rc, M + 1, R);
    sum[o] = sum[lc] + sum[rc];
}

void recover(int o, int L, int R, int l, int r, int tt)
{
    if (L == R && (l <= L && R <= r)) 
    {
        int temp = (tt - time[L])*rege[L];
        if (sum[o] + temp > maxm[L]) sum[o] = maxm[L];
        else sum[o] += temp;
        return;
    }
    int M = (L + R) >> 1, lc = o << 1, rc = lc | 1;
    if (l <= M) recover(lc, L, M, l, r, tt);
    if (r > M) recover(rc, M + 1, R, l, r, tt);
    sum[o] = sum[lc] + sum[rc];
}

LL query(int o, int L, int R, int l, int r)
{
    if (l <= L && R <= r) return sum[o];
    int M = (L + R) >> 1, lc = o << 1, rc = lc | 1;
    LL ans = 0;
    if (l <= M) ans += query(lc, L, M, l, r);
    if (r > M) ans += query(rc, M + 1, R, l, r);
    return ans;
}

void clear(int o, int L, int R, int l, int r, int tt)
{
    if (L == R && (l <= L && R <= r)) 
    {
        time[L] = tt;
        sum[o] = 0;
        return;
    }
    int M = (L + R) >> 1, lc = o << 1, rc = lc | 1;
    if (l <= M) clear(lc, L, M, l, r, tt);
    if (r > M) clear(rc, M + 1, R, l, r, tt);
    sum[o] = sum[lc] + sum[rc];
}

int main()
{
    scanf("%d", &n);
    build(1, 1, n);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) 
    {
        scanf("%d %d %d", &t, &l, &r);
        recover(1, 1, n, l, r, t);
        ans = (ans + query(1, 1, n, l, r)) % MOD;
        clear(1, 1, n, l, r, t);
    }
    printf("%lld\n", ans);
    return 0;
}
