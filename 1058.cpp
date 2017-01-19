#include <cstdio>

#define maxn 50010
char c, s[maxn], cmd[5];
inline void swap(char &a, char &b)
{
    a = a^b;
    b = a^b;
    a = a^b;
}
void cmd1(int i, int j, char c)
{
    for (int k = i - 1; k < j; ++k) s[k] = c;
}
void cmd2(int i, int j, int k)
{
    for (int t = i - 1; t < j; ++t) s[t] = ((s[t] -'A' + k) % 26) + 'A';
}
void cmd3(int k, int n)
{
    int i, j;
    i = 0, j = k - 1; while (i < j) swap(s[i++], s[j--]);
    i = k, j = n - 1; while (i < j) swap(s[i++], s[j--]);
    i = 0, j = n - 1; while (i < j) swap(s[i++], s[j--]);
}
void cmd4(int i, int j)
{
    if (i > j) return;
    cmd4(i + 1, j);
    cmd2(i, j, 1);
}
int main()
{
    int i, j, k, n, m, ins;
    scanf("%d %d", &n, &m);
    scanf("%s", s);
    while (m--)
    {
        scanf("%s %d", cmd, &ins);
        switch (ins)
        {
        case 1: scanf("%d %d %c", &i, &j, &c); cmd1(i, j, c); break;
        case 2: scanf("%d %d %d", &i, &j, &k); cmd2(i, j, k); break;
        case 3: scanf("%d", &k);               cmd3(k, n);    break;
        case 4: scanf("%d %d", &i, &j);        cmd4(i, j);    break;
        }
    }
    printf("%s\n", s);
    return 0;
}