#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;

map<string, int> phrase;
map<string, int>::iterator phraseiter;
int getline(char *buff)
{
    char ch;
    int i = 0;
    while ((ch = getchar()) != EOF)
    {
        if (ch != '\n' && ch != '\r')
            *(buff + i++) = ch;
        else if (ch == '\r') continue;
        else
        {
            *(buff + i) = '\0';
            return i;
        }
    }
    return EOF;
}

bool isLegal(char ch)
{
    return ch <= 'z' && ch >= 'a';
}

int main()
{
    int len;
    char buffer[510], word[510];
    bool flag = true, vis[510];
    int maxfre = 0;
    vector<string> vec;
    string ans = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    while ((len = getline(buffer)) != EOF)
    {   
        if (strcmp(buffer, "####") == 0)
        {
            printf("%s:%d\n", ans.c_str(), phrase[ans]);
            phrase.clear();
            ans = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
            maxfre = 0;
            continue;
        }
        memset(vis, -1, sizeof(vis));
        for (int i = 0, j = 0, k = 0; i <= len; ++i)
        {
            if (isLegal(buffer[i])) word[j++] = buffer[i];
            else if (j > 0)
            {
                word[j] = '\0';
                string s(word);
                vec.push_back(s);
                j = 0;
                vis[++k] &= (buffer[i] == ' ');
            }
            else vis[k] &= (buffer[i] == ' ');
        }
        int ed = vec.size() - 1;
        for (int i = 0; i < ed; ++i)
        {
            if (!vis[i+1]) continue;
            string key = vec[i] + " " + vec[i + 1];
            phraseiter = phrase.find(key);
            ++phrase[key];
            if (phrase[key] > maxfre || phrase[key] == maxfre && key < ans)
            {
                maxfre = phrase[key];
                ans = key;
            }
        }
        vec.clear();
    }
    return 0;
}