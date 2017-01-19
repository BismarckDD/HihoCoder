#include <cstdio>
int limit[7] = { 45, 345, 1245, 7745, 13745, 22495, 0 };
int fct[7] = { 0, 105, 555, 1005, 2755, 5505, 13505 };
double fac[7] = { 0.03, 0.1, 0.2, 0.25, 0.3, 0.35, 0.45 };
int main()
{
    int n, ans, i;
    scanf("%d", &n);
    /* n = n - 3500;
    if (n <= 1500) ans = n * 0.03;
    else if (n <= 4500) ans = n * 0.10 - 105;
    else if (n <= 9000) ans = n * 0.20 - 555;
    else if (n <= 35000) ans = n * 0.25 - 1005;
    else if (n <= 55000) ans = n * 0.30 - 2755;
    else if (n <= 80000) ans = n * 0.35 - 5505;
    else if (n > 80000) ans = n * 0.45 - 13505;*/
    for (i = 0; i < 6; ++i)
        if (n <= limit[i]) break;
    ans = (n + fct[i]) / fac[i];
    printf("%d\n", ans+3500);

    return 0;
}