#include <iostream>
#include <vector>
using namespace std;
#define MAX 10
#define ANS 1000
//#define DEBUG

int N;
bool map[MAX][MAX];
int paper[6] = { 0,5,5,5,5,5 }; //색종이 개수

struct Space {
	int r, c, size;
	Space(int _r, int _c) { r = _r; c = _c; size = 0; }
};
vector <Space> space;

int answer = ANS;

int find_max_size(int idx) //최대로 붙일 수 있는 색종이 찾기
{
	int r = space[idx].r;
	int c = space[idx].c;
	bool flag = true;
	int answer = 0;

	for (int k = 1; k <= 5; k++)
	{
		if (r + k > MAX || c + k > MAX)
			break;

		for (int i = r; i < r + k; i++)
		{
			for (int j = c; j < c + k; j++)
			{
				if (!map[i][j]) //색종이 붙일 공간이 아님
				{
					flag = false;
					break;
				}
			}
			if (!flag)//색종이 붙일 공간이 아님
				break;
		}
		if (!flag)//색종이 붙일 공간이 아님
			break;

		answer++;
	}

	return answer;
}

void change_ststus(int r, int c, int size, bool status) //색종이 붙이기 or 떼기
{
	for (int i = r; i < r + size; i++)
	{
		for (int j = c; j < c + size; j++)
			map[i][j] = status;
	}
}

void attach(int idx, int total) //dfs 돌면서 큰 색종이부터 붙여보기
{
	int r, c, size, nr, nc;

	if (idx >= space.size())
		return;

	r = space[idx].r;
	c = space[idx].c;
	size = find_max_size(idx);

	for (int i = size; i > 0; i--)
	{
		if (paper[i] == 0) //색종이 없으면 못붙여
			continue;

		//붙이기
		change_ststus(r, c, i, false);
		paper[i]--;

		if (total + i * i == space.size()) //다 붙였다!
		{
			int sum = 0;
			for (int j = 1; j <= 5; j++)
				sum += (5 - paper[j]);
			answer = answer < sum ? answer : sum; //최솟값 갱신
		}

		//다음 붙일 곳을 찾기
		for (int j = idx + 1; j < space.size(); j++)
		{
			nr = space[j].r;
			nc = space[j].c;

			if (map[nr][nc]) //붙일 자리가 존재
			{
				attach(j, total + i * i);
				break;
			}
		}

		//떼기
		change_ststus(r, c, i, true);
		paper[i]++;
	}
}

int main()
{
	//input
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			cin >> map[i][j];
			if (map[i][j])
				space.push_back(Space(i, j));
		}
	}

	//solve
	if (space.empty()) //붙일 곳이 처음부터 없다
		answer = 0;
	else
		attach(0, 0);

	//output
	if (answer == ANS)
		cout << "-1" << endl;
	else
		cout << answer << endl;
}