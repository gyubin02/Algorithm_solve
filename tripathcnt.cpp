//문제 ID : TRIPATHCNT
#include <iostream>
using namespace std;
int func(int y, int x);
int func2(int y, int x);

int A[101][101];
int cache[101][101];
int cache2[101][101];
int n;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		cin >> n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i+1; j++) {
				cin >> A[i][j];
				cache[i][j] = cache2[i][j] = -1;
			}
		
		cout << func2(0, 0) << "\n";
	}
}

int func(int y, int x) { //(y,x)에서 (n-1, x+c)로 가는 경로들 중 최대합 반환
	//base
	if (y == n - 1) return A[y][x];
	//check memo
	int& ret = cache[y][x];
	if (ret != -1) return ret;
	//no memo
	return ret = max(func(y + 1, x), func(y + 1, x + 1)) + A[y][x];
}

int func2(int y, int x) { //(y, x)에서 (n-1, x+c)로 가는 최대합 경로의 개수를 반환
	//base
	if (y == n - 1) return 1;
	//check memo
	int& ret = cache2[y][x];
	if (ret != -1) return ret;
	//step
	ret = 0;
	if (func(y + 1, x) >= func(y + 1, x + 1)) ret += func2(y + 1, x);
	if (func(y + 1, x) <= func(y + 1, x + 1)) ret += func2(y + 1, x + 1);
	return ret;

}