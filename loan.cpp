//���� ID : LOAN
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

bool repay(double C) { //�Ŵ� C���� ���Ƽ� �� ���� �� �ִ��� ���θ� ��ȯ
	double balance = N;
	for (int i = 0; i < M; i++) {
		balance = balance * (1 + P / 1200);
		balance -= C;
	}
	return balance <= 0;
}

double search() {
	double lo = 0, hi = N * (1 + P / 1200); //repay(lo) == false, repay(hi) == true : �Һ�
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2;
		if (repay(mid))
			hi = mid;
		else
			lo = mid;
	}
	return (lo + hi) / 2;
}