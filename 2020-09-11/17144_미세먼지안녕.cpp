#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define DEBUG 
#define MAX 50

int R, C, T;
int A[MAX][MAX];
vector <pair<int, int>> m; //공기청정기

int dust[MAX][MAX];
int dir[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} };

int rslt = 0;

void solve()
{
	int spread = 0;
	int nr, nc;

	while (T--) //시간만큼
	{
		//1. 확산
		memset(dust, 0, sizeof(dust)); //0으로 초기화

		for (int r = 0; r < R; r++) //확산될 먼지의 양을 구한다
		{
			for (int c = 0; c < C; c++)
			{
				spread = A[r][c] / 5; //현재 칸이 옆으로 퍼트릴 먼지의 양
				
				if (A[r][c] == 0 || spread == 0) //퍼트릴 먼지가 없다.
					continue;

				for (int d = 0; d < 4; d++) //사방으로 확산
				{
					nr = r + dir[d][0];
					nc = c + dir[d][1];

					if (nr < 0 || nc < 0 || nr >= R || nc >= C || A[nr][nc] == -1) //범위 벗어남 or 공청기
						continue;

					dust[nr][nc] += spread; //주변에 더하기(확산)
					A[r][c] -= spread; //현재 칸에서 없애기
				}
			}
		}

		for (int r = 0; r < R; r++) //확산
		{
			for (int c = 0; c < C; c++)
				A[r][c] += dust[r][c];
		}

		//2. 작동
		for (int r = m[0].first; r > 0; r--) //step. 1(위)
			A[r][0] = A[r - 1][0];

		for (int r = m[1].first; r < R - 1; r++) //step. 1(아래)
			A[r][0] = A[r + 1][0];

		for (int c = 0; c < C - 1; c++)//step. 2
		{
			A[0][c] = A[0][c + 1]; //위
			A[R - 1][c] = A[R - 1][c + 1]; //아래
		}

		for (int r = 0; r < m[0].first; r++) //step. 3(위)
			A[r][C - 1] = A[r + 1][C - 1];

		for (int r = R - 1; r > m[1].first; r--) //step. 3(아래)
			A[r][C - 1] = A[r - 1][C - 1];

		for (int c = C - 1; c > 0; c--)//step. 4
		{
			A[m[0].first][c] = A[m[0].first][c - 1]; //위
			A[m[1].first][c] = A[m[1].first][c - 1]; //아래
		}

		A[m[0].first][m[0].second] = A[m[1].first][m[1].second] = -1; //공청기는 항상 -1
		A[m[0].first][m[0].second + 1] = A[m[1].first][m[1].second + 1] = 0; //공청기에서 새로 나오는 바람은 항상 0
	}
	
}

int main()
{
	//input
	cin >> R >> C >> T;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> A[i][j];

			if (A[i][j] == -1)
				m.push_back(make_pair(i, j));
		}
	}

	solve();

	//output
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if(A[i][j] != -1) //공청기 제외
				rslt += A[i][j];
		}
	}
	cout << rslt << endl;
}