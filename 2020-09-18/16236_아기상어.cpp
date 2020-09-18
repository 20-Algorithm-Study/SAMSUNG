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

bool compare(Fish a, Fish b) //물고기 정렬을 위해서..
{
	if (a.d == b.d)
	{
		if (a.r == b.r)
			return a.c < b.c; //더 왼쪽
		else
			return a.r < b.r; //더 위
	}
	else 
		return a.d < b.d; //더 가까운
}

void bfs()
{
	int r, c, nr, nc;

	//init
	memset(visited, 0, sizeof(visited));
	fish.clear();

	q.push(make_pair(shark.r, shark.c)); //상어 위치를 큐에 삽입
	visited[shark.r][shark.c] = 1;

	while (!q.empty())
	{
		r = q.front().first;
		c = q.front().second;
		q.pop();

		if (!fish.empty() && visited[r][c] > fish[fish.size() - 1].d) //현재 먹을 수 있는 물고기보다 먼 곳에 있는건 먹을 필요가 없음
			continue;

		for (int i = 0; i < 4; i++)
		{
			nr = r + dir[i][0];
			nc = c + dir[i][1];

			if (nr < 0 || nc < 0 || nr >= N || nc >= N || visited[nr][nc] > 0) //범위 벗어남 or 이미 방문
				continue;

			if(map[nr][nc] > shark.size) //상어보다 큰 물고기 = 지나갈 수 없다
				continue;
		
			if (map[nr][nc] != 0 && map[nr][nc] < shark.size) //상어보다 작은 물고기 = 먹을 수 있다
				fish.push_back(Fish(nr, nc, visited[r][c]));

			q.push(make_pair(nr, nc)); //상어가 이동 가능한 곳
			visited[nr][nc] = visited[r][c] + 1;
		}
	}

	sort(fish.begin(), fish.end(), compare); //먹을 수 있는 물고기 정렬
}

void solve()
{
	while (true)
	{
		//1. 먹을 물고기를 고른다
		bfs();

		if (fish.empty()) //더이상 먹을 물고기가 없다. = 엄마 상어에 도움 요청
			break;

		//2. 먹는다
		map[shark.r][shark.c] = 0; //이동
		map[fish[0].r][fish[0].c] = 9;

		shark.r = fish[0].r; //상어 상태 변경
		shark.c = fish[0].c;
		shark.eat++;

		if (shark.size == shark.eat) //상어 크기만큼 물고기 먹으면 상어 사이즈 업
		{
			shark.size++;
			shark.eat = 0;
		}

		//3. 시간이 지나간다
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

			if (map[i][j] == 9) //상어
				shark = Shark(i, j, 2, 0); // r, c, 상어 사이즈, 먹은 물고기 수
		}
	}

	solve();

	//output
	cout << time << endl;
}