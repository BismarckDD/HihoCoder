#include <cstdio>

double dp[101][601] = { 0 };
int n, m;
double p = (double)1 / (double)6;
int main()
{
    dp[1][1] = dp[1][2] = dp[1][3] = dp[1][4] = dp[1][5] = dp[1][6] = p;
    scanf("%d %d", &n, &m);
    for (int i = 2; i <= n; ++i)
        for (int j = i; j <= 6 * i; ++j)
        {
            int s = j - 6 >= 1 ? j - 6 : 1;
            int t = j - 1 >= 6 * (i - 1) ? 6 * (i - 1) : j - 1;
            for (; s <= t; ++s)
                dp[i][j] += dp[i - 1][s] * p; 
        }
    printf("%.2lf\n", dp[n][m] * 100);
    return 0;
}