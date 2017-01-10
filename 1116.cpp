#include <cstdio>

#define maxn 100010
#define mod 10007
int n, q, a, b;

int sum[maxn << 2] = { 0 }, pre[maxn << 2] = { 0 }, suf[maxn << 2] = { 0 }, mul[maxn << 2] = { 0 };

void update(int o, int L, int R, int a, int b)
{
    if (L == R)
    {
        sum[o] = mul[o] = pre[o] = suf[o] = b % mod;
        return;
    }
    int M = L + R >> 1, lc = o << 1, rc = lc | 1;
    if (a <= M) update(lc, L, M, a, b);
    else update(rc, M + 1, R, a, b);
    mul[o] = mul[lc] * mul[rc] % mod;
    pre[o] = (pre[lc] + mul[lc] * pre[rc]) % mod;
    suf[o] = (suf[lc] * mul[rc] + suf[rc]) % mod;
    sum[o] = (sum[lc] + sum[rc] + suf[lc] * pre[rc]) % mod;
}

int main()
{
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= q; ++i)
    {
        scanf("%d %d", &a, &b);
        update(1, 1, n, a, b);
        printf("%d\n", sum[1]);
    }
    return 0;
}