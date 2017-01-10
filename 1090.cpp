#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxn 1010
int n;
struct CarInfo
{
    int id;
    int in_pos;
    int out_pos;
    int velocity;
    double time;
} maincars[maxn], auxcars[maxn];

bool in_pos_decrease(CarInfo a, CarInfo b)
{
    return a.in_pos > b.in_pos;
}

bool out_pos_increase(CarInfo a, CarInfo b)
{
    return a.out_pos < b.out_pos;
}

bool id_increase(CarInfo a, CarInfo b)
{
    return a.id < b.id;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d %d %d", &maincars[i].in_pos, &maincars[i].out_pos, &maincars[i].velocity);
        maincars[i].id = i;
        maincars[i].time = 0;
    }
    memcpy(auxcars, maincars, sizeof(CarInfo)*n);
    sort(maincars, maincars + n, in_pos_decrease);
    sort(auxcars, auxcars + n, out_pos_increase);
    for (int i = 0; i < n; ++i) // X[i] decrease
    {
        int pos = maincars[i].in_pos;
        double t = 0;
        for (int j = 0; j < n; ++j) // Y[i] increase
        {
            if (maincars[i].in_pos  >= auxcars[j].out_pos) continue;
            t += (double)(auxcars[j].out_pos - pos) / (double)maincars[i].velocity;
            t = auxcars[j].time > t ? auxcars[j].time : t;
            auxcars[j].time = t;
            if (maincars[i].id == auxcars[j].id) 
            {
                maincars[i].time = auxcars[j].time; 
                break;
            }
            pos = auxcars[j].out_pos;
        }
    }

    sort(maincars, maincars + n, id_increase);
    for (int i = 0; i < n; ++i) printf("%.2lf\n", maincars[i].time);
    return 0;
}