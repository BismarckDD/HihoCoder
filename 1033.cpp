#include <cstdio>
#include <cstring>
long long mod = 1000000007;
long long offset = 100;
long long base[20];
long long l, r, k, digits[20], gpos, cpos, sum;
typedef struct NODE { long long sum, num;} Node; //s = sum of digits, n = num of digits
Node dp[20][400]; //dp array.
Node dfs(long long pos, long long k, bool limit) //digit dp model, may use later.
{
    Node ans;
    ans.sum = ans.num = 0;
    if (pos == 0) 
    { // Last digit  
        if (k == offset) ans.num = 1;
        return ans;
    }
    if (!limit && (dp[pos][k].num != -1)) return dp[pos][k];
    long long tail = limit ? digits[pos] : 9;      // If we can use greater than digits[pos] end.
    long long head = pos == cpos ? 1 : 0;          // If we can use 0 start. 
    long long sgn = ((cpos - pos) & 0x1) ? -1 : 1; // to calc the sgn
    for (int i = head; i <= tail; ++i)
    {   // only one situation that we can not use the number greater than digit[pos]
        Node tmp = dfs(pos - 1, k - i*sgn, limit && (i == digits[pos]));
        if (tmp.num > 0)
        {
            ans.num += tmp.num;
            sum = ((((tmp.num % mod) * base[pos]) % mod) * i) % mod;
            ans.sum += tmp.sum;
            ans.sum %= mod;
            ans.sum += sum;
            ans.sum %= mod;
        }
    }
    if (!limit) dp[pos][k] = ans;
    return ans;
}
long long Cal(long long n, long long k)
{
    long long ans = 0;
    if (n <= 0) return 0;
    gpos = 0;
    while (n)
    {
        digits[++gpos] = n % 10;
        n /= 10;
    }
    for (cpos = 1; cpos <= gpos; cpos++) 
    { // take 1-digit, 2-digit, ..., into consideration individually.
        memset(dp, -1, sizeof(dp));
        ans += dfs(cpos, k + offset, cpos == gpos).sum;
        ans %= mod;
    }
    return ans;
}
int main()
{
    base[1] = 1;
    for (int i = 2; i <= 19; i++) base[i] = (base[i - 1] * 10) % mod;
    scanf("%lld %lld %lld", &l, &r, &k);
    printf("%lld\n", (Cal(r, k) - Cal(l - 1, k) + mod) % mod);
    return 0;
}