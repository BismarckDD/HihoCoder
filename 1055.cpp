#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
const int MAXN = 101;
int Value[MAXN];
vector<int> Children[MAXN];
int dp[MAXN][MAXN];
int n, m;

void dfs(int u, int p, int m)
{
	for (int i = 1; i <= m; i++)
		dp[u][i] = Value[u];

	for (int v : Children[u])
	{
		if (v == p) continue;
		dfs(v, u, m-1);
		for (int i = m; i > 0; i--)
			for (int j = m - i; j > 0; j--)
				dp[u][i + j] = max(dp[u][i + j], dp[u][i] + dp[v][j]);
	}
}

int main()
{
	int u, v;
	scanf("%d %d", &n, &m);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			dp[i][j] = 0;
	for (int i = 1; i <= n; i++)
		scanf("%d", &Value[i]);

	for (int i = 1; i < n; i++)
	{
		scanf("%d %d", &u, &v);
		Children[u].push_back(v);
		Children[v].push_back(u);
	}
	dfs(1, 0, m);
	printf("%d\n", dp[1][m]);

	return 0;
}
