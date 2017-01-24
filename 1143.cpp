#include <cstdio>
#include <cstring>
#define mod 19999997
typedef long long ll;
int n, f1 = 1, f2 = 2;
ll map[30][2][2];
void matrix_mul(ll m1[2][2], ll m2[2][2], ll m3[2][2])
{
    /* for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                m3[i][j] += m1[i][k] * m2[k][j]; */
    m3[0][0] = (m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0]) % mod;
    m3[0][1] = (m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1]) % mod;
    m3[1][0] = (m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0]) % mod;
    m3[1][1] = (m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1]) % mod;
}

int main()
{
    ll tmp[2][2];
    int pow = 0;
    map[0][0][0] = map[0][1][1] = 1, map[0][0][1] = map[0][1][0] = 0;
    map[1][0][0] = 0, map[1][0][1] = map[1][1][0] = map[1][1][1] = 1;
    for (int i = 1; i <= 27; ++i) matrix_mul(map[i], map[i], map[i + 1]);
    scanf("%d", &n);
    while (n)
    {
        ++pow;
        if (n & 0x1)
        {
            matrix_mul(map[0], map[pow], tmp);
            memcpy(map[0], tmp, sizeof(ll) * 4);
        }
        n >>= 1;
    }
    printf("%lld\n", (map[0][0][0] + map[0][1][0]) % mod);
    return 0;
}