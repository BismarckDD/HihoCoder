#include <cstdio>
char cons[21][110][110];
char sky[1010][1010];
int K, H, W, N, M;

int lineMatch(char *a, char *b)
{
    
}
bool isMatch(char a[110][110], char b[1010][1010])
{
    for()
    return true;
}

int main()
{
    scanf("%d", &K);
    for (int i = 0; i < K; ++i)
    {
        scanf("%d %d", &H, &W);
        for (int j = 0; j < H; ++j)
            scanf("%s", cons[K][H]);
    }
    scanf("%d %d", &N, &M);
    for (int j = 0; j < N; ++j)
        scanf("%s", sky[N]);
    for (int i = 0; i < K; ++i)
    {
        if (isMatch(cons[i], sky))
            printf("Yes\n");
        else
            printf("No\n");
    }

    return 0;
}