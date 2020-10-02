#include<iostream>

using namespace std;

int Paper[11][11];
bool check[11][11];
int remainPaper[6] = { 0,5,5,5,5,5 };
int All = 0;
int MMin = 987654321;
bool Stop = false;

void IInput();
void Sticker(int x);
bool Checkingsize(int x, int y, int cnt);
void patch_paper(int x, int y, int cnt, bool now);
void Print();

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	IInput(); //�Է�
	Sticker(0); //��ƼĿ

	if (MMin == 987654321) cout << -1;
	else
		cout << MMin;

	return 0;
}


void IInput() {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> Paper[i][j];
			if (Paper[i][j] == 1)All++;
		}
	}
}

void Sticker(int x) {
	

	if (All == 0 || (remainPaper[1] == 0 && remainPaper[2] == 0 && remainPaper[3] == 0 && remainPaper[4] == 0 && remainPaper[5] == 0))
	{
		int mmin = 25;
		for (int i = 1; i <= 5; i++) {
			mmin -= remainPaper[i];
		}
		if (MMin > mmin)MMin = mmin;
		return;
	}

	for (int i = x; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			
			if (Paper[i][j] == 1 && !check[i][j]) { //�´�ũ�� �����̱��ϱ�
			
				for (int k = 1; k <= 5 ; k++) { //������ ũ�� 5����
					
					if (remainPaper[k] > 0 && Checkingsize(i, j, k)) { //�����̰� �����ְų�, ���ϼ� ������
						
						remainPaper[k]--;
						patch_paper(i, j, k, true);
						//Print();

						Sticker(i);

						remainPaper[k]++;
						patch_paper(i, j, k, false);
					}
					else return; //�����̴� 1~���̴ϱ� ���������� �����̸� ū����� ������.
					
				}
			}
		}
	}
}

bool Checkingsize(int x, int y, int cnt)
{
	for (int i = x; i < x + cnt; i++) {
		for (int j = y; j < y + cnt; j++) {
			if (check[i][j] || Paper[i][j] == 0|| i>=10 || j>=10)return false;
		}
	}
	return true;
}


void patch_paper(int x, int y, int cnt, bool now) {

	if (now == true) {
		for (int i = x; i < x + cnt; i++) {
			for (int j = y; j < y + cnt; j++) {
				check[i][j] = now;
				All--;
			}
		}
		//Print();
	}
	else{
		for (int i = x; i < x + cnt; i++) {
			for (int j = y; j < y + cnt; j++) {
				check[i][j] = now;
				All++;
			}
		}
	}

  
}

void Print() {

	cout << "\n";
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << check[i][j] << " ";
		}
		cout << "\n";
	}

}