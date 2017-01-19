#include <cstdio>
#include <cstring>

int st[1000], sp = -1;
char s[1020];
int color[3] = { 0 };
int strcmp_c(char *src, char *des)
{
    int len = strlen(des);
    int i = 0;
    while (i < len)
        if (*(src + i) != *(des + i))
            return -1;
        else
            ++i;
    return 0;
}

int main()
{
    gets_s(s);
    int len = strlen(s), i = 0;
    while (i < len)
    {
        if (strcmp_c(s + i, "<red>") == 0)
        {
            st[++sp] = 0; i += 5;
        }
        else if (strcmp_c(s + i, "<yellow>") == 0)
        {
            st[++sp] = 1; i += 8;
        }
        else if (strcmp_c(s + i, "<blue>") == 0)
        {
            st[++sp] = 2; i += 6;
        }
        else if (strcmp_c(s + i, "</red>") == 0)
        {
            --sp; i += 6;
        }
        else if (strcmp_c(s + i, "</yellow>") == 0)
        {
            --sp; i += 9;
        }
        else if (strcmp_c(s + i, "</blue>") == 0)
        {
            --sp; i += 7;
        }
        else 
        {
            if (sp >= 0 && s[i] <='z' && s[i] >= 'a') ++color[st[sp]];
            ++i;
        }
    }
    for (int i = 0; i <= 2; ++i)
        printf("%d%c", color[i], i == 2 ? '\n' : ' ');
    return 0;
}