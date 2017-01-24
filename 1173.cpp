#include <cstdio>
#include <cstring>
int SG[1010];
bool vis[1010];

int originalGetSG(int n) 
{
    if (SG[n] != -1) return SG[n];
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i < n; ++i) 
    {
        SG[i] = originalGetSG(i);
        SG[n-i] = originalGetSG(n-i);
        int a = SG[i], b = SG[n - i], t = 0;
        t ^= a^b;
        //if(n == 3) printf("%d %d %d\n", t, i, n - i);
        vis[a] = vis[b] = vis[t] = true;
    }
    vis[0] = true;
    for (int i = 0; ; ++i) 
        if (!vis[i])
            return i;
}

int getSG(int n)
{
    if (n == 0) return 0;
    else if (n % 4 == 0) return n - 1;
    else if (n % 4 == 3) return n + 1;
    else return n;
}

int main()
{
    int n, ans = 0, t;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &t);
        ans ^= getSG(t);
    }
    ans == 0 ? printf("Bob\n") : printf("Alice\n");
    return 0;
}