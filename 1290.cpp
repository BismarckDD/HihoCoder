#include <cstdio>
#define min(a, b) (a<b?a:b)
#define max(a, b) (a>b?a:b)
#define maxlimit 10010;
int n, m;
int mc[110][110][2];
char map[110][110];
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%s", map[i]);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < 2; ++k)
                mc[i][j][k] = maxlimit;
    mc[0][0][1] = 0;
    map[0][1] == 'b'? mc[0][0][0] = 0 : mc[0][0][0] = 1;
    for (int i = 1; i < m; ++i)
    {
        mc[0][i][1] = map[0][i] == 'b' ? mc[0][i - 1][1] + 1 : mc[0][i - 1][1];
        mc[0][i][0] = (i == m - 1 || map[0][i + 1] == 'b') ? mc[0][i][1] : mc[0][i][1] + 1;
    }
    for (int i = 1; i < n; ++i)
    {
        mc[i][0][0] = map[i][0] == 'b' ? mc[i - 1][0][0] + 1 : mc[i - 1][0][0];
        mc[i][0][1] = (i == n - 1 || map[i + 1][0] == 'b') ? mc[i][0][0] : mc[i][0][0] + 1;
    }
    for(int j = 1; j < n; ++j)
        for (int i = 1; i < m; ++i)
        {
            mc[j][i][0] = (map[j][i] == 'b') ? min(mc[j][i][0], mc[j - 1][i][0] + 1) : min(mc[j][i][0], mc[j - 1][i][0]);
            mc[j][i][1] = (map[j][i] == 'b') ? min(mc[j][i][1], mc[j][i - 1][1] + 1) : min(mc[j][i][1], mc[j][i - 1][1]);
            mc[j][i][0] = (i == m - 1 || map[j][i + 1] == 'b') ? min(mc[j][i][0], mc[j][i][1]) : min(mc[j][i][0], mc[j][i][1] + 1);
            mc[j][i][1] = (j == n - 1 || map[j + 1][i] == 'b') ? min(mc[j][i][1], mc[j][i][0]) : min(mc[j][i][1], mc[j][i][0] + 1);
        }
    /* for (int j = 0; j < n; ++j)
        for (int i = 0; i < m; ++i)
            printf("%d%c", mc[j][i][0], i == m - 1 ? '\n' : ' ');
    for (int j = 0; j < n; ++j)
        for (int i = 0; i < m; ++i)
            printf("%d%c", mc[j][i][1], i == m - 1 ? '\n' : ' '); */
    printf("%d\n", min(mc[n - 1][m - 1][0], mc[n - 1][m - 1][1]));
    return 0;
}