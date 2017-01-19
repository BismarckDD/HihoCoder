#include <cstdio>
#include <cstring>
#define maxn 1010
#define maxm 100010
#define mod 1000000007
#define LL long long
int n, m, x, y, k, x1, y1;
LL TreeArrayD[maxn][maxn] = { 0 };
char str[5];
int lowbit(int x)
{
    return x & (-x);
}

void AddNum(int x, int y, int k)
{
    ++x, ++y;
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
            TreeArrayD[i][j] += k;
}

LL GetSum(int x, int y)
{
    ++x, ++y;
    LL ans = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            ans += TreeArrayD[i][j];
    return ans;
}

int main()
{
    scanf("%d %d %d", &n, &m);
    while (m--)
    {
        scanf("%s", str);
        if (strcmp(str, "Add") == 0)
        {
            scanf("%d %d %d", &x, &y, &k);
            AddNum(x, y, k);
        }
        else
        {
            scanf("%d %d %d %d", &x, &y, &x1, &y1);
            LL ans = 0;
            ans += (GetSum(x1, y1) + GetSum(x-1, y-1));
            ans -= (GetSum(x-1, y1) + GetSum(x1, y-1));
            ans = ((ans % mod) + mod) % mod;
            printf("%d\n", ans);
        }
    }
    return 0;
}
