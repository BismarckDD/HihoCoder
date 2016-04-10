/*#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
int Task,N;
int a[100005];
vector<int> yes, no;
int main()
{
	scanf("%d", &Task);
	while(Task--)
	{
		scanf("%d", &N);
	    for (int i = 1; i <= N; ++i)
		    scanf("%s", a+i);
		for (int i = 1; i <= N; ++i)
		{
			if (i == 1) {
				if (a[i] == 0) {
					yes.push_back(1);
					yes.push_back(2);
					i += 1;
				}
				else if (a[i] == 2) {
					no.push_back(1);
					no.push_back(2);
					i += 1;
				}
			} 
			else if (i == N) {

			}
			else {

			}
		}

	}
	return 0;
}*/