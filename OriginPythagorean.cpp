#include <cstdio>

int main()
{
    for (int u = 1; u <= 10; ++u)
    {
        for (int v = 1; v < u; ++v)
        {
            printf("(%d, %d: %d %d %d)\n", u, v, (u*u - v*v), 2 * u*v, (u*u + v*v));
        }
        printf("\n");
    }
    return 0;
}