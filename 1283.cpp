#include <cstdio>

int n, a[1010];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    int flag = 1;
    for (int i = n - 1; i > 0; --i)
    {
        if (a[i] >= a[i + 1])
        {
            flag = i;
            break;
        }
    }
    for (int i = 1; i <= flag; ++i) printf("%d%c", a[i], i == flag ? '\n' : ' ');
    return 0;
}