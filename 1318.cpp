#include <cstdio>

const int mod = 1000000007;
const int MAXN = 100;
int n;
int pow2[MAXN + 1] = { 1 };
int ansIllegal[MAXN + 1] = { 0, 0, 1 };
int ansLegal[MAXN + 1] = { 0, 2, 3 };
void func(int n)
{
    for (int i = 1; i <= n - 2; ++i)
    {
        pow2[i] = (pow2[i - 1] << 1) % mod;
        // Notice, here need mod twice to avoid exceed the limit. 
        // or we may use the unsigned to accelerate the program.
        ansIllegal[i + 2] = ((ansIllegal[i + 1] + ansIllegal[i]) % mod + pow2[i]) % mod;
        ansLegal[i + 2] = (ansLegal[i + 1] + ansLegal[i]) % mod;
        if (ansIllegal[i] != ((pow2[i] - ansLegal[i]) % mod + mod) % mod)
            printf("Error: %d %d %d\n", i, ansLegal[i + 2], ansIllegal[i + 2]);
    }
}

int main()
{
    scanf("%d", &n);
    func(n);
    printf("%d\n", ansIllegal[n]);
    // printf("%d\n", ~(1 << 31));
    return 0;
}
