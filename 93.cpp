#include<cstdio>
#include<iostream>
using namespace std;
int n;
bool vis[1000005] = {false};
int primes[100001];
int EularShift(int n)
{
    int countPrimes = 0;
    for (int i = 2; i <= n; ++i)
    {
        if (vis[i] == false)
            primes[countPrimes++] = i;
        for (int j = 0; j < countPrimes; ++j)
        {
            if (i*primes[j] > n) break;
            vis[i*primes[j]] = true;
            if (i%primes[j]==0) break;
        }
    }
    return countPrimes;
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d\n", EularShift(n));
    return 0;

}