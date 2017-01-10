#include <cstdio>

#define mod 1000000007
int n, m, row = 0;
int dp[2][32];

bool isLegal(int s)
{
    for (int i = 0; i < m; ++i)
    {
        if (s & (1 << i))
        {
            if ((i == m - 1) || !(s & (1 << (i + 1)))) // next location must exsit, and equals one.
                return false;
            else
                ++i;
        }
    }
    return true;
}

bool isLegal(int cs, int ps)
{
    for (int i = 0; i < m; ++i)
    {
        if (cs & (1 << i)) // cs & ( 1<<i ) == 1 current location has been occupied.
        {
            if (ps & (1 << i)) // ps & ( 1<<i ) == 1, current location (of last row) has been occupied.
            {
                if ((i == m - 1) || !(ps & (1 << (i + 1))) || !(cs & (1 << (i + 1))))
                    return false; // next location must exsit, and equals one.
                else
                    ++i;
            }
        }
        else // cs & ( 1<<i ) == 0, current location is empty.
            if (row == n || !(ps & (1 << i)))
                return false;
    }
    return true;
}

void calc(int n, int maxs)
{
    for (int i = 0; i <= maxs; ++i) dp[1][i] = isLegal(i);
    for (row = 2; row <= n; ++row)
    {
        for (int cs = 0; cs <= maxs; ++cs) //current row
        {
            dp[row & 0x1][cs] = 0;
            for (int ps = 0; ps <= maxs; ++ps) //previous row
                if (isLegal(cs, ps))
                {
                    dp[row & 0x1][cs] += dp[(row ^ 0x1) & 0x1][ps];
                    if (dp[row & 0x1][cs] > mod) dp[row & 0x1][cs] %= mod;
                }
        }
    }
}
int main()
{
    scanf("%d %d", &n, &m);
    if ((n & 0x1) && (m & 0x1))
    {
        printf("0\n");
    }
    else
    {
        if (n < m) n = m^n, m = m^n, n = m^n;
        calc(n, (1 << m) - 1);
        printf("%d\n", dp[n & 0x1][(1 << m) - 1]);
    }
    return 0;
}
