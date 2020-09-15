#include <iostream>
#include <cstring>
using namespace std;

#define MAX 100
//#define DEBUG

int T, N, X;
int map[MAX][MAX];
bool slope[MAX][MAX];
int cnt = 0;

bool make_slope_down(int r, int c) //내려가는 경사로
{
	if (c + X > N) //배열 범위 벗어남
		return false;

	for (int nc = c; nc < c + X; nc++) 
	{
		if (slope[r][nc]) //이미 경사로가 있음
			return 0;
		if (map[r][nc] != map[r][c]) //경사로 놓아야하는 구간이 평평하지 않음(높이가 다름)
			return 0;
		slope[r][nc] = true;
	}

	return true;
}

int make_slope_up(int r, int c) //올라가는 경사로
{
	if (c - X < 0) //배열 범위 벗어남
		return false;

	for (int nc = c - X; nc < c; nc++)
	{
		if (slope[r][nc]) //이미 경사로가 있음
			return 0;
		if (map[r][nc] != map[r][c - 1]) //경사로 놓아야하는 구간이 평평하지 않음(높이가 다름)
			return 0;
		slope[r][nc] = true;
	}

	return true;
}

bool is_street(int r)
{
	int c = 1;

	while (c < N)
	{
		if (map[r][c - 1] == map[r][c]) //높이가 같은 경우는 한 칸만 이동
			c++;
		else if (map[r][c - 1] - 1 == map[r][c] && make_slope_down(r, c)) //내려가는 경사로 + 경사로 만들기 가능
			c += X;
		else if (map[r][c - 1] + 1 == map[r][c] && make_slope_up(r, c)) //올라가는 경사로 + 경사로 만들기 가능
			c++;
		else  //경사로를 못 만든다(높이 차가 1 초과 or X 만큼 공간이 없음)
			return false;
	}

	return true;
}
void solve()
{
	//행
	for (int r = 0; r < N; r++)
	{
		if (is_street(r))
			cnt++;
	}
	memset(slope, false, sizeof(slope));

	//행렬 바꾸기
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
			swap(map[i][j], map[j][i]);
	}

	//열
	for (int r = 0; r < N; r++)
	{
		if (is_street(r))
			cnt++;
	}
	memset(slope, false, sizeof(slope));
}

int main(void)
{
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cnt = 0; 

		//input
		cin >> N >> X;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				cin >> map[i][j];
		}

		solve();

		//output
		cout << "#" << tc << " " << cnt << endl;
	}
	
}