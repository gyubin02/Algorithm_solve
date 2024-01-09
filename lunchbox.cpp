//문제 ID : LUNCHBOX
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int func();

const int MAX_N = 10000;
int P[MAX_N], C[MAX_N];
int n;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> P[i];
		for (int i = 0; i < n; i++)
			cin >> C[i];
		cout << func() << "\n";
	}
}

// P(i) : i번째 도시락을 데우는데 걸리는 시간
// C(i) : i번째 도시락을 먹는데 걸리는 시간
// E(i) = P(0) + ... + P(i) + C(i)
// 최소화할 값 : max(E(0), ... , E(n-1)) 
int func() {
	vector<pair<int, int>> order;
	for (int i = 0; i < n; i++)
		order.push_back(make_pair(-C[i], i));
	sort(order.begin(), order.end());
	int E = 0, beginEat = 0;
	for (int i = 0; i < n; i++) {
		int box = order[i].second;
		beginEat += P[box];
		E = max(E, beginEat + C[box]);
	}
	return E;
}