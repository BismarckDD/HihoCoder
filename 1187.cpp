#include<iostream>
#include<cstdio>
using namespace std;

const int prime[13] = { 2,  3,  5,  7, 
                        11, 13, 17, 19,
                        23, 29, 31, 37, 41};
// pi{ prime[i] } <= 10 ^ 16 

long long ans, upper,maxDivisor = 1;
void DFS(long long now, long long divisor, int idx, int lastI)
{
    if (divisor > maxDivisor || 
        divisor == maxDivisor && now < ans)
    {
        maxDivisor = divisor;
        ans = now;
    }
    for (int i = 1; i <= lastI && idx < 13; ++i)
    {
        now *= prime[idx];
        if (now > upper) break;
        DFS(now, divisor*(i+1), idx + 1, i);
        
    }
}
int main()
{
    scanf("%lld", &upper);
    ans = upper;
    DFS(1, 1, 0, 50);
    printf("%lld\n", ans);
    return 0;
}