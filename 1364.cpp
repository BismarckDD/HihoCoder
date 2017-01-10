#include<cstdio>
#include<cstring>

/**
    Simple Package: V, w[i], p[i]
    Base Function:
    dp[i][j] = max(dp[i][j], dp[i][j-w[i]]+p[i])
    
    Optimization:
    for i in (1...n)
        for j in (V...w[i])
            dp[j] = max(dp[j], dp[j-w[i]] + p[i])

    Complete Package: V, w[i], p[i]
    Base Function:
    dp[i][j] = max(dp[i][j-k*w[i]], dp[i][j-k*w[i]]+k*p[i]) (1<=k<=V/w[i])

    Optimization:
    for i in (1...n)
        for j in (w[i]...V)
            dp[j] = max(dp[j], dp[j-w[i]] + p[i])

    Multiple Package: V, w[i], p[i], c[i]
    Base Function:
    dp[i][j] = max(dp[i][j-k*w[i]], dp[i][j-k*w[i]]+k*p[i]) (1<=k<=c[i])

    Optimization:
    for i in (1...n)
        for j in (V...w[i])
            for offset in (1, 2, 4...2^(x-1), c[i]-(2^x-1))
                dp[j] = max(dp[j], dp[j-offset*w[i]] + offset*p[i])
*/
const int DPLENGTH = 100005;
const int WLENGTH = 11;
const int PLENGTH = 11;
int n, m, dp[DPLENGTH], w, p, item[WLENGTH][PLENGTH];
inline int max(int a, int b) { return a > b ? a : b; }
int main()
{
    scanf("%d %d", &n, &m);
    memset(dp, 0, sizeof(dp));
    memset(item, 0, sizeof(item));
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d %d", &w, &p);
        ++item[w][p];
        /* for (int j = m; j >= w; --j)
            dp[j] = max(dp[j], dp[j - w] + p); */
    }
    for (int i = 1; i < WLENGTH; ++i)
    {
        for (int j = 1; j < PLENGTH; ++j)
        {
            for (int k = 0; item[i][j]; ++k)
            {
                int offset = 1 << k;
                if (offset > item[i][j])
                    offset = item[i][j];
                item[i][j] -= offset;
                for (int l = m; l >= offset*i; --l)
                    dp[l] = max(dp[l], dp[l - offset*i] + offset*j);
            }
        }
    }
    int mmax = 0;
    for (int i = 0; i <= m; ++i)
        if (mmax < dp[i])
            mmax = dp[i];
    printf("%d\n", mmax);
    return 0;
}

