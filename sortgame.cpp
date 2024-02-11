//¹®Á¦ ID : SORTGAME
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

map<vector<int>, int> tree;
void bfs(vector<int>& A) {
	queue<vector<int>> q;
	tree[A] = 0;
	q.push(A);
	while (!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		int n = here.size();
		int cost = tree[here];
		for(int s=0; s<n-1; s++)
			for (int e = s + 2; e <= n; e++) {
				reverse(here.begin() + s, here.begin() + e);
				if (tree.count(here) == 0) {
					tree[here] = cost + 1;
					q.push(here);
				}
				reverse(here.begin() + s, here.begin() + e);
			}
	}
}

void precalc() {
	for (int i = 1; i <= 8; i++) {
		vector<int> A(i);
		for (int j = 0; j < i; j++)
			A[j] = j;
		bfs(A);
	}
}

int main() {
	precalc();
	int C;
	cin >> C;
	while (C-- > 0) {
		int N;
		cin >> N;
		vector<int> A(N);
		for (int i = 0; i < N; i++)
			cin >> A[i];

		vector<int> fixed(N);
		for (int i = 0; i < N; i++) {
			int smaller = 0;
			for (int j = 0; j < N; j++)
				if (A[i] > A[j])
					smaller++;
			fixed[i] = smaller;
		}
		cout << tree[fixed] << "\n";
	}
}