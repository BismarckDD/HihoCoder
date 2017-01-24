#include <cstdio>
#include <cstring>
#define mod 12357

int n, f2 = 3, f4 = 11;
int map[30][8][8] = { 0 };
void matrix_mul(int m1[8][8], int m2[8][8], int m3[8][8])
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
        {
            for (int k = 0; k < 8; ++k)
                m3[i][j] += ((m1[i][k] * m2[k][j]) % mod);
            m3[i][j] %= mod;
        }
}

int main()
{
    int tmp[8][8] = { 0 };
    int pow = 0;
    for (int i = 0; i < 8; ++i) map[0][i][i] = 1;
    map[1][0][7] = map[1][1][6] = map[1][2][5] = map[1][3][4] = 1;
    map[1][7][0] = map[1][6][1] = map[1][5][2] = map[1][4][3] = 1;
    map[1][3][7] = map[1][7][3] = map[1][6][7] = map[1][7][6] = 1;
    for (int i = 1; i <= 27; ++i) matrix_mul(map[i], map[i], map[i + 1]);
    scanf("%d", &n);
    if (n & 0x1)
        printf("0\n");
    else
    {
        while (n)
        {
            ++pow;
            if (n & 0x1)
            {
                memset(tmp, 0, sizeof(tmp));
                matrix_mul(map[0], map[pow], tmp);
                memcpy(map[0], tmp, sizeof(int) * 64);
            }
            n >>= 1;
        }
        printf("%lld\n", map[0][7][7]);
    }
    return 0;
}