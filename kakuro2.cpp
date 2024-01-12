//문제 ID : KAKURO2
#include <iostream>
using namespace std;

int candidates[11][46][513], hint[21][21][2], known[401], length[401], Sum[401], value[21][21], color[21][21];
const int BLACK_HINT = 0;
const int WHITE = 1;
int n;
//candidates[len][sum][known] : 연속된 len개의 흰 칸에 적힌 수 합이 sum이어야 하고, 이미 적힌 숫자의 집합이 known일 때, 후보의 집합을 저장
//hint[y][x][0] : (y, x)의 세로 힌트 번호, hint[y][x][1] : (y, x)의 가로 힌트 번호
//known[i] : i번 hint의 연속된 흰 칸에 적힌 숫자의 집합
//length[i] : i번 hint의 연속된 흰 칸의 개수
//Sum[i] : i번 hint의 연속된 흰 칸에 적힌 수 합
//value[y][x] : (y, x)에 적힌 숫자
//color[y][x] : (y, x)가 검은 칸이거나 hint 칸이면 0, 흰 칸이면 1

int getSize(int mask) {

}

int getSum(int mask) {

}

void put(int y, int x, int val) {
	for (int h = 0; h < 2; h++)
		known[hint[y][x][h]] |= (1 << val);
	value[y][x] = val;
}

void remove(int y, int x, int val) {
	for (int h = 0; h < 2; h++)
		known[hint[y][x][h]] &= ~(1 << val);
	value[y][x] = 0;
}

int getCandhint(int hint) {
	return candidates[length[hint]][Sum[hint]][known[hint]];
}

int getCandcoord(int y, int x) {
	return getCandhint(hint[y][x][0]) & getCandhint(hint[y][x][1]);
}

void precalc() {
	//initialize
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 46; j++)
			for (int k = 0; k < 513; k++)
				candidates[i][j][k] = 0;
	for (int set = 0; set < 1024; set += 2) {
		int len = getSize(set), sum = getSum(set);
		int subset = set;
		while (true) {
			candidates[len][sum][subset] |= (set & ~subset);
			if (subset == 0) break;
			subset = (subset - 1) & set;
		}
	}
}

void search() {
	int y = -1, x = -1, minCand = 1023;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (color[i][j] == WHITE && value[y][x] == 0) {
				int cand = getSize(getCandcoord(i, j));
				if (getSize(minCand) > getSize(cand)) {
					minCand = cand;
					y = i; x = j;
				}
			}
	//base
	if (minCand == 0) return;
	if (minCand == 1023) {
		printSolution();
		return;
	}
	//step
	for(int val=1; val<10; val++)
		if (minCand & (1 << val)) {
			put(y, x, val);
			search();
			remove(y, x, val);
		}
}

void printSolution() {

}