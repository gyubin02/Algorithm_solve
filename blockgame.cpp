//문제 ID : BLOCKGAME
#include <iostream>
#include <vector>
using namespace std;
inline int transfer(int y, int x);
void precalc();
int canWin(int state);
int precalc_board();

vector<int> moves;
int cache[1 << 25];
string board[5];

int main() {
	int cases;
	cin >> cases;
	while (cases--) {
		for (int i = 0; i < (1 << 25); i++)
			cache[i] = -1;
		for (int i = 0; i < 5; i++)
			cin >> board[i];
		int state = precalc_board();
		int ret = canWin(state);
		if (ret == 1) cout << "WINNING" << "\n";
		if (ret == 0) cout << "LOSING" << "\n";
	}
}

inline int transfer(int y, int x) {
	return 1 << (y * 5 + x);
}

int precalc_board() {
	int ret = 0;
	for (int i = 4; i >= 0; i--)
		for (int j = 4; j >= 0; j--) {
			if (board[i][j] == '#')
				ret++;
			ret = (ret << 1);
		}
	return ret;
}

void precalc() {
	//3칸
	for(int y=0; y<4; y++)
		for (int x = 0; x < 4; x++) {
			vector<int> cell;
			for (int dx = 0; dx < 2; dx++)
				for (int dy = 0; dy < 2; dy++)
					cell.push_back(transfer(y + dy, x + dx));
			int square = cell[0] + cell[1] + cell[2] + cell[3];
			for (int i = 0; i < 4; i++)
				moves.push_back(square - cell[i]);
		}
	//2칸
	for(int i=0; i<5; i++)
		for (int j = 0; j < 4; j++) {
			moves.push_back(transfer(i, j) + transfer(i, j + 1));
			moves.push_back(transfer(j, i) + transfer(j + 1, i));
		}
}

int canWin(int state) { //현재 게임판의 상태 state가 주어졌을 때, 이번 차례인 player가 이기면 1, 지면 0을 반환
	//check memo
	int& ret = cache[state];
	if (ret != -1)
		return ret;
	//step
	ret = 0;
	for (int i = 0; i < moves.size(); i++) {
		if (state & moves[i]) continue;
		if (!canWin(state | moves[i])) {
			ret = 1;
			break;
		}
	}
	return ret;
}