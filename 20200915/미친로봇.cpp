#include<iostream>

using namespace std;


double Ans;
double percent[4];
bool map[31][31];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

void DFS(int x, int y, int total, double per);

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;
	cin >> N;

	for (int i = 0; i < 4; i++) {
		cin >> percent[i];
		percent[i] /= 100;
	}
	
	DFS(15, 15, N, 1.0);

	cout << fixed;
	cout.precision(10);
	cout << Ans;

	return 0;
}


void DFS(int x, int y, int total, double per) {
	
	map[x][y] = true;

	if (total == 0) {
		Ans += per;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (map[nx][ny] == true)continue;
		
		DFS(nx, ny, total--, per * percent[i]);	
	}
	 
	map[x][y] = false;
}