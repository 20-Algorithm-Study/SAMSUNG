#include<iostream>
#include<vector>

using namespace std;

vector<int>Graph[100010];
bool visit[100010];
int parent[100010];

void DFS(int cnt);

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;
	cin >> N;

	for (int i = 1; i < N; i++) {
		int a, b;
		cin >> a >> b;
		Graph[a].push_back(b);
		Graph[b].push_back(a);
	}

	DFS(1);

	for (int i = 2; i <= N; i++) {
		cout << parent[i] << "\n";
	}
	return 0;
}


void DFS(int cur) 
{
	visit[cur] = true;

	for (int i = 0; i < Graph[cur].size(); i++) {
		
		int next = Graph[cur][i];

		if (!visit[next]) {
			parent[next] = cur;
			DFS(next);
		}
	}
}