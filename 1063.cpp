#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstdio>
using namespace std;
const int inf = 1 << 29;
const int MAXN = 101;
const int MAXM = 200;
int Value[MAXN];
vector<int> Children[MAXN];
int Edge[MAXN][MAXN];
int dp[MAXN][2][MAXM+1];
map<int, int> ans;

void dfs(int u, int p) 
{	
	for (int i = 0; i <= Value[u]; i++) 
		dp[u][0][i] = dp[u][1][i] = 0;

	for (int v : Children[u]) 
	{
		if (v == p) continue;
		dfs(v, u);
		for (int i = MAXM; i >= 0; i--)
		{
			for (int j = MAXM - i; j > 0; j--)
			{
				dp[u][0][i + j] = min(dp[u][0][i + j], dp[u][0][i] + dp[v][0][j] + 2 * Edge[u][v]);
				dp[u][1][i + j] = min(dp[u][1][i + j], dp[u][1][i] + dp[v][0][j] + 2 * Edge[u][v]);
				dp[u][1][i + j] = min(dp[u][1][i + j], dp[u][0][i] + dp[v][1][j] + 1 * Edge[u][v]);
			}
		}
	}
}

int main()
{
	//ios::sync_with_stdio(false);
	//cin.tie(0);
//	printf("%d\n", inf);
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k <= MAXM; k++)
				dp[i][j][k] = inf;

	int n, u, v, w;
	scanf("%d", &n);
	//cin >> n;

	for (int i = 1; i <= n; i++)
		scanf("%d", &Value[i]);
	//cin >> Value[i];

	for (int i = 1; i < n; i++)
	{
		scanf("%d %d %d", &u, &v, &w);
		//cin >> u >> v >> w;
		Children[u].push_back(v);
		Children[v].push_back(u);
		Edge[u][v] = w;
		Edge[v][u] = w;
	}
	dfs(1, 0);
	ans[0] = 0;
	for (int i = 1; i <= MAXM; i++)
	{
		int d = min(dp[1][0][i], dp[1][1][i]);
		ans[d] = i;
	}
	int q, d;
	scanf("%d", &q);
	//cin >> q;
	for (int i = 1; i <= q; i++)
	{
		scanf("%d", &d);
		//cin >> d;
		auto it = ans.upper_bound(d);
		printf("%d\n", (--it)->second);
	}
	return 0;
}
