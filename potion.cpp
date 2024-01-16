//¹®Á¦ ID : POTION
#include <iostream>
#include <vector>
using namespace std;
vector<int> solve();
int gcd(int p, int q);

int r[200], p[200], n;

int main() {
	int cases;
	cin >> cases;
	while (cases-- > 0) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> r[i];
		for (int i = 0; i < n; i++)
			cin >> p[i];
		vector<int> ret = solve();
		for (int i = 0; i < n; i++)
			cout << ret[i] << " ";
	}
}

vector<int> solve() {
	int b = gcd(r[0], 0);
	for (int i = 1; i < n; i++)
		b = gcd(b, r[i]);
	int a = b;
	for (int i = 0; i < n; i++) {
		int cand = (b * p[i] + r[i] - 1) / r[i];
		a = max(a, cand);
	}
	vector<int> ret;
	for (int i = 0; i < n; i++)
		ret.push_back(r[i] * (a / b) - p[i]);
	return ret;
}

int gcd(int p, int q) {
	return (q == 0) ? p : gcd(q, p % q);
}