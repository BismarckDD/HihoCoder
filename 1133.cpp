#include<cstdio>

#define maxn 1000010
int n, k, a[maxn];

inline void swap(int& a, int &b)
{
    a = a^b; b = a^b; a = a^b;
}

int Selection(int st, int ed, int k)
{
    int i = st, j = ed, key = a[st + ed >> 1];
    while (i<j)
    {
        while (i<j && a[i] < key) ++i;
        while (i<j && a[j] > key) --j;
        if (i<j) swap(a[i], a[j]);
    }
    i = i - st + 1;
    if (i == k) return a[i + st - 1];
    else if (i > k) return Selection(st, st + i - 2, k);
    else if (i < k) return Selection(st + i, ed, k - i);

}
int main()
{

    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    if (k <= 0 || k > n)
        printf("-1\n");
    else
        printf("%d\n", Selection(1, n, k));
    return 0;
}