#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int N;
vector <int> rslt;

bool isPrime(int k) 
{
    int end = (int) sqrt(k);

    if (k == 1) 
        return false;

    for (int i = 2; i <= end; i++) 
    {
        if (k % i == 0) 
            return false;
    }
	
    return true;
}

void dfs(int num, int len) 
{
    if (N == len)
        rslt.push_back(num);

    for (int i = 1; i <= 9; i++) 
    {
        if (isPrime(num * 10 + i))
            dfs(num * 10 + i, len + 1);
    }
}

int main()
{
	//input
	cin >> N;
	
    	dfs(0, 0);

	//output
	for (int i = 0; i < rslt.size(); i++)
		cout << rslt[i] << endl;
}
