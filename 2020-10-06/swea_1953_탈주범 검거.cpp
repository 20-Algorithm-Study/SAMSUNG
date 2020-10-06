#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define MAX 50

int T, N, M, R, C, L;
int map[MAX][MAX];
int answer = 0;

struct Loc {
    int r, c;
    Loc(int _r, int _c) { r = _r; c = _c; }
};
queue <Loc> q;
int visited[MAX][MAX] = { 0, };
int dir[8][4][2] = {{{0,0}, {0,0}, {0,0}, {0,0}  }, //0
                    {{-1,0}, {1,0}, {0,-1}, {0,1}}, //1. 상 하 좌 우
                    {{-1,0}, {1,0}, {0,0}, {0,0} }, //2. 상 하 
                    {{0,0}, {0,0}, {0,-1}, {0,1} }, //3.       좌 우
                    {{-1,0}, {0,0}, {0,0}, {0,1} }, //4. 상       우
                    {{0,0}, {1,0}, {0,0}, {0,1}  }, //5.    하    우
                    {{0,0}, {1,0}, {0,-1}, {0,0} }, //6.    하 좌
                    {{-1,0}, {0,0}, {0,-1}, {0,0}}, //7. 상    좌 
                    }; 

void solve()
{
    int r, c, d, nr, nc;
    
    answer = 0;
    memset(visited, 0, sizeof(visited));

    q.push(Loc(R, C));
    visited[R][C] = 1;

    while (!q.empty())
    {
        r = q.front().r;
        c = q.front().c;
        d = map[r][c];
        answer++;
        q.pop();

        if (visited[r][c] >= L) //탈출 후 소요된 시간
            continue;

        for (int i = 0; i < 4; i++)
        {
            nr = r + dir[d][i][0];
            nc = c + dir[d][i][1];

            if (nr < 0 || nc < 0 || nr >= N || nc >= M || visited[nr][nc] > 0) //범위 넘어감 or 이미 방문
                continue;

            if (map[nr][nc] == 0)
                continue;
            
            if (i == 0 && map[nr][nc] != 1 && map[nr][nc] != 2 && map[nr][nc] != 5 && map[nr][nc] != 6) //상
                continue;
            else if (i == 1 && map[nr][nc] != 1 && map[nr][nc] != 2 && map[nr][nc] != 4 && map[nr][nc] != 7) //하
                continue;
            else if (i == 2 && map[nr][nc] != 1 && map[nr][nc] != 3 && map[nr][nc] != 4 && map[nr][nc] != 5) //좌
                continue;
            else if (i == 3 && map[nr][nc] != 1 && map[nr][nc] != 3 && map[nr][nc] != 6 && map[nr][nc] != 7) //우
                continue;

            cout << r << " " << c << " : " << nr << " " << nc << endl;
            q.push(Loc(nr, nc));
            visited[nr][nc] = visited[r][c] + 1;
        }
    }
}

int main()
{
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        //input
        cin >> N >> M >> R >> C >> L;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
                cin >> map[i][j];
        }

        solve();

        //output
        cout << "#" << tc << " " << answer << endl;
    }
}
