#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
//#define DEBUG

int T, N, M, K;
int grid[1000][1000];

struct Cell {
	int r, c, k, t;
	Cell(int _r, int _c, int _k, int _t) { r = _r; c = _c; k = _k; t = _t; }
};
vector <Cell> inactive, active;
vector <Cell> tmpI, tmpA;

int dir[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };

void solve()
{
	int nr, nc;

	while (K--)
	{
		for (int i = 0; i < inactive.size(); i++) //비활성
		{
			inactive[i].t++;
			if (inactive[i].k == inactive[i].t) //활성화 될 시간
			{
				inactive[i].t = 0; //소요 시간을 0으로 돌리고
				tmpA.push_back(inactive[i]); //활성화로 간다.
			}
			else //아직 비활성에 남아있어야 한다.
				tmpI.push_back(inactive[i]);
			
		}

		for (int i = 0; i < active.size(); i++) //활성
		{
			active[i].t++;
			
			for (int d = 0; d < 4; d++)//퍼트리기
			{
				nr = active[i].r + dir[d][0];
				nc = active[i].c + dir[d][1];

				if (grid[nr][nc] == 0) //세포가 없다
				{
					grid[nr][nc] = active[i].k;
					tmpI.push_back(Cell(nr, nc, grid[nr][nc], 0)); //비활성 상태로 퍼트리기
				}
			}

			if (active[i].k == active[i].t) //죽을 시간
				grid[active[i].r][active[i].c] = -1;
			else //아직 활성에 남아있어야 한다.
				tmpA.push_back(active[i]);
		}

		//다음 턴을 위해서.
		swap(inactive, tmpI);
		swap(active, tmpA);
		tmpI.clear();
		tmpA.clear();
	}
}

int main(void)
{
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		//init
		memset(grid, 0, sizeof(grid));
		inactive.clear();
		active.clear();

		//input
		cin >> N >> M >> K;
		for (int i = 500; i < 500 + N; i++)
		{
			for (int j = 500; j < 500 + M; j++)
			{
				cin >> grid[i][j];

				if (grid[i][j] > 0) //초기상태 = 비활성
					inactive.push_back(Cell(i, j, grid[i][j], 0));
			}
		}

		solve();

		//output
		cout << "#" << tc << " " << inactive.size() + active.size() << endl;
	}
	
}
