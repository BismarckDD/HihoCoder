#include <cstdio>
char str[100010];

int main()
{
    int n, ans = 0, t;
    scanf("%d", &n);
    scanf("%s", str);
    for (int i = 0; i < n; ++i)
    {
        if (str[i] == 'H')
            ans ^= (i + 1);
    }
    ans == 0 ? printf("Bob\n") : printf("Alice\n");
    return 0;
}