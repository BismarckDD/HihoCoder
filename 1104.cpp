#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int inf = -1;

vector<int> children[101];

int n, m, k;
int dp[101][101];
int attractive[101];

void dfs(int u, int m)
{
	dp[u][1] = attractive[u];
	for (size_t i = 0; i < children[u].size(); i++)
	{
		dfs(children[u][i], m-1);
		for (size_t x = m; x >= 1; x--)
		{
			if (dp[u][x] > inf)
				for (size_t y = 0; y <= m - x; y++)
					if (dp[children[u][i]][y] != inf)
						dp[u][x + y] = max(dp[u][x + y], dp[u][x] + dp[children[u][i]][y]);
		}
	}
}

int main()
{
	int t;
	cin >> n >> k >> m;
	for (size_t i = 1; i <= n; i++)
		cin >> attractive[i];
	for (size_t i = 1; i <= k; i++)
		cin >> t, attractive[t] += 20000;
	for (size_t i = 1; i<n; i++)
	{
		size_t a, b;
		cin >> a >> b;
		children[a].push_back(b);
	}
	
	if (k > m || m > n)
	{
		cout << -1 << endl;
		return 0;
	}
	for (size_t i = 0; i <= n; i++)
		for (size_t j = 0; j <= m; j++)
			dp[i][j] = inf;
	dfs(1, m);
	cout << dp[1][m] - 20000 * k << endl;
	//system("pause");
	return 0;
}


