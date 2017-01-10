#include <cstdio>

#define maxn 1010
#define max(a, b) (a>b?a:b)
int n, m, q, w[maxn];
int dp[maxn][1025] = { 0 };

int countOnes(int num)
{
    int count = 0;
    while (num)
    {
        ++count;
        num = num & (num - 1);
    }
    return count;
}
int main()
{
    scanf("%d %d %d", &n, &m, &q);
    const int maxj = (1 << m) - 1;
    const int m2j = 1 << (m - 1);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &w[i]);
        dp[i][m2j] = w[i];
    }
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j <= maxj; ++j)
        {
            if (countOnes(j >> 1) < q)
                dp[i + 1][m2j | (j >> 1)] = max(dp[i][j] + w[i+1], dp[i + 1][m2j | (j >> 1)]);
            dp[i + 1][j >> 1] = max(dp[i][j], dp[i + 1][j >> 1]);
        }
    }
    int maxw = 0;
    for (int j = 0; j <= maxj; ++j)
        maxw = max(dp[n][j], maxw);
    printf("%d\n", maxw);
    return 0;
}