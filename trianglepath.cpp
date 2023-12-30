//문제 ID : TRIANGLEPATH
#include <iostream>
using namespace std;
int func(int y, int x);
int func_memo(int y, int x);

int arr[100][100];
int n;
int cache[100][100];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases-- > 0) {
		cin >> n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i + 1; j++)
				cin >> arr[i][j];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i + 1; j++)
				cache[i][j] = -1;
		cout << func_memo(0, 0) << "\n";
	}
}

//완전 탐색
int func(int y, int x) {
	//base
	if (y == n) return 0;
	//step
	int a = arr[y][x] + func(y + 1, x);
	int b = arr[y][x] + func(y + 1, x + 1);
	return max(a, b);
}

//메모이제이션
int func_memo(int y, int x) {
	//base
	if (y == n-1) return arr[y][x];
	//has memo
	int& ret = cache[y][x];
	if (ret != -1) return ret;
	//no memo
	int a = arr[y][x] + func(y + 1, x);
	int b = arr[y][x] + func(y + 1, x + 1);
	return ret = max(a, b);
}