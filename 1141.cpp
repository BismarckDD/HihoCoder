#include <cstdio>
#include <cstring>
int n, a[100010], temp[100010];
long long ans = 0;
void MergeSort(int a[], int st, int ed)
{
    if (st == ed) return;
    int m = (st + ed) >> 1;
    MergeSort(a, st, m);
    MergeSort(a, m + 1, ed);
    int i = st, j = m + 1, k = i;
    while (i <= m && j <= ed)
    {
        if (a[i] <= a[j]) temp[k++] = a[i++];
        else { temp[k++] = a[j++]; ans += (m - i + 1); }
    }
    while (i <= m) temp[k++] = a[i++];
    while (j <= ed) temp[k++] = a[j++];
    memcpy(a + st, temp + st, sizeof(int)*(ed - st + 1));
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    MergeSort(a, 1, n);
    printf("%lld\n", ans);
    return 0;
}
