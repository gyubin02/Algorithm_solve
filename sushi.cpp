//¹®Á¦ ID : SUSHI
#include <iostream>
using namespace std;
int select();

int n, m, price[20], pref[20];
int c[220];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		cin >> n >> m;
		for (int i = 0; i < n; i++)
			cin >> price[i] >> pref[i];
		m /= 100;
		for (int i = 0; i < n; i++)
			price[i] /= 100;
		cout << select() << "\n";
	}
}

int select() {
	c[0] = 0;
	for (int budget = 1; budget <= m; budget++) {
		int cand = 0;
		for(int dish=0; dish<20; dish++)
			if (budget >= price[dish]) {
				cand = max(cand, pref[dish] + c[(budget - price[dish]) % 220]);
			}
		c[budget % 220] = cand;
	}
	return c[m % 220];
}