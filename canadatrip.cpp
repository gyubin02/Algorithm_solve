#include <iostream>
using namespace std;
bool decision(int x);
int search();

int N, K;
int L[5000], M[5000], G[5000];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	while (T-- > 0) {
		cin >> N >> K;
		for (int i = 0; i < N; i++)
			cin >> L[i] >> M[i] >> G[i];
		cout << search() << "\n";
	}
}

bool decision(int x) {
	int sum = 0;
	for (int i = 0; i < N; i++)
		if (x >= L[i] - M[i])
			sum += (min(x, L[i]) - (L[i] - M[i])) / G[i] + 1;
	return sum >= K;
}

int search() {
	int lo = -1; //decision(lo) == false
	int hi = 8030000; //decision(hi) == true
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}