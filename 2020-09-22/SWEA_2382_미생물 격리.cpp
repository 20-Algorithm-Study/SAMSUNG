#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define DEBUG
#define MAX 101

int T;
int N, M, K;
struct Micro {
	int n, r, c, cnt, d; //번호, 행, 렬, 개수, 이동방향
	Micro(int _n, int _r, int _c, int _cnt, int _d) { n = _n; r = _r; c = _c; cnt = _cnt; d = _d; }
};
vector <Micro> micro; //미생물

vector<int> map[MAX][MAX];
vector <Micro> maxM; //2개이상 군집이 모였을 때 best를 찾는 용도

int dir[5][2] = { {0,0}, {-1,0}, {1,0}, {0,-1}, {0,1} }; //그대로.상.하.좌.우
int reverseDir[5] = { 0, 2, 1, 4, 3 }; //그대로.하.상.우.좌

int rslt = 0; //결과값

bool compare(Micro a, Micro b)
{
	return a.cnt > b.cnt;
}

void solve()
{
	while (M--) // M 시간만큼
	{
		//초기화
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				map[i][j].clear();
		}

		for (int i = 0; i < micro.size(); i++) //모든 군집
		{
			if (micro[i].cnt == 0) // 미생물 수가 없음 = 죽음
				continue;

			//군집 이동
			micro[i].r += dir[micro[i].d][0];
			micro[i].c += dir[micro[i].d][1];
			map[micro[i].r][micro[i].c].push_back(i); //이동 후 해당 map 위치에 넣는다

			//약품 셀에 진입
			if (micro[i].r < 1 || micro[i].c < 1 || micro[i].r >= N - 1 || micro[i].c >= N - 1) 
			{
				micro[i].d = reverseDir[micro[i].d]; //방향전환
				micro[i].cnt /= 2; //절반 죽는다
			}
		}

		for (int i = 0; i < micro.size(); i++) //모든 군집
		{
			if (micro[i].cnt == 0) // 미생물 수가 없음 = 죽음
				continue;

			if (map[micro[i].r][micro[i].c].size() > 1) //2개 이상의 군집이 모였다
			{
				int sum = 0;
				maxM.clear(); //초기화

				for (int j = 0; j < map[micro[i].r][micro[i].c].size(); j++) //해당 map 위치에 있는 모든 미생물 군집
				{
					maxM.push_back(micro[map[micro[i].r][micro[i].c][j]]); //maxM에 삽입
					sum += micro[map[micro[i].r][micro[i].c][j]].cnt; //각 군집의 미생물 개수를 더한다
					micro[map[micro[i].r][micro[i].c][j]].cnt = 0; //미생물 개수 0으로 초기화(죽음)
				}

				sort(maxM.begin(), maxM.end(), compare); //정렬해서 미생물이 가장 많은 군집을 찾는다
				micro[maxM[0].n].cnt = sum; //미생물이 가장 많은 군집으로 모든 미생물이 간다.(다른 군집은 죽음)
			}
		}
	}
}

int main()
{
	int r, c, n, d;

	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		//init
		micro.clear();

		//input
		cin >> N >> M >> K;
		for (int i = 0; i < K; i++)
		{
			cin >> r >> c >> n >> d;
			micro.push_back(Micro(i, r, c, n, d));
		}

		solve();

		//output
		rslt = 0;
		for (int i = 0; i < micro.size(); i++)
			rslt += micro[i].cnt;
		cout << "#" << tc << " " << rslt << endl;
	}

}