#include <cstdio>
#include <map>
using namespace std;
#define mod 1000000007
int n, k, fib[30] = { 0, 1, 1 }, len[30] = { 0 };
map<int, int> _fib;
int Find(int l, int r, int key) 
{
    while (l <= r) // WA*2
    {
        int m = (l + r) >> 1;
        if (fib[m] == key) return m;
        else if (fib[m] > key) r = m - 1;
        else l = m + 1;
    }
    return -1; 
}
int main()
{
    scanf("%d", &n);
    for (int i = 3; fib[i - 1] <= 100000; ++i)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
        //printf("%d: %d\n", i, fib[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &k);
        if (k == 1) 
        { 
            len[2] += len[1]; 
            ++len[1]; 
            len[1] = len[1] >= mod ? len[1] % mod : len[1];
            len[2] = len[2] >= mod ? len[2] % mod : len[2];
        }
        else 
        {
            int idx = Find(3, 26, k);
            if (idx > 0)
            {
                len[idx] += len[idx - 1];
                len[idx] = len[idx] >= mod ? len[idx] % mod : len[idx];
            }
        }
    }
    int ans = 0;
    for (int i = 1; len[i] != 0; ++i)
    {
        ans += len[i];
        ans %= mod;
    }
    printf("%d\n", ans);
    return 0;
}