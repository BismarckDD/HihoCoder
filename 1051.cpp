#include <cstdio>

int T, n, m;
int a[101];

int maxLE(int a[101], int l, int r, int key)
{
    int ans = -1, m;
    while (l <= r)
    {
        m = (l + r) >> 1;
        if (a[m] <= key) { ans = m, l = m + 1; }
        else r = m - 1;
    }
    return ans;
}

int maxL(int a[101], int l, int r, int key)
{
    int ans = -1, m;
    while (l <= r)
    {
        m = (l + r) >> 1;
        if (a[m] < key) { ans = m, l = m + 1; }
        else r = m - 1;
    }
    return ans;
}

int minGE(int a[101], int l, int r, int key)
{
    int ans = -1, m;
    while (l <= r)
    {
        m = (l + r) >> 1;
        if (a[m] >= key) { ans = m, r = m - 1; }
        else l = m + 1;
    }
    return ans;
}

int minG(int a[101], int l, int r, int key)
{
    int ans = -1, m;
    while (l <= r)
    {
        m = (l + r) >> 1;
        if (a[m] > key) { ans = m, r = m - 1; }
        else l = m + 1;
    }
    return ans;
}

bool test(int len)
{
    for (int i = 1; i + len - 1 <= 100; ++i)
    {
        int b = maxL(a, 0, n + 1, i);
        int c = minG(a, 0, n + 1, i + len - 1);
        int contain = c - b - 1;
        if (contain <= m) return true;
    }
    return false;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        if (n == 0 || n <= m)
        {
            printf("100\n");
            continue;
        }
        a[0] = 0, a[n + 1] = 101;
        int l = 0, r = 100, m, ans = -1;
        while (l <= r)
        {
            m = (l + r) >> 1;
            if (test(m)) { ans = m, l = m + 1; }
            else r = m - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}