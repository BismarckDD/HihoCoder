#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
int T;
int find(int i, int k)
{
	int tmp;
	while (k > 0)
	{
		tmp = i % 4;
		if (tmp == 2 || tmp == 3)
			return k;
		else
			i = (i & 3) ? (i >> 2) + 1 : (i >> 2);
		k--;
		//printf("%d %d\n", k, i);
	}
	return k;
}
int main()
{
	int i, k;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d %d", &i, &k);
		printf("%d\n", find(i, k));
	}
	return 0;
}

