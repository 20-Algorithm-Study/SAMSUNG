#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define DEBUG 
#define MAX 8
#define WALL 3

int N, M;
int map[MAX][MAX];
int wall = WALL; //세우려고 하는 만큼(3)은 기본으로 깔고 시작
vector <pair<int, int>> virus, emp; //바이러스, 빈 공간
vector <int> pick; //벽을 세울 곳

queue <pair<int, int>> q;
int visited[MAX][MAX] = { 0, };
int turn = 0; //바이러스 퍼트리는 시뮬레이션의 회차
int dir[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };

int rslt = 0; //결과값

void spread_virus() //바이러스 퍼트리기(BFS)
{
	int r, c, nr, nc;
	int cnt = 0;

	turn++; //회차

	for (int i = 0; i < virus.size(); i++) //큐에 삽입
	{
		q.push(make_pair(virus[i].first, virus[i].second));
		visited[virus[i].first][virus[i].second] = turn;
	}

	while (!q.empty())
	{
		r = q.front().first;
		c = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) //사방으로 퍼져나간다
		{
			nr = r + dir[i][0];
			nc = c + dir[i][1];

			if (nr < 0 || nc < 0 || nr >= N || nc >= M || visited[nr][nc] == turn) //범위 벗어났거나 이미 방문
				continue;

			if (map[nr][nc] == 1) // 벽
				continue;

			q.push(make_pair(nr, nc)); //바이러스 이동
			visited[nr][nc] = turn;
		}
	}

	for (int i = 0; i < N; i++) //안전영역 크기 구하기
	{
		for (int j = 0; j < M; j++)
		{
			if (visited[i][j] != turn) //바이러스가 방문하지 못한 곳
				cnt++;
		}
	}
	cnt -= wall; //벽은 제외
	rslt = rslt > cnt ? rslt : cnt; //최댓값 찾기
}

void comb(int cnt) //벽 세울 위치 뽑기(조합)(DFS)
{
	if (pick.size() == WALL) //벽 세울 자리 3곳 다 뽑으면
	{
		for (int i = 0; i < pick.size(); i++) //벽 세우기
			map[emp[pick[i]].first][emp[pick[i]].second] = 1;

		spread_virus(); //바이러스 퍼트리기

		for (int i = 0; i < pick.size(); i++) //다시 빈 공간으로
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

			if (map[i][j] == 0) //빈칸
				emp.push_back(make_pair(i, j));
			else if (map[i][j] == 1) // 벽
				wall++;
			else //바이러스
				virus.push_back(make_pair(i, j));
		}
	}

	comb(0); //solve

	//output
	cout << rslt << endl;
}