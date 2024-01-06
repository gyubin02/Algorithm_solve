//문제 ID : ZIMBABWE
/*
#include <iostream>
#include <algorithm>
using namespace std;
int func(int index, int used, int mod, bool less);

const int MAX = 15;
const int MOD = 1000000007;
string e, digits;
int m;
int cache[1 << 14][20][2];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		for (int i = 0; i < (1 << 14); i++)
			for (int j = 0; j < 20; j++)
				cache[i][j][0] = cache[i][j][1] = -1;
		cin >> e >> m;
		digits = e;
		sort(digits.begin(), digits.end());
		cout << func(0, (0 << 14), 0, false) << "\n";
	}
}

//현재 index개의 플라스틱을 사용했을 때, 남은 플라스틱으로 만들 수 있는 가격들
//중 e보다 작고 m의 배수인 가격의 개수를 반환
int func(int index, int used, int mod, bool less) { 
	//base
	if (index == e.size())
		return (less && mod == 0) ? 1 : 0;
	//check memo
	int& ret = cache[used][mod][less];
	if (ret != -1) return ret;
	//step
	ret = 0;
	for (int next = 0; next < digits.size(); next++) {
		if (used & (1 << next)) 
			continue;
		if (!less && digits[next] > e[index]) continue;
		if (next != 0 && digits[next - 1] == digits[next] && (used & (1 << next - 1)))
			continue;
		int nextUsed = used | (1 << next);
		int nextMod = (10 * mod + digits[next] - '0') % m;
		bool nextLess = less || digits[next] < e[index];
		ret += func(index + 1, nextUsed, nextMod, nextLess);
		ret %= MOD;
	}
	return ret;
}
*/