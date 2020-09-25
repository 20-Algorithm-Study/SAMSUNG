#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MAX 250

int N, M;
int map[MAX][MAX];
vector <pair<int, int>> ch;

queue <pair<int, int>> q;
bool visited[MAX][MAX]; 
int dir[8][2] = { {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1} };

int rslt = 0;

void bfs()
{
    int r, c, nr, nc;

    for (int i = 0; i < ch.size(); i++)
    {
        r = ch[i].first;
        c = ch[i].second;

        if (visited[r][c]) //이미 방문
            continue;

        q.push(make_pair(r, c)); //아직 방문 안한 글자니까 큐에 삽입
        visited[r][c] = true;

        while (!q.empty()) 
        {
            r = q.front().first;
            c = q.front().second;
            q.pop();

            for (int d = 0; d < 8; d++) //상하좌우대각선 조사
            {
                nr = r + dir[d][0];
                nc = c + dir[d][1];

                if (nr < 0 || nc < 0 || nr >= M || nc >= N || visited[nr][nc]) //범위 벗어남 or 이미 방문
                    continue;

                if (map[nr][nc] != 1) //글자가 아님
                    continue;

                q.push(make_pair(nr, nc));
                visited[nr][nc] = true;
            }
        }

        rslt++;
    }
}

int main()
{
    //input
    cin >> M >> N;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> map[i][j];
            if(map[i][j] == 1) //글자
                ch.push_back(make_pair(i, j));
        }
    }

    bfs(); //solve

    //output
    cout << rslt << endl;
}