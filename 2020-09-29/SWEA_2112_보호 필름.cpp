#include <iostream>
#include <vector>
using namespace std;

int T, D, W, K;
int cell[13][20];

vector<int> pick;

int rslt = 0;

bool check()
{
    int cntA, cntB;
    bool flag;

    for (int c = 0; c < W; c++) 
    {
        cntA = 0;
        cntB = 0;
        flag = false;

        for (int r = 0; r < D; r++) //열 조사
        {
            if (cell[r][c] == 0) //A이면
            {
                cntA++; //A개수 증가
                cntB = 0; //B개수 0으로 초기화
            }
            else
            {
                cntA = 0;
                cntB++;
            }

            if (cntA == K || cntB == K) //A, B 둘 중 하나라도 K개 이상이면 통과
            {
                flag = true;
                break;
            }
        }

        if (!flag) //한 열이라도 통과하지 못했다면
            return false;
    }

    return true;
}

bool injection(int now, int r) //약물 투입(현재 투입한 행, 행의 개수)
{
    int line[20];

    if (now >= r) //투입 끝
    {
        if (check()) //검사했는데 합격
            return true;
        else
            return false;
    }

    for (int kind = 0; kind <= 1; kind++) //A약물 = 0, B약물 = 1
    {
        for (int i = 0; i < W; i++) 
        {
            line[i] = cell[pick[now]][i]; //내가 고른 행(막)을 저장
            cell[pick[now]][i] = kind; //약을 투입해서 바꿔줌(0 = A / 1 = B)
        }

        if (injection(now + 1, r)) //다음 행(막) 바꿔주기
            return true;

        for (int i = 0; i < W; i++)
            cell[pick[now]][i] = line[i]; //다시 원래대로
    }

    return false;
}

bool comb(int cnt, int r) //D C r : D개의 행(막)에서 r개의 행(막)을 고른다
{
    if (pick.size() == r) //어떤 행(막)에 투입할지 다 골랐다 
    {
        if (injection(0, r)) // 투입
            return true;
        else
            return false;
    }

    for (int i = cnt; i < D; i++)
    {
        pick.push_back(i);
        if (comb(i + 1, r))
            return true;
        pick.pop_back();
    }

    return false;
}

void solve()
{
    if (K == 1 || check()) //합격기준 1 or 주어진 그대로 합격
        rslt = 0;
    else //약품 투입
    {
        rslt = K; 
        for (int i = 1; i < K; i++) //적어도 K번보다는 적게 투여해야 함
        {
            pick.clear();
            if (comb(0, i)) //만약 i회 투입에서 성공
            {
                rslt = i; //최소 투입 횟수 갱신
                break;
            }
        }
    }
}

int main()
{
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        //init
        rslt = 0;

        //input
        cin >> D >> W >> K;
        for (int i = 0; i < D; i++)
        {
            for (int j = 0; j < W; j++)
                cin >> cell[i][j];
        }

        solve();

        //output
        cout << "#" << tc << " " << rslt << endl;
    }
}
