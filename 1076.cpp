#include <cstdio>
#include <cstring>
#define mod 1000000009
typedef long long ll;
int T, K, n;
ll dp[2][10010];
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &K, &n);
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i <= n && i <= K; ++i) dp[0][i] = 1;
        for (int i = 1; i <= 13; ++i)
        {
            memset(dp[i & 0x1], 0, sizeof(ll)*(n+1));
            for (int j = 0; j <= n; ++j)
            {
                int tmp = j;
                for (int t = 0; tmp <= n && t <= K; ++t, tmp = j + (1 << i) * t)
                {
                    dp[i & 0x1][tmp] += dp[(i + 1) & 0x1][j];
                    dp[i & 0x1][tmp] %= mod;
                }
                    
            }
        }
        printf("%lld\n", dp[1][n]);
    }
    return 0;
}