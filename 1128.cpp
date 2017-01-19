#include <cstdio>

#define maxn 1000010
int a[maxn], n, K;

inline void swap(int& a, int& b)
{
    a = a^b; b = a^b; a = a^b;
}

int find(int st, int ed, int K)
{
    int i = st, j = ed;
    while (i<j)
    {
        while (i<j && a[i] < K) ++i;
        while (i<j && a[j] > K) --j;
        if (i<j) swap(a[i], a[j]);
    }
    if (a[i] == K)
        return i;
    else
        return -1;
}

int main()
{
    scanf("%d %d", &n, &K);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    printf("%d\n", find(1, n, K));
    return 0;
}