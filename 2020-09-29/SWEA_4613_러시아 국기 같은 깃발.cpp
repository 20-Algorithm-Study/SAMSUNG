#include <iostream>
#include <cstring>
using namespace std;
//#define DEBUG
#define MAX 50

int T, N, M;
char cell[MAX][MAX];
int color[MAX][3]; //각 줄마다의 색 개수 (0 = W, 1 = B, 2 = R)
int rslt, base; //결과값, 기본값

void range_of_blue(int sr, int er) //파랑 범위 기준으로 색 바꾸기
{
    int ans = base;

    //white : 파랑 기준으로 위
    for (int i = 1; i < sr; i++)
        ans += (color[i][1] + color[i][2]); 

    //blue
    for (int i = sr; i < er; i++)
        ans += (color[i][0] + color[i][2]); 

    //red : 파랑 기준으로 아래
    for (int i = er; i < N - 1; i++)
        ans += (color[i][0] + color[i][1]); 

    rslt = rslt < ans ? rslt : ans; //최소값 찾기
}

void solve()
{
    //init
    memset(color, 0, sizeof(color));
    base = 0; //맨 위, 맨 아래 변경 값은 고정
    rslt = MAX * MAX;

    for (int c = 0; c < M; c++)
    {
        if (cell[0][c] != 'W') //맨 윗줄은 항상 흰색
            base++;
        if (cell[N - 1][c] != 'R') //맨 아랫줄은 항상 빨간색
            base++;
    }

    for (int r = 1; r < N - 1; r++) //각 줄마다 색 개수 세기
    {
        for (int c = 0; c < M; c++)
        {
            if (cell[r][c] == 'W')
                color[r][0]++;
            else if (cell[r][c] == 'B')
                color[r][1]++;
            else //R
                color[r][2]++;
        }
    }

    //파랑의 범위를 정하기
    for (int line = 1; line <= N-2; line++) //파랑은 최소 1줄부터 최대 N-2줄까지
    {
        for (int r = 1; r + line < N; r++)
            range_of_blue(r, r + line);
    }
}

int main() 
{  
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        //input
        cin >> N >> M;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
                cin >> cell[i][j];
        }

        solve();

        //output
        cout << "#" << tc << " " << rslt << endl;
    }
}