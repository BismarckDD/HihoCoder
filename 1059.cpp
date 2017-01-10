#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 2101;
int len1, len2, dp[MAXN][MAXN]={0},f[MAXN][MAXN]={0};
char str1[MAXN];
char str2[MAXN];

inline int mymax(int a, int b)
{
	return a>b?a:b;
}

int main()
{
	scanf("%s",str1);
	scanf("%s",str2);
    len1 = strlen(str1);
	len2 = strlen(str2);
	for(int i=0;i<len1;++i) 
		for(int j=0;j<len2;++j)
			if(str1[i]==str2[j])
				f[i+1][j+1]=f[i][j]+1;
		    else
				f[i+1][j+1]=0;
	for(int i=0;i<len1;++i)
		for(int j=0;j<len2;++j)
		{
			dp[i+1][j+1] = mymax(dp[i+1][j],dp[i][j+1]);
			if(f[i+1][j+1]>=3)
			{
				for(int k=3;k<=f[i+1][j+1];++k)
					dp[i+1][j+1] = mymax(dp[i+1][j+1],dp[i+1-k][j+1-k]+k);
			}
		}
    printf("%d\n",dp[len1][len2]);	
	return 0;
}
