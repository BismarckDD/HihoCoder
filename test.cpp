#include<cstdio>  
#include<cstring>  
#include<string.h>  
#include<algorithm>  
#include<math.h>  
#include<cmath>  
#include<map>  
#include<string>  
#include<iostream>  
using namespace std;

const int maxn = 5000;
char s[maxn];
string str, ans;
int maxlen;
map<string, int> mp;

int main() {
    //freopen("input.txt","r",stdin);  
    mp.clear();
    maxlen = 0; ans = "zzzzzzzzzzzzzzzzzz";
    while (gets_s(s + 1, maxn-2)) {
        if (s[1] == '#') {
            cout << ans << ":" << maxlen << endl;
            maxlen = 0; ans = "zzzzzzzzzzzzzzzzzz";
            mp.clear();
        }
        //cout<<s<<endl;  
        int len = strlen(s + 1), i, j, k, jj, kk, pos;
        s[0] = s[len + 1] = '#';
        for (i = 1; i <= len; i++)
            if (s[i] == ' ') {
                k = i; j = i - 1;
                while (s[k] == ' ') k++;
                jj = j - 1; kk = k;
                while (s[jj] >= 'a'&&s[jj] <= 'z') jj--;
                while (s[kk] >= 'a'&&s[kk] <= 'z') kk++;
                //if (jj==j) continue;  
                //if (kk==k) continue;  
                //if (jj==0) jj++;  
                str = "";
                for (pos = jj + 1; pos <= j; pos++) str = str + s[pos];
                str = str + ' ';
                for (pos = k; pos<kk; pos++) str = str + s[pos];
                //cout<<str<<endl;  
                mp[str]++;
                if ((mp[str]>maxlen) || (mp[str] == maxlen&&ans>str)) {
                    maxlen = mp[str];
                    ans = str;
                }
                i = kk - 1;
            }
    }
    return 0;
}