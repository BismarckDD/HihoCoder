#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>

#define mod 1000000007
#define ll long long
using namespace std;
struct node
{
    ll cnt,sum;
    node()
    {
        cnt = -1;
        sum = 0;
    }
} dp[22][402][2][202];
int num[22],k;
ll ten[22];
ll l,r;

node dfs(int site,int sum,int p,int f,int zero)
{
    if(site==0)
    {
        node a;
        if( zero==1 || sum!=k+200) a.cnt=0;
        else a.cnt=1;
        return a;
    }
    if(!f && !zero && dp[site][sum][p][k].cnt!=-1) return dp[site][sum][p][k];
    int len=f?num[site]:9;
    node ans,cur;
    ans.cnt=0;
    for(int i=0; i<=len; i++)
    {
        if(zero && i==0) cur=dfs(site-1,sum,p,f&&i==len,1);
        else
        {
            if(p==0) cur=dfs(site-1,sum+i,p^1,f&&i==len,0);
            else cur=dfs(site-1,sum-i,p^1,f&&i==len,0);
        }
        ll tep=(i*ten[site])%mod;
        ans.cnt=(ans.cnt+cur.cnt)%mod;
        ans.sum=(ans.sum+cur.sum+cur.cnt*tep)%mod;
    }
    if(!f && !zero) dp[site][sum][p][k]=ans;
    return ans;
}

ll solve(ll x)
{
    if(x<0) return 0;
    int cnt=0;
    while(x)
    {
        num[++cnt] = x%10;
        x /= 10;
    }
    node ans = dfs(cnt, 200, 0, 1, 1);
    return ans.sum;
}

int main()
{
    ten[1]=1;
    for(int i=2; i<=20; i++)
        ten[i]=(ten[i-1]*10)%mod;
    while(scanf(%lld%lld%d,&l,&r,&k) != EOF)
    {
        printf(%lld,((solve(r)-solve(l-1))%mod+mod)%mod);
    }
    return 0;
}