#include <cstdio>
#define max(a, b) (a>b?a:b)
#define min(a, b) (a<b?a:b)
int n, m, L, l, r, t, b, w, h;
int res = 0;

int calculate(int pl, int pr, int pt, int pb)
{
    int ll = max(l, pl);
    int rr = min(r, pr);
    int tt = max(t, pt);
    int bb = min(b, pb);

    if (ll >= rr || tt >= bb)
        return (pr - pl) * (pb - pt);

    int inside = 0;
    if (ll > pl && ll < pr && tt > pt && tt < pb)
        inside++;
    if (rr > pl && rr < pr && tt > pt && tt < pb)
        inside++;
    if (ll > pl && ll < pr && bb > pt && bb < pb)
        inside++;
    if (rr > pl && rr < pr && bb > pt && bb < pb)
        inside++;

    if (inside == 1 || inside == 4)
        return (pr - pl) * (pb - pt) - (rr - ll) * (bb - tt);
    else
        return 0;
}

int main()
{
    scanf("%d %d %d", &n, &m, &L);
    scanf("%d %d %d %d", &l, &r, &t, &b);
    int sumlw = L >> 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) 
        {
            w = 1, h = (L - (w << 1)) >> 1;
            while (w > 0 && h > 0) 
            {
                res = max(res, calculate(j, min(m, j + w), i, min(n, i + h)));
                ++w, h = (L - (w << 1)) >> 1;
            }
        }
    printf("%d\n", res);
    return 0;
}
