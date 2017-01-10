#include <cstdio>

typedef long long ll;
typedef unsigned long long ull;
/**
1, selection two different prime p & q, that N = pq
2, according to Euler Theory, there are (p-1)(q-1) integers that huzhi with N.
3, select an e that e < (p-1)(q-1) and huzhi with it.
4, d * e = 1 mod (p-1)(q-1).
5, (N, e) is public key, while (N, d) is the private key.


N = M*233
RSA public key (N, 7)     M = 9001, N = 2097233, e = 7
p = 9001, q = 233
d * e = 1 mod (p-1)(q-1) => 2088000
=> d*e + k*2088000 = 1 => Extended Euclidean


text**(public key) mod N = cipher
cipher(private key) mode N = text

*/
const int MAXN = 10000;
bool prime[MAXN] = { 0 };
int p = 0, q = 233, e = 7, d = 0, fn = 0, N = 0;

void calculatePrime()
{
    for (int i = 2; i <= 100; ++i)
    {
        for (int j = 1; j*i < MAXN; j++)
        {
            prime[j*i] = true;
        }
    }
}

void calculateFN()
{
    for (int i = 9997; i >= 1001; --i)
    {
        if (!prime[i] && i * q % 1000 == q)
        {
            p = i, N = p*q, fn = (p - 1)*(q - 1);
            printf("%d %d %d\n", p, N, fn);
            return;
        }
    }
}

int Extended_Eculidean(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1; y = 0;
        return a;
    }
    int r = Extended_Eculidean(b, a%b, x, y);
    int t = x; x = y; y = t - a / b*y;
    return r;
}

void fast_exp_mod(long long a, long long b, long long mod)
{
    long long res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    printf("%lld", res);
}

int main()
{
    calculatePrime();
    calculateFN();
    // printf("%d\n", prime[233]);
    int k;
    int r = Extended_Eculidean(e, fn, d, k);
    printf("%d %d %d\n", d, k, r);
    if (d < 0) 
    {
        d = (d % fn + fn) % fn;
    }
    fast_exp_mod(197372, d, N);
    fast_exp_mod(333079, d, N);
    // 378390696
    printf("\n");
    return 0;
}