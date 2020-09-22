#include<iostream>
#include<vector>
#include<cstring>
#include<cmath>
using namespace std;
//#define DEBUG

#define MAX 4 //톱니바퀴 개수
#define WHEEL_SIZE 8 //톱니 개수
#define MAX_TURN 20 //최대 회전수

int T; //테스트케이스 수
int K; //회전수
int wheel[MAX][WHEEL_SIZE]; //톱니바퀴 정보
int turn[MAX_TURN][2]; //0 = 톱니번호, 1 = 방향
int status[4]; //변화해야할 상태 (1 = 시계 / 0 = 그대로 / -1 = 반시계)
int rslt = 0; //결과값

void change(int r)
{
	if (status[r] == 1) //시계방향으로 돈다
	{
		int tmp = wheel[r][WHEEL_SIZE - 1];
		for (int i = WHEEL_SIZE - 1; i > 0; i--)
			wheel[r][i] = wheel[r][i - 1];
		wheel[r][0] = tmp;
	}
	else //반시계방향으로 돈다
	{
		int tmp = wheel[r][0];
		for (int i = 0; i < WHEEL_SIZE - 1; i++)
			wheel[r][i] = wheel[r][i + 1];
		wheel[r][WHEEL_SIZE - 1] = tmp;
	}
}

void solve()
{
	for (int i = 0; i < K; i++)
	{
		memset(status, 0, sizeof(status)); //init

		status[turn[i][0]] = turn[i][1]; //회전하는 톱니 상태 갱신

		//왼쪽 톱니바퀴
		for (int j = turn[i][0]; j > 0; j--)
		{
			if (wheel[j - 1][2] == wheel[j][6]) //같으면 더이상 변화 없음
				break;
			else //다르면 상태 변화
			status[j - 1] = status[j] * -1; // 반전(반대로 돈다)
		}

		//오른쪽 톱니바퀴
		for (int j = turn[i][0]; j < MAX - 1; j++)
		{
			if (wheel[j][2] == wheel[j + 1][6]) //같으면 더이상 변화 없음
				break;
			else //다르면 상태 변화
			status[j + 1] = status[j] * -1; // 반전(반대로 돈다)
		}

		//상태변화
		for (int j = 0; j < MAX; j++)
		{
			if (status[j] != 0) //변해야 하는 애들만
				change(j);
		}
	}
}

int main()
{
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		//input
		cin >> K; //회전수
		for (int i = 0; i < MAX; i++) //톱니바퀴 개수만큼
		{
			for (int j = 0; j < WHEEL_SIZE; j++) //배열로 쪼개주기
				cin >> wheel[i][j];
		}
		for (int i = 0; i < K; i++) //톱니번호, 방향
		{
			cin >> turn[i][0] >> turn[i][1];
			turn[i][0]--; //입력은 1~4인데 저장은 0~3이니까
		}

		solve();

		//output
		rslt = 0;
		for (int i = 0; i < MAX; i++) //톱니바퀴 개수만큼
		{
			if (wheel[i][0])
				rslt += pow((double)2, (double)i);
		}
		cout << "#" << tc << " " << rslt << endl;
	}
}