#include <cstdio>
#include <cstring>
#define mod 12357

int n, K;
int map[30][128][128] = { 0 };

void DFS(int cs, int ps, int col)
{
    if (col == K)
    {
        map[1][ps][cs] = 1;
        return ;
    }
    DFS(cs << 1, (ps << 1) + 1, col + 1);
    DFS((cs << 1) + 1, ps << 1, col + 1);
    if (col + 2 <= K)
        DFS((cs << 2) + 3, (ps << 2) + 3, col + 2);
}

void matrix_mul(int m1[128][128], int m2[128][128], int m3[128][128], int len)
{
    for (int i = 0; i < len; ++i)
        for (int j = 0; j < len; ++j)
        {
            for (int k = 0; k < len; ++k)
                m3[i][j] += ((m1[i][k] * m2[k][j]) % mod);
            m3[i][j] %= mod;
        }
}

int main()
{
    int tmp[128][128] = { 0 };
    int pow = 0;
    scanf("%d %d", &K, &n);
    if ((n & 0x1) && (K & 0x1))
        printf("0\n");
    else
    {
        DFS(0, 0, 0);
        int len = 1 << K;
        for (int i = 0; i < len; ++i) map[0][i][i] = 1;
        for (int i = 1; i <= 27; ++i) matrix_mul(map[i], map[i], map[i + 1], len);
        while (n)
        {
            ++pow;
            if (n & 0x1)
            {
                memset(tmp, 0, sizeof(tmp));
                matrix_mul(map[0], map[pow], tmp, len);
                memcpy(map[0], tmp, sizeof(int) * 16384);
            }
            n >>= 1;
        }
        printf("%lld\n", map[0][len-1][len-1]);
    }
    return 0;
}