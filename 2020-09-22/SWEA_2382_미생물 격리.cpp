#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define DEBUG
#define MAX 101

int T;
int N, M, K;
struct Micro {
	int n, r, c, cnt, d; //��ȣ, ��, ��, ����, �̵�����
	Micro(int _n, int _r, int _c, int _cnt, int _d) { n = _n; r = _r; c = _c; cnt = _cnt; d = _d; }
};
vector <Micro> micro; //�̻���

vector<int> map[MAX][MAX];
vector <Micro> maxM; //2���̻� ������ ���� �� best�� ã�� �뵵

int dir[5][2] = { {0,0}, {-1,0}, {1,0}, {0,-1}, {0,1} }; //�״��.��.��.��.��
int reverseDir[5] = { 0, 2, 1, 4, 3 }; //�״��.��.��.��.��

int rslt = 0; //�����

bool compare(Micro a, Micro b)
{
	return a.cnt > b.cnt;
}

void solve()
{
	while (M--) // M �ð���ŭ
	{
		//�ʱ�ȭ
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				map[i][j].clear();
		}

		for (int i = 0; i < micro.size(); i++) //��� ����
		{
			if (micro[i].cnt == 0) // �̻��� ���� ���� = ����
				continue;

			//���� �̵�
			micro[i].r += dir[micro[i].d][0];
			micro[i].c += dir[micro[i].d][1];
			map[micro[i].r][micro[i].c].push_back(i); //�̵� �� �ش� map ��ġ�� �ִ´�

			//��ǰ ���� ����
			if (micro[i].r < 1 || micro[i].c < 1 || micro[i].r >= N - 1 || micro[i].c >= N - 1) 
			{
				micro[i].d = reverseDir[micro[i].d]; //������ȯ
				micro[i].cnt /= 2; //���� �״´�
			}
		}

		for (int i = 0; i < micro.size(); i++) //��� ����
		{
			if (micro[i].cnt == 0) // �̻��� ���� ���� = ����
				continue;

			if (map[micro[i].r][micro[i].c].size() > 1) //2�� �̻��� ������ �𿴴�
			{
				int sum = 0;
				maxM.clear(); //�ʱ�ȭ

				for (int j = 0; j < map[micro[i].r][micro[i].c].size(); j++) //�ش� map ��ġ�� �ִ� ��� �̻��� ����
				{
					maxM.push_back(micro[map[micro[i].r][micro[i].c][j]]); //maxM�� ����
					sum += micro[map[micro[i].r][micro[i].c][j]].cnt; //�� ������ �̻��� ������ ���Ѵ�
					micro[map[micro[i].r][micro[i].c][j]].cnt = 0; //�̻��� ���� 0���� �ʱ�ȭ(����)
				}

				sort(maxM.begin(), maxM.end(), compare); //�����ؼ� �̻����� ���� ���� ������ ã�´�
				micro[maxM[0].n].cnt = sum; //�̻����� ���� ���� �������� ��� �̻����� ����.(�ٸ� ������ ����)
			}
		}
	}
}

int main()
{
	int r, c, n, d;

	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		//init
		micro.clear();

		//input
		cin >> N >> M >> K;
		for (int i = 0; i < K; i++)
		{
			cin >> r >> c >> n >> d;
			micro.push_back(Micro(i, r, c, n, d));
		}

		solve();

		//output
		rslt = 0;
		for (int i = 0; i < micro.size(); i++)
			rslt += micro[i].cnt;
		cout << "#" << tc << " " << rslt << endl;
	}

}