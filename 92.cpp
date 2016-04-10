#include<iostream>
#include<cstdio>
using namespace std;
const int S = 5;

long long mod_mul(long long a, long long b, long long n) 
{
    long long res = 0;
    while (b) 
    {
        if (b & 1)
            res = (res + a) % n;
        a = (a + a) % n;
        b >>= 1;
    }
    return res;
}

long long mod_exp(long long a, long long b, long long n) 
{
    long long res = 1;
    while (b) 
    {
        if (b & 1)
            res = mod_mul(res, a, n);
        a = mod_mul(a, a, n);
        b >>= 1;
    }
    return res;
}

long long pow(long long a, long long u)
{
    //printf("%lld,%lld\n", a, u);
    if (u == 0) return 1;
    if (u == 1) return a;
    long long t = pow(a, u >> 1);
    if ((u & 0x1) == 0)
        return t*t;
    else
        return t*t*a;
}
bool Miller_Rabin(long long n)
{
    if (n <= 2)
        if (n == 2)
            return true;
        else
            return false;

    if ((n & 0x1) == 0)
        return false;

    long long u1 = n - 1;
    while ((u1 & 0x1) == 0) 
        u1 >>= 1;
    
    for (int i = 1; i <= S; ++i)
    {
        long long u = u1;
        long long a = rand()%(n-2)+2; // a random from 2 to n-1
        long long x = mod_exp(a,u,n) % n, y=1;
        while(u < n)
        {
            y = mod_exp(x, 2, n) % n;
            if ((y == 1) && (x != 1) && (x != n - 1)) // quardric probe
                return false;
            x = y;
            u = u<<1;
        }
        //cout << a << "," << u << "," << x << "," << y << "," << n <<endl;
        if (x != 1) // Fermat test
            return false;
    }
    return true;
}
int main()
{
    int t;
    long long n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%lld", &n);
        if (Miller_Rabin(n))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
