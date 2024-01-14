//¹®Á¦ ID : RATIO
#include <iostream>
using namespace std;
bool decision(long long x);
int search();

long long N, M;

int main() {
	int T;
	cin >> T;
	while (T-- > 0) {
		cin >> N >> M;
		cout << search() << "\n";
	}
}

bool decision(long long x) {
	return (M + x) * 100 / (N + x) > M * 100 / N;
}

int search() {
	long long lo = 0, hi = 2000000000;
	if (!decision(hi)) return -1;
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}