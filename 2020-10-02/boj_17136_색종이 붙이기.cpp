#include <iostream>
#include <vector>
using namespace std;
#define MAX 10
#define ANS 1000
//#define DEBUG

int N;
bool map[MAX][MAX];
int paper[6] = { 0,5,5,5,5,5 }; //������ ����

struct Space {
	int r, c, size;
	Space(int _r, int _c) { r = _r; c = _c; size = 0; }
};
vector <Space> space;

int answer = ANS;

int find_max_size(int idx) //�ִ�� ���� �� �ִ� ������ ã��
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
				if (!map[i][j]) //������ ���� ������ �ƴ�
				{
					flag = false;
					break;
				}
			}
			if (!flag)//������ ���� ������ �ƴ�
				break;
		}
		if (!flag)//������ ���� ������ �ƴ�
			break;

		answer++;
	}

	return answer;
}

void change_ststus(int r, int c, int size, bool status) //������ ���̱� or ����
{
	for (int i = r; i < r + size; i++)
	{
		for (int j = c; j < c + size; j++)
			map[i][j] = status;
	}
}

void attach(int idx, int total) //dfs ���鼭 ū �����̺��� �ٿ�����
{
	int r, c, size, nr, nc;

	if (idx >= space.size())
		return;

	r = space[idx].r;
	c = space[idx].c;
	size = find_max_size(idx);

	for (int i = size; i > 0; i--)
	{
		if (paper[i] == 0) //������ ������ ���ٿ�
			continue;

		//���̱�
		change_ststus(r, c, i, false);
		paper[i]--;

		if (total + i * i == space.size()) //�� �ٿ���!
		{
			int sum = 0;
			for (int j = 1; j <= 5; j++)
				sum += (5 - paper[j]);
			answer = answer < sum ? answer : sum; //�ּڰ� ����
		}

		//���� ���� ���� ã��
		for (int j = idx + 1; j < space.size(); j++)
		{
			nr = space[j].r;
			nc = space[j].c;

			if (map[nr][nc]) //���� �ڸ��� ����
			{
				attach(j, total + i * i);
				break;
			}
		}

		//����
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
	if (space.empty()) //���� ���� ó������ ����
		answer = 0;
	else
		attach(0, 0);

	//output
	if (answer == ANS)
		cout << "-1" << endl;
	else
		cout << answer << endl;
}