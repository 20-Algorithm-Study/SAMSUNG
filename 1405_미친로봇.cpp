#include <iostream>
using namespace std;
#define MAX 15

int N;
double prob[4];

int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };
bool visited[MAX*2][MAX*2];
double rslt = 0;

void dfs(int n, int r, int c, double p) //이동 횟수, 행, 열, 확률
{
	int nr, nc;

	if (n == 0)
	{
		rslt += p;
		return;
	}
	for (int d = 0; d < 4; d++)
	{
		nr = r + dir[d][0];
		nc = c + dir[d][1];

		if (visited[nr][nc]) //이미 방문한 곳은 제외
			continue;

		visited[nr][nc] = true;
		dfs(n - 1, nr, nc, p * prob[d]);
		visited[nr][nc] = false;
	}
}

int main()
{
	//input
	cin >> N;
	for (int i = 0; i < 4; i++)
	{
		cin >> prob[i];
		prob[i] /= 100;
	}

	//solve
	visited[15][15] = true; //시작지점은 15,15
	dfs(N, 15, 15, 1);

	//output
	cout.precision(11); 
	cout << fixed;
	cout << rslt << endl;
}