//문제 ID : PASS486
#include <iostream>
using namespace std;
void eratosthenes();
void getNum();

const int MAX_N = 10000000;
int minFactor[MAX_N + 1], minFactorNum[MAX_N + 1], num[MAX_N + 1];

int main() {
	eratosthenes(); getNum();
	int cases;
	cin >> cases;
	while (cases-- > 0) {
		int n, lo, hi;
		cin >> n >> lo >> hi;
		int ret = 0;
		for (int i = lo; i <= hi; i++)
			if (num[i] == n) ret++;
		cout << ret << "\n";
	}
}

void eratosthenes() {
	minFactor[0] = minFactor[1] = -1;
	for (int i = 2; i <= MAX_N; i++)
		minFactor[i] = i;
	for (int i = 2; i <= (int)sqrt(MAX_N); i++)
		if (minFactor[i] == i)
			for (int j = i * i; j <= MAX_N; j += i)
				if (minFactor[j] == j)
					minFactor[j] = i;
}

void getNum() {
	num[1] = 1; //1인 경우
	for (int i = 2; i <= MAX_N; i++) {
		if (minFactor[i] == i) { //소수인 경우
			minFactorNum[i] = 1;
			num[i] = 2;
		}
		else { //합성수인 경우
			int j = i / minFactor[i];
			if (minFactor[i] != minFactor[j])
				minFactorNum[i] = 1;
			else
				minFactorNum[i] = minFactorNum[j] + 1;
			int p = minFactorNum[i];
			num[i] = (num[j] / p) * (p + 1);
		}
	}
}