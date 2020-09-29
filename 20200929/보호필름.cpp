#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

/*
1. K기준을 통과하는지 확인.
2. 1~D까지 조합을 구함
   -> 조합을 구하면서 K기준통과하는지 확인. -> 통과한다면 값 출력
      --> 조합안에서 A,B약품 조합
*/

int T, D, W, K;
int Cell[15][25];
bool flag = false;

void Init();
void IInput();
int Comb();
bool Check(int cell[15][25]);
void put_medicine(vector<int>n, int idx, int map[15][25]);

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> T;

	for (int q = 1; q <= T; q++) {
		
		Init();
		IInput();
		int result = Comb();
		
		cout << "#" << q << " " << result << "\n";
	}

	return 0;
}


void Init() {
	D = 0;
	W = 0;
	K = 0;
	memset(Cell, 0, sizeof(Cell));
	flag = false;
}

void IInput() {
	cin >> D >> W >> K;
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < W; j++) {
			cin >> Cell[i][j];
		}
	}

	
}

bool Check(int cell[15][25]) {

	//int all = 0;
	
	/*
	cout << "check \n";
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < W; j++) {
			cout << cell[i][j] << " ";
		}
		cout << "\n";
	}*/

	for (int i = 0; i < W; i++) {
		int a = 0; int b = 0;
		int before = cell[0][i];
		bool stop = false;

		for (int j = 0; j < D; j++) {
			if (cell[j][i] == 0) {
				if (before != cell[j][i]) {
					if (before == 1) b = 0;
					before = cell[j][i];
				}
				a++;
				if (a >= K) {
					stop = true;
					break;
				}

			}
			else {
				if (before != cell[j][i]) {
					if (before == 0) a = 0;
					before = cell[j][i];
				}
				b++;
				if (b >= K) {
					stop = true;
					break;
				}
			}
		}

		if (!stop) return false;
	}
	
	return true;
}

int Comb() {

	
	int cpy[15][25] = {0};

	// 약품안넣을때,
	if (Check(Cell)) return 0;

	//약품 한줄 넣을때.
	for (int i = 0; i < D; i++) {
		memcpy(cpy, Cell, sizeof(Cell)); 
		for (int j = 0; j < W; j++) {
			cpy[i][j] = 1;
		}
		if (Check(cpy)) return 1;

		memcpy(cpy, Cell, sizeof(Cell));
		for (int j = 0; j < W; j++) {
			cpy[i][j] = 0;
		}
		if (Check(cpy)) return 1;
	}

	//2~K-1까지 조합 -> K개 약품처리하면 무조건 되니까..
	for (int i = 2; i < K; i++) {

		vector<int>V;
		
		for (int j = 0; j < D - i; j++) {
			V.push_back(0);
		}

		for (int j = 0; j < i; j++) {
			V.push_back(1);
		}
		

		do {

			vector<int>Num;
			for(int j = 0; j < D; j++) {
				if (V[j] == 1) Num.push_back(j);
			}
			
			int cpy[15][25] = { 0 };
			memcpy(cpy, Cell, sizeof(Cell));

			put_medicine(Num, 0, cpy);
			if(flag) break;
			

		} while (next_permutation(V.begin(),V.end()));

		if (flag) {
			return i;
		}
	}


	return K;
}


void put_medicine(vector<int>v,int idx, int map[15][25]) {

	if (idx == v.size()) {

		if (Check(map)) flag = true;
		return;
	}

	//cout << 1 << "\n";
	for (int i = 0; i < W; i++) {
		map[v[idx]][i] = 0;
	}
	put_medicine(v, idx + 1, map);


	//cout << 2 << "\n";
	for (int i = 0; i < W; i++) {
		map[v[idx]][i] = 1;
	}
	put_medicine(v, idx + 1, map);

}

