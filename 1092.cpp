//#include<cstdio>
//#include<iostream>
//#include<vector>
//using namespace std;
//
//int N, M;
//char map[102][102];
//bool visit[102][102];
//int dir[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
//struct node
//{
//	int x, y, step;
//	void set(int px, int py)
//	{
//		x = px;
//		y = py;
//		step = 0;
//	}
//};
//node st;
//vector<node> seat;
//vector<int> ans;
//void bfs(node st)
//{
//	node q[10005],t;
//	int rear = 0, front = 0;
//	q[front++] = st;
//	visit[st.x][st.y] = true;
//	while (rear < front)
//	{
//		node tmp = q[rear++];
//		for (int i = 0; i <= 3; ++i)
//		{
//			int x = tmp.x + dir[i][0];
//			int y = tmp.y + dir[i][1];
//			if (x <= N && x >= 1 && y <= M && y >= 1)
//			{
//				t.x = x;
//				t.y = y;
//				t.step = tmp.step + 1;
//				if (map[x][y] == '.' && visit[x][y] == false)
//					q[front++] = t;
//				if (map[x][y] == 'S' && visit[x][y] == false)
//					seat.push_back(t);
//				visit[x][y] = true;
//			}
//		}
//		
//	}
//}
//int main()
//{
//	scanf("%d %d", &N, &M);
//	for (int i = 1; i <= N; ++i)
//	{
//		scanf("%s", map[i] + 1);
//		for (int j = 1; j <= M; ++j)
//		{
//			visit[i][j] = false;
//			if (map[i][j] == 'H')
//				st.set(i, j);
//		}
//	}
//	bfs(st);
//	for (int i = 0; i < seat.size(); ++i)
//		for (int j = i+1; j < seat.size(); ++j)
//			if (abs(seat[i].x - seat[j].x) + abs(seat[i].y - seat[j].y) == 1)
//				ans.push_back(seat[i].step + seat[j].step);
//	//printf("%c\n", map[6][9]);
//	if (ans.size() == 0)
//		printf("Hi and Ho will not have lunch.\n");
//	else
//	{ 
//		int minAns = ans[0];
//		for (int i = 1; i < ans.size(); ++i)
//			if (minAns > ans[i])
//				minAns = ans[i];
//		printf("%d\n", minAns);
//
//	}
//	return 0;
//}