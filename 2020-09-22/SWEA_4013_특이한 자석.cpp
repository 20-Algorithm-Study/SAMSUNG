#include<iostream>
#include<vector>
#include<cstring>
#include<cmath>
using namespace std;
//#define DEBUG

#define MAX 4 //��Ϲ��� ����
#define WHEEL_SIZE 8 //��� ����
#define MAX_TURN 20 //�ִ� ȸ����

int T; //�׽�Ʈ���̽� ��
int K; //ȸ����
int wheel[MAX][WHEEL_SIZE]; //��Ϲ��� ����
int turn[MAX_TURN][2]; //0 = ��Ϲ�ȣ, 1 = ����
int status[4]; //��ȭ�ؾ��� ���� (1 = �ð� / 0 = �״�� / -1 = �ݽð�)
int rslt = 0; //�����

void change(int r)
{
	if (status[r] == 1) //�ð�������� ����
	{
		int tmp = wheel[r][WHEEL_SIZE - 1];
		for (int i = WHEEL_SIZE - 1; i > 0; i--)
			wheel[r][i] = wheel[r][i - 1];
		wheel[r][0] = tmp;
	}
	else //�ݽð�������� ����
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

		status[turn[i][0]] = turn[i][1]; //ȸ���ϴ� ��� ���� ����

		//���� ��Ϲ���
		for (int j = turn[i][0]; j > 0; j--)
		{
			if (wheel[j - 1][2] == wheel[j][6]) //������ ���̻� ��ȭ ����
				break;
			else //�ٸ��� ���� ��ȭ
			status[j - 1] = status[j] * -1; // ����(�ݴ�� ����)
		}

		//������ ��Ϲ���
		for (int j = turn[i][0]; j < MAX - 1; j++)
		{
			if (wheel[j][2] == wheel[j + 1][6]) //������ ���̻� ��ȭ ����
				break;
			else //�ٸ��� ���� ��ȭ
			status[j + 1] = status[j] * -1; // ����(�ݴ�� ����)
		}

		//���º�ȭ
		for (int j = 0; j < MAX; j++)
		{
			if (status[j] != 0) //���ؾ� �ϴ� �ֵ鸸
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
		cin >> K; //ȸ����
		for (int i = 0; i < MAX; i++) //��Ϲ��� ������ŭ
		{
			for (int j = 0; j < WHEEL_SIZE; j++) //�迭�� �ɰ��ֱ�
				cin >> wheel[i][j];
		}
		for (int i = 0; i < K; i++) //��Ϲ�ȣ, ����
		{
			cin >> turn[i][0] >> turn[i][1];
			turn[i][0]--; //�Է��� 1~4�ε� ������ 0~3�̴ϱ�
		}

		solve();

		//output
		rslt = 0;
		for (int i = 0; i < MAX; i++) //��Ϲ��� ������ŭ
		{
			if (wheel[i][0])
				rslt += pow((double)2, (double)i);
		}
		cout << "#" << tc << " " << rslt << endl;
	}
}