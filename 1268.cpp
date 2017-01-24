#include <cstdio>

int a[4][4];

void cal(int a[4][4], int i, int j)
{
    int cnt = 0, sum = 0;
    for(int t = 1; t <= 3; ++t)
    {
        if (a[i][t]) ++cnt;
        sum += a[i][t];
    }
    if (cnt == 2) 
    {
        a[i][j] = 15 - sum; 
        return;
    }
    cnt = 0, sum = 0;
    for (int t = 1; t <= 3; ++t)
    {
        if (a[t][j]) ++cnt;
        sum += a[t][j];
    }
    if (cnt == 2)
    {
        a[i][j] = 15 - sum;
        return;
    }
    cnt = 0, sum = 0;
    if (i == j)
    {
        for (int t = 1; t <= 3; ++t)
        {
            if (a[t][t]) ++cnt;
            sum += a[t][t];
        }
    }
    else if (i + 2 == j || i - 2 == j)
    {
        for (int t = 1; t <= 3; ++t)
        {
            if (a[t][4-t]) ++cnt;
            sum += a[t][4-t];
        }
    }
    if (cnt == 2)
    {
        a[i][j] = 15 - sum;
        return;
    }
        
}

void Deal(int a[4][4])
{
    for (int t = 1; t <= 3; ++t)
        for (int i = 1; i <= 3; ++i)
            for (int j = 1; j <= 3; ++j)
            {
                if (a[i][j]) continue;
                cal(a, i, j);
            }
    if (!a[1][1]) a[1][1] = 10 - ((a[2][1] + a[1][2]) >> 1);
    if (!a[1][3]) a[1][3] = 10 - ((a[2][3] + a[1][2]) >> 1);
    if (!a[3][1]) a[3][1] = 10 - ((a[2][1] + a[3][2]) >> 1);
    if (!a[3][3]) a[3][3] = 10 - ((a[2][3] + a[3][2]) >> 1);
    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= 3; ++j)
            printf("%d%c", a[i][j], j == 3 ? '\n' : ' ');
}

bool Judge(int a[4][4])
{
    if (a[1][1] && a[2][2] && a[3][3]
        || a[1][2] && a[2][2] && a[3][2]
        || a[1][3] && a[2][2] && a[3][1]
        || a[2][1] && a[2][2] && a[2][3])
        return true;
    else return false;
}

int main()
{
    int count = 0;
    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= 3; ++j)
        {
            scanf("%d", &a[i][j]);
            if (i == 2 && j == 2) a[i][j] = 5;
            if (a[i][j]) ++count;
        }
    if (count <= 2 || count == 3 && Judge(a))
        printf("Too Many\n");
    else
        Deal(a);
    return 0;
}