#include<cstdio>
#include<xmemory>

int map[3][9][9];
int dir[8][2] = { {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1} };
const int QLENGTH = 64;
struct NODE { int x, y; } q[QLENGTH];

bool verify(int x, int y)
{
    return x <= 8 && y <= 8 && x >= 1 && y >= 1;
}
void traverse(int c, int x, int y)
{
    int rear = 0, front = 1, nx, ny;
    q[0] = { x, y };
    //int imap[9][9] = map[c];
    while (rear != front)
    {
        NODE tmp = q[rear++];
        rear %= QLENGTH;
        for (int i = 0; i < 8; ++i)
        {
            nx = tmp.x + dir[i][0];
            ny = tmp.y + dir[i][1];
            if (verify(nx, ny) && map[c][nx][ny] == -1)// || map[nx][ny] > map[tmp.x][tmp.y] + 1)
            {
                map[c][nx][ny] = map[c][tmp.x][tmp.y] + 1;
                q[front].x = nx;
                q[front].y = ny;
                front++;
                front %= QLENGTH;
            }
        }
    }
}

void SetBoard(char stpos[], int i)
{
    int x = stpos[0] - 'A' + 1;
    int y = stpos[1] - '0';
    map[i][x][y] = 0;
    traverse(i, x, y);
}
int main()
{
    int Case;
    char stpos[3];
    scanf("%d", &Case);
    while (Case--)
    {
        memset(map, -1, sizeof(map));
        for (int i = 0; i <= 2; ++i)
        {
            scanf("%s", stpos);
            SetBoard(stpos, i);
        }
        int mmin = 1 << 30;
        for (int i = 1; i <= 8; ++i)
            for (int j = 1; j <= 8; ++j)
                if (map[0][i][j] + map[1][i][j] + map[2][i][j] < mmin)
                    mmin = map[0][i][j] + map[1][i][j] + map[2][i][j];
        printf("%d\n", mmin);
    }
    return 0;
}