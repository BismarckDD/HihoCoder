#include <cstdio>
#include <cmath>

bool checkIfOne(int n) 
{
    int i2 = int(sqrt(n));
    return i2*i2 == n;
}

bool checkIfTwo(int n) 
{
    for (int i = 1, i2 = i*i; i2<n; i2 += (2 * i + 1), ++i)
        if (checkIfOne(n - i2)) return true;
    return false;
}

bool checkIfThree(int n)
{
    for (int i = 1, i2 = i*i; i2<n; i2 += (2 * i + 1), ++i)
        if (checkIfTwo(n - i2)) return true;
    return false;
}

int main()
{
    int n;
    while (scanf("%d", &n) && n != -1)
    {
        if (n == 0)
            printf("1\n");
        else if (checkIfOne(n))
            printf("1\n");
        else if (checkIfTwo(n))
            printf("2\n");
        else if (checkIfThree(n))
            printf("3\n");
        else
            printf("4\n");
    }
    return 0;
}