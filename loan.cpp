//문제 ID : LOAN
#include <iostream>
using namespace std;
bool repay(double C);
double search();

double N, P;
int M;

int main() {
	int T;
	cin >> T;
	while (T-- > 0) {
		cin >> N >> M >> P;
		cout << search() << "\n";
	}
}

bool repay(double C) { //매달 C원씩 갚아서 다 갚을 수 있는지 여부를 반환
	double balance = N;
	for (int i = 0; i < M; i++) {
		balance = balance * (1 + P / 1200);
		balance -= C;
	}
	return balance <= 0;
}

double search() {
	double lo = 0, hi = N * (1 + P / 1200); //repay(lo) == false, repay(hi) == true : 불변
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2;
		if (repay(mid))
			hi = mid;
		else
			lo = mid;
	}
	return (lo + hi) / 2;
}