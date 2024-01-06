//¹®Á¦ ID : TICTACTOE
#include <iostream>
#include <vector>
using namespace std;
int transfer(const vector<string>& board);
bool isFinished(vector<string>& board, char turn);
bool isWin(const vector<string>& board, char symbol);
int canWin(vector<string>& board, char turn);

vector<string> board(3);
int cache[3 * (10 ^ 9) - 1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		for (int i = 0; i < 3 * (10 ^ 9) - 1; i++)
			cache[i] = -2;
		for (int i = 0; i < 3; i++)
			cin >> board[i];
		int ret = canWin(board, 'x');
		if (ret == -1) cout << 'o';
		if (ret == 0) cout << "TIE";
		if (ret == 1) cout << 'x';
		cout << "\n";
	}
}

int transfer(const vector<string>& board) {
	int ret = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			ret *= 3;
			if (board[i][j] == 'o') ret++;
			else if (board[i][j] == 'x') ret += 2;
		}
	return ret;
}

bool isFinished(vector<string>& board, char turn) {
	bool ret = false;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if (board[i][j] == '.') {
				board[i][j] = turn;
				ret = isWin(board, turn);
				board[i][j] = '.';
				if (ret)
					return ret;
			}
	return ret;
}

bool isWin(const vector<string>& board, char symbol) {
	//check rows
	bool win;
	for (int i = 0; i < 3; i++) {
		win = true;
		for (int j = 0; j < 3; j++)
			if (board[i][j] != symbol)
				win = false;
		if (win) return true;
	}
	//check cols
	for (int i = 0; i < 3; i++) {
		win = true;
		for (int j = 0; j < 3; j++)
			if (board[j][i] != symbol)
				win = false;
		if (win) return true;
	}
	//check diagonal
	win = true;
	for (int i = 0; i < 3; i++)
		if (board[i][i] != symbol)
			win = false;
	if (win) return true;
	win = true;
	for (int i = 0; i < 3; i++)
		if (board[i][2 - i] != symbol)
			win = false;
	if (win) return true;

	return false;
}

int canWin(vector<string>& board, char turn) {
	//base
	if (isFinished(board, 'o' + 'x' - turn))
		return -1;
	//check memo
	int& ret = cache[transfer(board)];
	if (ret != -2) return ret;
	//step
	ret = 2;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (board[i][j] == '.') {
				board[i][j] = turn;
				ret = min(ret, canWin(board, 'o' + 'x' - turn));
				board[i][j] = '.';
			}
	if (ret == 2) 
		return ret = 0;
	ret = -ret;
	return ret;
}