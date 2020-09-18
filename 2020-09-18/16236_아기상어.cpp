#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
//#define DEBUG 
#define MAX 20

int N;
int map[MAX][MAX];
int time = 0;

struct Shark {
	int r, c, size, eat;
	Shark() {}
	Shark(int _r, int _c, int _size, int _eat) { r = _r; c = _c; size = _size; eat = _eat; }
} shark;

struct Fish {
	int r, c, d;
	Fish(int _r, int _c, int _d) { r = _r; c = _c; d = _d; }
};
vector <Fish> fish;

queue<pair<int, int>> q;
int visited[MAX][MAX] = { 0, };
int dir[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };

bool compare(Fish a, Fish b) //����� ������ ���ؼ�..
{
	if (a.d == b.d)
	{
		if (a.r == b.r)
			return a.c < b.c; //�� ����
		else
			return a.r < b.r; //�� ��
	}
	else 
		return a.d < b.d; //�� �����
}

void bfs()
{
	int r, c, nr, nc;

	//init
	memset(visited, 0, sizeof(visited));
	fish.clear();

	q.push(make_pair(shark.r, shark.c)); //��� ��ġ�� ť�� ����
	visited[shark.r][shark.c] = 1;

	while (!q.empty())
	{
		r = q.front().first;
		c = q.front().second;
		q.pop();

		if (!fish.empty() && visited[r][c] > fish[fish.size() - 1].d) //���� ���� �� �ִ� ����⺸�� �� ���� �ִ°� ���� �ʿ䰡 ����
			continue;

		for (int i = 0; i < 4; i++)
		{
			nr = r + dir[i][0];
			nc = c + dir[i][1];

			if (nr < 0 || nc < 0 || nr >= N || nc >= N || visited[nr][nc] > 0) //���� ��� or �̹� �湮
				continue;

			if(map[nr][nc] > shark.size) //���� ū ����� = ������ �� ����
				continue;
		
			if (map[nr][nc] != 0 && map[nr][nc] < shark.size) //���� ���� ����� = ���� �� �ִ�
				fish.push_back(Fish(nr, nc, visited[r][c]));

			q.push(make_pair(nr, nc)); //�� �̵� ������ ��
			visited[nr][nc] = visited[r][c] + 1;
		}
	}

	sort(fish.begin(), fish.end(), compare); //���� �� �ִ� ����� ����
}

void solve()
{
	while (true)
	{
		//1. ���� ����⸦ ����
		bfs();

		if (fish.empty()) //���̻� ���� ����Ⱑ ����. = ���� �� ���� ��û
			break;

		//2. �Դ´�
		map[shark.r][shark.c] = 0; //�̵�
		map[fish[0].r][fish[0].c] = 9;

		shark.r = fish[0].r; //��� ���� ����
		shark.c = fish[0].c;
		shark.eat++;

		if (shark.size == shark.eat) //��� ũ�⸸ŭ ����� ������ ��� ������ ��
		{
			shark.size++;
			shark.eat = 0;
		}

		//3. �ð��� ��������
		time += fish[0].d;
	}
}

int main()
{
	//input
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 9) //���
				shark = Shark(i, j, 2, 0); // r, c, ��� ������, ���� ����� ��
		}
	}

	solve();

	//output
	cout << time << endl;
}