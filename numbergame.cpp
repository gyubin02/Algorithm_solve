//문제 ID : NUMBERGAME
#include <iostream>
using namespace std;
int play(int left, int right);

const int NEGINF = -999999999;
int cache[50][50];
int board[50];
int n;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		for (int i = 0; i < 50; i++)
			for (int j = 0; j < 50; j++)
				cache[i][j] = NEGINF;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> board[i];
		cout << play(0, n - 1) << "\n";
	}
}

int play(int left, int right) { //현재 게임판에 남은 숫자의 맨 왼쪽, 오른쪽 위치가 주어졌을 때, player 점수 - opponent 점수의 최대값을 반환
	//base
	if (left > right)
		return 0;
	//check memo
	int& ret = cache[left][right];
	if (ret != NEGINF) 
		return ret;
	//step
	ret = max(ret, board[left] - play(left + 1, right));
	ret = max(ret, board[right] - play(left, right - 1));
	if (right - left + 1 >= 2) {
		ret = max(ret, -play(left + 2, right));
		ret = max(ret, -play(left, right - 2));
	}
	return ret;
}