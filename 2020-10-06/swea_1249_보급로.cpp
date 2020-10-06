#include <iostream>
#include <queue>
using namespace std;
#define MAX 100

int T, N;
char map[MAX][MAX];

struct Loc {
    int r, c;
    Loc(int _r, int _c) { r = _r; c = _c; }
};
queue <Loc> q;
int visited[MAX][MAX] = { 0, };
int dir[4][2] = { {-1,0}, {1,0}, {0,1}, {0,-1} };

void solve()
{
    int r, c, nr, nc;

    //init
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            visited[i][j] = 90000;
    }

    q.push(Loc(0, 0));
    visited[0][0] = map[0][0] - '0';

    while (!q.empty())
    {
        r = q.front().r;
        c = q.front().c; 
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            nr = r + dir[i][0];
            nc = c + dir[i][1];

            if (nr < 0 || nc < 0 || nr >= N || nc >= N) //범위 넘어갔음
                continue;

            if (visited[r][c] + map[nr][nc] - '0' >= visited[nr][nc]) //새로운 경로가 더 복구시간이 길면 갈 필요 없음
                continue;

            visited[nr][nc] = visited[r][c] + map[nr][nc] - '0';

            if (nr == N - 1 && nc == N - 1) //도착지 왔으면 갱신만 하고 큐에 넣을 필요는 없음
                continue;
            else
                q.push(Loc(nr, nc));
        }
    }
}

int main()
{
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        //input
        cin >> N;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cin >> map[i][j];
        }

        solve();

        //output
        cout << "#" << tc << " " << visited[N - 1][N - 1] << endl;
    }
}
