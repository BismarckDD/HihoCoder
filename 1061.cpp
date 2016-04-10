#include<cstdio>
#include<iostream>
#include<string>
using namespace std;
int T, len;
const int MAXN = (1 << 20) * 10 + 10;
char str[MAXN];
int num[MAXN];
bool flag = false;
int main()
{
	int i, k;
	scanf("%d", &T);
	while (T--)
	{
		flag = false;
		scanf("%d %s", &len, str);
		for (int i = 0,j,k; i < len; i = j)
		{
			for (j = i + 1; j < len; ++j)
				if (str[j] != str[i])
					break;
			num[i] = j - i;
			for (k = i + 1; k < j; ++k)
				num[k] = num[k - 1] - 1;
		}
		int s1, s2, s3;
		for (int i = 0; i < len && !flag; ++i)
		{
			s1 = i;
			s2 = s1 + num[s1];
			if (s2 >= len) continue;
			s3 = s2 + num[s2];
			if (s3 >= len) continue;
			if (num[s1] >= num[s2] &&
				num[s2] <= num[s3] &&
				str[s1] + 1 == str[s2] &&
				str[s2] + 1 == str[s3])
				flag = true;
		}
		if (flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
