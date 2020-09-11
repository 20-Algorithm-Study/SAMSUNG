#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define DEBUG 
#define MAX 50

int R, C, T;
int A[MAX][MAX];
vector <pair<int, int>> m; //����û����

int dust[MAX][MAX];
int dir[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} };

int rslt = 0;

void solve()
{
	int spread = 0;
	int nr, nc;

	while (T--) //�ð���ŭ
	{
		//1. Ȯ��
		memset(dust, 0, sizeof(dust)); //0���� �ʱ�ȭ

		for (int r = 0; r < R; r++) //Ȯ��� ������ ���� ���Ѵ�
		{
			for (int c = 0; c < C; c++)
			{
				spread = A[r][c] / 5; //���� ĭ�� ������ ��Ʈ�� ������ ��
				
				if (A[r][c] == 0 || spread == 0) //��Ʈ�� ������ ����.
					continue;

				for (int d = 0; d < 4; d++) //������� Ȯ��
				{
					nr = r + dir[d][0];
					nc = c + dir[d][1];

					if (nr < 0 || nc < 0 || nr >= R || nc >= C || A[nr][nc] == -1) //���� ��� or ��û��
						continue;

					dust[nr][nc] += spread; //�ֺ��� ���ϱ�(Ȯ��)
					A[r][c] -= spread; //���� ĭ���� ���ֱ�
				}
			}
		}

		for (int r = 0; r < R; r++) //Ȯ��
		{
			for (int c = 0; c < C; c++)
				A[r][c] += dust[r][c];
		}

		//2. �۵�
		for (int r = m[0].first; r > 0; r--) //step. 1(��)
			A[r][0] = A[r - 1][0];

		for (int r = m[1].first; r < R - 1; r++) //step. 1(�Ʒ�)
			A[r][0] = A[r + 1][0];

		for (int c = 0; c < C - 1; c++)//step. 2
		{
			A[0][c] = A[0][c + 1]; //��
			A[R - 1][c] = A[R - 1][c + 1]; //�Ʒ�
		}

		for (int r = 0; r < m[0].first; r++) //step. 3(��)
			A[r][C - 1] = A[r + 1][C - 1];

		for (int r = R - 1; r > m[1].first; r--) //step. 3(�Ʒ�)
			A[r][C - 1] = A[r - 1][C - 1];

		for (int c = C - 1; c > 0; c--)//step. 4
		{
			A[m[0].first][c] = A[m[0].first][c - 1]; //��
			A[m[1].first][c] = A[m[1].first][c - 1]; //�Ʒ�
		}

		A[m[0].first][m[0].second] = A[m[1].first][m[1].second] = -1; //��û��� �׻� -1
		A[m[0].first][m[0].second + 1] = A[m[1].first][m[1].second + 1] = 0; //��û�⿡�� ���� ������ �ٶ��� �׻� 0
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
			if(A[i][j] != -1) //��û�� ����
				rslt += A[i][j];
		}
	}
	cout << rslt << endl;
}