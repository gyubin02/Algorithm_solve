//¹®Á¦ ID : TILING2
#include <iostream>
using namespace std;
int func(int cur);

int n;
int cache[100];
const int MOD = 1000000007;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		for (int i = 0; i < 100; i++) cache[i] = -1;
		cin >> n;
		cout << func(0) << "\n";
	}
}

int func(int cur) {
	//base
	if (cur >= n - 1) return 1;
	//check memo
	int& ret = cache[cur];
	if (ret != -1) return ret;
	//no memo
	return ret = (func(cur + 1) + func(cur + 2)) % MOD;
}