#include <cstdio>
#include <cstring>
int T, n, k, a[301], cntC, cntV, Circle[301];
bool vis[301];
double dp[301][301], C[301][301];

void CalCombination()
{
    for (int i = 0; i <= 300; ++i)
    {
        C[i][0] = C[i][i] = 1.0;
        for (int j = 1; j < i; ++j)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
}
int main()
{
    CalCombination();
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; ++i) 
        {
            scanf("%d", &a[i]); 
            vis[i] = false;
        }
        cntC = 0, cntV = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (!vis[i])
            {
                ++cntC;
                int t = i;
                do
                {
                    vis[t] = true;
                    ++cntV;
                    t = a[t];
                } while (t != i);
                Circle[cntC] = cntV;
                cntV = 0;
            }
        }
        if (k < cntC)
        {
            printf("0.000000000\n");
            continue;
        }
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 1; i <= cntC; ++i)
            for (int j = 0; j < k; ++j)
            {
                if (dp[i - 1][j] > 0 ? dp[i - 1][j] < 0.000001 : dp[i - 1][j] > -0.000001) continue;
                for (int l = 1; l <= Circle[i] && j + l <= k; ++l)
                    dp[i][j + l] += dp[i - 1][j] * C[Circle[i]][l];
            }
                
        printf("%.9lf\n", dp[cntC][k] / C[n][k]);
    }
    return 0;
}