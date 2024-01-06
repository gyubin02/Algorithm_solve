//¹®Á¦ ID : TICTACTOE
#include <iostream>
#include <vector>
using namespace std;
int transfer(const vector<string>& board);
bool isFinished(vector<string>& board, char turn);
char whoWin(const vector<string>& board);
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
	char ret;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if (board[i][j] == '.') {
				board[i][j] = turn;
				ret = whoWin(board);
				board[i][j] = '.';
				if (ret == turn)
					return true;
			}
	return false;
}

char whoWin(const vector<string>& board) {
	//check rows
	for (int line = 0; line < 3; line++)
		if (board[line][0] == board[line][1] && board[line][0] == board[line][2])
			return board[line][0];
	//check cols
	for (int line = 0; line < 3; line++)
		if (board[0][line] == board[1][line] && board[0][line] == board[2][line])
			return board[0][line];
	//check diagonal
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
		return board[0][0];
	if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
		return board[0][2];
	return '@';
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