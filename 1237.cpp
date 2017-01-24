#include <cstdio>  
#include <cmath>

int main()
{
    double x, y, r;
    int xx, yy, ansx = 0, ansy = 0;
    double dis = 0, tmp;
    scanf("%lf %lf %lf", &x, &y, &r);
    int maxx = (int)floor(x + r);
    int minx = (int)ceil(x - r);
    for (xx = minx; xx <= maxx; ++xx)
    {
        yy = (int)floor(y + sqrt(r*r - (xx*1.0 - x)*(xx*1.0 - x)));
        tmp = sqrt((xx*1.0 - x)*(xx*1.0 - x) + (yy*1.0 - y)*(yy*1.0 - y));
        if (tmp > dis || tmp == dis && (xx > ansx || xx == ansx && yy > ansy))
            ansx = xx, ansy = yy, dis = tmp;
        yy = (int)ceil(y - sqrt(r*r - (xx*1.0 - x)*(xx*1.0 - x)));
        tmp = sqrt((xx*1.0 - x)*(xx*1.0 - x) + (yy*1.0 - y)*(yy*1.0 - y));
        if (tmp > dis || tmp == dis && (xx > ansx || xx == ansx && yy > ansy))
            ansx = xx, ansy = yy, dis = tmp;
    }
    printf("%d %d\n", ansx, ansy);
    return 0;
}