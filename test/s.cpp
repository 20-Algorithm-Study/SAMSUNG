#include <iostream>
#include <queue>
using namespace std;
#define DEBUG 
#define MAX 1001


int W, H;
char map[MAX][MAX];

int dir[8][2] = { {-1,-1}, {-1,0}, {-1,1}, { 0,-1}, {0,1}, {1,-1}, {1,0}, {1,1} };

queue<pair<int, int>> q, nq;
int visited[MAX][MAX] = { 0, };

int rslt = 0;

void bfs()
{
	int r, c, nr, nc;

	while (true)
	{
		rslt++; //���° �ĵ�

		while (!q.empty())
		{
			r = q.front().first;
			c = q.front().second;
			q.pop();

			for (int i = 0; i < 8; i++) //8���� Ȯ��
			{
				nr = r + dir[i][0];
				nc = c + dir[i][1];

				if (nr < 0 || nc < 0 || nr >= W || nc >= H) //���� ���
					continue;

				visited[nr][nc]++; //�ֺ��� �𷡼��� �׿����� ���� �κ��� ����

				if (map[nr][nc] != '.' && visited[nr][nc] >= map[nr][nc] - '0') //��������
				{

					map[nr][nc] = '.';
					nq.push(make_pair(nr, nc));
#ifdef DEBUG
					cout << nr << " " << nc << endl;
#endif
				}
			}
		}

#ifdef DEBUG
		cout << "���� ������ �� : " << nq.size() << endl;

		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
				cout << map[i][j];
			cout << endl;
		}
		cout << endl;
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
				cout << visited[i][j];
			cout << endl;
		}
#endif
		swap(q, nq);
		if (q.empty()) //��
			break;
		while (!nq.empty()) //����
			nq.pop();
	}
}

int main()
{
	//input
	cin >> H >> W;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == '.')
				q.push(make_pair(i, j));
		}
	}

	//solve
	bfs();

	//output
	cout << rslt << endl;

}