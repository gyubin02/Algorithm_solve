//문제 ID : JUMPGAME
#include <iostream>
using namespace std;
int jump(int y, int x, int a);

const int n = 100;
int board[n][n];
int hasAns[n][n]; //0이면 false, 1이면 true, -1이면 no memo

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases-- > 0) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				hasAns[i][j] = -1;
		//memset(hasAns, -1, sizeof(hasAns)); //컴파일 오류
		int a;
		cin >> a;
		for (int i = 0; i < a; i++)
			for (int j = 0; j < a; j++)
				cin >> board[i][j];
		if (jump(0, 0, a)) cout << "YES" << "\n";
		else cout << "NO" << "\n";
	}
}

int jump(int y, int x, int a) {
	//base
	if (x >= a || y >= a) return 0;
	if (y == a-1 && x == a-1) return 1;
	//check memo
	int& ret = hasAns[y][x];
	if (ret != -1) return ret;
	//no memo
	int number = board[y][x];
	return ret = jump(y + number, x, a) | jump(y, x + number, a);
}