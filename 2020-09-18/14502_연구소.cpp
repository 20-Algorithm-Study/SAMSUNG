#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define DEBUG 
#define MAX 8
#define WALL 3

int N, M;
int map[MAX][MAX];
int wall = WALL; //������� �ϴ� ��ŭ(3)�� �⺻���� ��� ����
vector <pair<int, int>> virus, emp; //���̷���, �� ����
vector <int> pick; //���� ���� ��

queue <pair<int, int>> q;
int visited[MAX][MAX] = { 0, };
int turn = 0; //���̷��� ��Ʈ���� �ùķ��̼��� ȸ��
int dir[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };

int rslt = 0; //�����

void spread_virus() //���̷��� ��Ʈ����(BFS)
{
	int r, c, nr, nc;
	int cnt = 0;

	turn++; //ȸ��

	for (int i = 0; i < virus.size(); i++) //ť�� ����
	{
		q.push(make_pair(virus[i].first, virus[i].second));
		visited[virus[i].first][virus[i].second] = turn;
	}

	while (!q.empty())
	{
		r = q.front().first;
		c = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) //������� ����������
		{
			nr = r + dir[i][0];
			nc = c + dir[i][1];

			if (nr < 0 || nc < 0 || nr >= N || nc >= M || visited[nr][nc] == turn) //���� ����ų� �̹� �湮
				continue;

			if (map[nr][nc] == 1) // ��
				continue;

			q.push(make_pair(nr, nc)); //���̷��� �̵�
			visited[nr][nc] = turn;
		}
	}

	for (int i = 0; i < N; i++) //�������� ũ�� ���ϱ�
	{
		for (int j = 0; j < M; j++)
		{
			if (visited[i][j] != turn) //���̷����� �湮���� ���� ��
				cnt++;
		}
	}
	cnt -= wall; //���� ����
	rslt = rslt > cnt ? rslt : cnt; //�ִ� ã��
}

void comb(int cnt) //�� ���� ��ġ �̱�(����)(DFS)
{
	if (pick.size() == WALL) //�� ���� �ڸ� 3�� �� ������
	{
		for (int i = 0; i < pick.size(); i++) //�� �����
			map[emp[pick[i]].first][emp[pick[i]].second] = 1;

		spread_virus(); //���̷��� ��Ʈ����

		for (int i = 0; i < pick.size(); i++) //�ٽ� �� ��������
			map[emp[pick[i]].first][emp[pick[i]].second] = 0;

		return;
	}

	for (int i = cnt; i < emp.size(); i++)
	{
		pick.push_back(i);
		comb(i + 1);
		pick.pop_back();
	}
}

int main()
{
	//input
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 0) //��ĭ
				emp.push_back(make_pair(i, j));
			else if (map[i][j] == 1) // ��
				wall++;
			else //���̷���
				virus.push_back(make_pair(i, j));
		}
	}

	comb(0); //solve

	//output
	cout << rslt << endl;
}