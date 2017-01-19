#include <cstdio>

#define mod 1000000007
#define ll long long
int n, m;
ll ans = 0;
ll dp[101][101][101] = { 0 }; // current max value, sum, remains
int sum[101] = { 0 };
int GCD[101][101];
int gcd(int a, int b)
{
    if (a < b) a = a^b, b = a^b, a = a^b;
    if (!GCD[a][b])
    {
        if (b == 0) GCD[a][b] = a;
        else GCD[a][b] = gcd(b, a%b);
    }
    return GCD[a][b];
}

void dfs(int i, int sum, ll pro)
{
    if (sum == n)
    {
        if (pro % m == 0)
            ++ans;
        return;
    }
    for (int t = i + 1; t <= n - sum; ++t)
        dfs(t, sum + t, pro*t);
}

int main()
{
    scanf("%d %d", &n, &m);
    dp[0][0][m] = dp[1][1][m] = 1;
    for (int i = 1; i < n; ++i)
        sum[i] = sum[i - 1] + i;
    for (int i = 0; i <= 100; ++i)
    {
        GCD[i][0] = GCD[0][i] = i;
        GCD[i][1] = GCD[1][i] = 1;
    }
    for (int k = 2; k <= n; ++k) //t
        for (int i = 0; i + k <= n && i <= sum[k-1]; ++i) // sum
            for (int j = 1; j <= m; ++j) // remain
                for (int l = 0; l < k; ++l)
                    dp[k][i + k][j / gcd(j, k)] += dp[l][i][j];
        
    /* for (int i = 0; i <= n; ++i)
    {
        printf("Case:%d\n", i);
        for (int j = 0; j <= n; ++j)
        {
            for (int k = 1; k <= n; ++k)
                printf("%d ", dp[i][j][k]);
            printf("\n");
        }
        printf("\n\n\n");
    }*/
    // dfs(0, 0, 1);
    for (int i = 0; i <= n; ++i)
        ans += dp[i][n][1];
    printf("%d\n", ans%mod);
    return 0;
}