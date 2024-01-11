//문제 ID : BOARDCOVER2
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int solve(vector<string>& block);
void search(int placed);
vector<string> turn_block(const vector<string>& block);
void getCoordinate(vector<string>& block);
bool set(int y, int x, vector<pair<int, int>>& block, int delta);

int H, W, R, C;
vector<vector<pair<int, int>>> coord;
vector<vector<int>> board;
int best;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	while (T--) {
		cin >> H >> W >> R >> C;
		board.resize(H, vector<int>(W));
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++) {
				char c;
				cin >> c;
				if (c == '#') board[i][j] = 1;
				else board[i][j] = 0;
			}
		vector<string> block(R);
		for (int i = 0; i < R; i++)
			cin >> block[i];
	}
}

int solve(vector<string>& block) {
	best = -1;
	getCoordinate(block);
	search(0);
	return best;
}

void search(int placed) {
	int firstX = -1, firstY = -1;
	for(int y = 0; y<board.size(); y++)
		for(int x=0; x<board[0].size(); x++)
			if (board[y][x] == 0 && firstY == -1) {
				firstY = y;
				firstX = x;
			}
	//base
	if (firstY == -1) {
		best = max(best, placed);
		return;
	}
	//step
	for (int i = 0; i < coord.size(); i++) {
		if (set(firstY, firstX, coord[i], 1))
			search(placed + 1);
		set(firstY, firstX, coord[i], -1);
	}
	board[firstY][firstX] = 1;
	search(placed);
	board[firstY][firstX] = 0;
}

vector<string> turn_block(const vector<string>& block) { //block을 90도 돌린다
	vector<string> ret(block[0].size(), string(block.size(), ' '));
	for (int y = 0; y < block.size(); y++)
		for (int x = 0; x < block[0].size(); x++)
			ret[x][block.size() - 1 - y] = block[y][x];
	return ret;
}

void getCoordinate(vector<string>& block) { //블록 칸들의 상대 좌표를 coord에 담는다
	coord.clear();
	coord.resize(4);
	for (int turn = 0; turn < 4; turn++) {
		int firstY = -1, firstX = -1;
		for (int y = 0; y < block.size(); y++)
			for (int x = 0; x < block[0].size(); x++)
				if (block[y][x] == '#') {
					if (firstY == -1) {
						firstY = y;
						firstX = x;
					}
					coord[turn].push_back(make_pair(y - firstY, x - firstX));
				}
		block = turn_block(block);
	}
	sort(coord.begin(), coord.end());
	coord.erase(unique(coord.begin(), coord.end()), coord.end());
}

bool set(int y, int x, vector<pair<int, int>>& block, int delta) {
	bool ok = true;
	for (int i = 0; i < block.size(); i++) {
		int ny = y + block[i].first;
		int nx = x + block[i].second;
		if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
			ok = false;
		if ((board[ny][nx] += delta) > 1)
			ok = false;
	}
	return ok;
}