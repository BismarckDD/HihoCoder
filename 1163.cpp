#include <cstdio>

int main()
{
    int n, ans = 0, t;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &t);
        ans ^= t;
    }
    ans == 0 ? printf("Bob\n") : printf("Alice\n");
    return 0;
}