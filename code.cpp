//¹®Á¦ ID : BOARDCOVER
#include <iostream>
#include <vector>
using namespace std;

bool set(vector<vector<int>>& board, int delta, int type, int x, int y);
int func(vector<vector<int>>& board);


int blockType[4][3][2] = {
	{{0,0},{0,1},{1,0}},
	{{0,0},{0,1},{1,1}},
	{{0,0},{1,0},{1,1}},
	{{0,0},{1,0},{1,-1}}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases = 0;
	cin >> cases;
	while (cases-- > 0) {
		//
		int h = 0;
		int w = 0;
		//
		cin >> h >> w;
		vector<vector<int>> board(h);
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				char c;
				cin >> c;
				int a;
				if (c == '#') a = 1;
				else if (c == '.') a = 0;
				board[i].push_back(a);
			}
		}
			
		cout << func(board) << "\n";
	}
	return 0;
}

bool set(vector<vector<int>>& board, int delta, int type, int x, int y) {
	bool possible = true;
	for (int i = 0; i < 3; i++) {
		int nx = x + blockType[type][i][1];
		int ny = y + blockType[type][i][0];
		if (nx < 0 || nx >= board[0].size() || ny < 0 || ny >= board.size()) possible = false;
		else if ((board[ny][nx] += delta) > 1) possible = false;
	}
	return possible;
}

int func(vector<vector<int>>& board) {
	int firstX = -1;
	int firstY = -1;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] == 0) { firstX = j; firstY = i; break; }
		}
		if (firstX != -1) break;
	}
	if (firstX == -1) return 1;
	int sum = 0;
	for (int type = 0; type < 4; type++) {
		if (set(board, 1, type, firstX, firstY))
			sum += func(board);
		set(board, -1, type, firstX, firstY);
	}
	return sum;
}