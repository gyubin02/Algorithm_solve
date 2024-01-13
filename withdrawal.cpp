//¹®Á¦ ID : WITHDRAWAL
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool decision(double x);
double optimization();

int n, k;
int c[1000], r[1000];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	while (T-- > 0) {
		cin >> n >> k;
		for (int i = 0; i < n; i++)
			cin >> r[i] >> c[i];
		cout << optimization() << "\n";
	}
}

bool decision(double x) {
	vector<double> s;
	for (int i = 0; i < n; i++)
		s.push_back(x * c[i] - r[i]);
	sort(s.begin(), s.end());
	double sum = 0;
	for (int i = n - k; i < n; i++)
		sum += s[i];
	return sum >= 0;
}

double optimization() {
	double lo = -1e-9, hi = 1;
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return (lo + hi) / 2;
}