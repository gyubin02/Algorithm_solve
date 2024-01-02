//문제 ID : POLY
#include <iostream>
using namespace std;
int poly(int n, int first);

int cache[101][101];
const int MOD = 10000000;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases-- > 0) {
		for (int i = 0; i < 101; i++)
			for (int j = 0; j < 101; j++)
				cache[i][j] = -1;
		int n;
		cin >> n;
		int ret = 0;
		for (int first = 1; first <= n; first++) ret += poly(n, first);
		cout << ret << "\n";
	}
}

int poly(int n, int first) { //n개의 정사각형을 이용해서 만들 수 있는 세로 단조인 폴리오미노의 개수 반환(맨 윗줄에 first개의 정사각형 이용)
	//base
	if (n == first) return 1;
	//check memo
	int& ret = cache[n][first];
	if (ret != -1) return ret;
	//step
	ret = 0;
	for (int second = 1; second <= n - first; second++) {
		int a = (second + first - 1)* poly(n - first, second);
		a %= MOD;
		ret = (ret + a) % MOD;
	}
	return ret;
}