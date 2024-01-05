//문제 ID : DRAGON
#include <iostream>
#include <assert.h>
using namespace std;
void func(const string& s, int n);
void precalc();
char curve(const string& s, int n, int k);

const int MAX_P = 1000000000;
const int MAX_N = 50;
int k;
int length[MAX_N+1]; //length[i] = X나 Y를 i세대 만큼 진화시킨 문자열의 길이

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	precalc();
	int cases;
	cin >> cases;
	while (cases--) {
		int n, p, l;
		cin >> n >> p >> l;

		for (int idx = p; idx < p + l; idx++)
			cout << curve("FX", n, idx);
		cout << "\n";
	}
}

void func(const string& s, int n) { //s를 n세대 진화시킨 결과
	//base
	if (n == 0) {
		cout << s;
		return;
	}
	//step
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'X') func("X+YF", n - 1);
		else if (s[i] == 'Y') func("FX-Y", n - 1);
		else cout << s[i];
	}
}

char curve(const string& s, int n, int k) { //s를 n세대 진화시킨 결과의 k번째 문자를 반환
	//base
	if (n == 0) {
		assert(k <= s.size());
		return s[k - 1];
	}
	//step
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'X' || s[i] == 'Y') {
			if (length[n] < k)
				k -= length[n];
			else if (s[i] == 'X')
				return curve("X+YF", n - 1, k);
			else
				return curve("FX-Y", n - 1, k);
		}
		else if (k > 1)
			k--;
		else
			return s[i];
	}
}

void precalc() {
	length[0] = 1;
	for (int i = 1; i < MAX_N+1; i++)
		length[i] = min(length[i - 1] * 2 + 2, MAX_P);
}