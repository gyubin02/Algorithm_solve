//¹®Á¦ ID : NERD2
#include <iostream>
#include <map>
using namespace std;
bool inGray(int p, int q, map<int, int>& tree);
void calc(int p, int q, map<int, int>& tree);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int C;
	cin >> C;
	while (C-- > 0) {
		int N;
		cin >> N;
		map<int, int> tree;
		int ret = 0;
		for (int i = 0; i < N; i++) {
			int p, q;
			cin >> p >> q;
			if (!inGray(p, q, tree)) {
				calc(p, q, tree);
				tree[p] = q;
			}
			ret += tree.size();
		}
		cout << ret << "\n";
	}
}

bool inGray(int p, int q, map<int, int>& tree) {
	map<int, int>::iterator it = tree.lower_bound(p);
	if (it == tree.end()) return false;
	return q < it->second;
}

void calc(int p, int q, map<int, int>& tree) {
	map<int, int>::iterator it = tree.lower_bound(p);
	if (it == tree.begin()) return;
	it--;
	while (true) {
		if (q < it->second) break;
		if (it == tree.begin()) {
			tree.erase(it);
			break;
		}
		map<int, int>::iterator jt = it;
		jt--;
		tree.erase(it);
		it = jt;
	}
}