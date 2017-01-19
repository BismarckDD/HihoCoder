#include <cstdio>

#define max(a, b) (a>b?a:b)
int dp[1001][1001][2], n;
int sum[1001][1001];
int DFS(int i, int j, bool b)
{
    if (dp[i][j][b] == 0x3fffffff)
    {
        if (i == j) { dp[i][j][b] = sum[i][i]; return dp[i][j][b]; }
        dp[i][j][b] = max(sum[i][i] + sum[i + 1][j] - DFS(i + 1, j, !b), sum[j][j] + sum[i][j - 1] - DFS(i, j - 1, !b));
    }
    return dp[i][j][b];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 0; k <= 1; ++k)
                dp[i][j][k] = 0x3fffffff;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &sum[i][i]);
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            sum[i][j] = sum[i][j - 1] + sum[j][j];
    printf("%d\n", DFS(1, n, 0));
    return 0;
}