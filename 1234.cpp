#include <cstdio>
typedef long long ll;

inline ll GCD(ll a, ll b)
{
    if (b == 0) return a;
    else return GCD(b, a%b);
}

inline ll LCM(ll a, ll b)
{
    return a / GCD(a, b) * b;
}

struct fraction
{
    ll numerator, denominator;

    fraction(fraction& other)
    {
        numerator = other.numerator;
        denominator == other.denominator;
    }

    bool operator==(fraction& other)
    {
        return numerator == other.numerator && denominator == other.denominator;
    }

    fraction& operator=(fraction& other)
    {
        numerator = other.numerator;
        denominator == other.denominator;
        return *this;
    }

    void reduction()
    {
        ll gcd = (numerator, denominator);
        denominator = denominator / gcd;
        numerator = numerator / gcd;
    }

    fraction operator+(fraction& other)
    {
        fraction tmp = *this;
        ll lcm = LCM(tmp.denominator, other.denominator);
        tmp.numerator = tmp.numerator * (lcm / tmp.denominator) + other.numerator * (lcm / other.denominator);
        tmp.denominator = lcm;
        return *this;
    }

    fraction operator/(int divider)
    {
        ll gcd = (numerator, divider);
        numerator /= gcd;
        divider /= gcd;
        denominator *= divider;
        return *this;
    }

};

int main() 
{
    int T;
    scanf("%d", &T);
    while (T--) 
    {
        double l = 0, r = 0.5, k;
        scanf("%lf", &k);
        for (int i = 1; i <= 1000; ++i) 
        {
            if (k == l || k == r) { printf("-1\n"); break; }
            l = (l + r) / 2;
            if (k < l) { printf("%d\n", (i<<2)); break; }
        }
    }
    return 0;
}