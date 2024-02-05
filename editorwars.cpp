//¹®Á¦ ID : EDITORWARS
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct UnionFind {
	vector<int> parent, rank, enemy, size;
	UnionFind(int _n) :parent(_n), rank(_n), enemy(_n, -1), size(_n, 1) {
		for (int i = 0; i < parent.size(); i++)
			parent[i] = i;
	}

	int find(int x) {
		if (x == parent[x]) return x;
		return parent[x] = find(x);
	}

	int merge(int x, int y) {
		if (x == -1 || y == -1) return max(x, y);
		x = find(x); y = find(y);
		if (x == y) return x;
		if (rank[x] > rank[y]) swap(x, y);
		parent[x] = y;
		size[y] += size[x];
		if (rank[x] == rank[y])rank[y]++;
		return y;
	}

	bool dis(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return false;
		int a = merge(enemy[x], y); 
		int b = merge(x, enemy[y]);
		enemy[a] = b; enemy[b] = a;
		return true;
	}

	bool ack(int x, int y) {
		x = find(x); y = find(y);
		if (enemy[x] == y) return false;
		int a = merge(x, y);
		int b = merge(enemy[x], enemy[y]);
		enemy[a] = b; 
		if(b != -1) enemy[b] = a;
		return true;
	}
};

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		int N, M, tt;
		cin >> N >> M;
		UnionFind u(N);
		bool t = true;
		for (int i = 1; i <= M; i++) {
			string str;
			cin.ignore();
			getline(cin, str);
			int x = str[4] - '0', y = str[6] - '0';
			if (str[0] == 'A') t = u.ack(x, y);
			else t = u.dis(x, y);
			if (!t) {
				tt = i;
				break;
			}
		}
		int ret = 0;
		for (int i = 0; i < N; i++) {
			if (!t) break;
			if (i != u.find(i) || i < u.enemy[i]) continue;
			int s_1 = u.size[i], s_2 = (u.enemy[i] == -1) ? 0 : u.size[u.enemy[i]];
			ret += max(s_1, s_2);
		}
		if (!t) cout << "CONTRADICTION AT " << tt << "\n";
		else cout << "MAX PARTY SIZE IS " << ret << "\n";
	}
}
