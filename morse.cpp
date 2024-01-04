//문제 ID : MORSE
#include <iostream>
using namespace std;
void morse_ex(int n, int m, string s);
void precalc();
string morse_rec(int n, int m, int k);

const int MAXK = 1000000000;
int skip, n, m, k;
int bino[201][101];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	precalc();
	int cases;
	cin >> cases;
	while (cases--) {

		cin >> n >> m >> k;
		cout << morse_rec(n, m, k) << "\n";
	}
}

void morse_ex(int n, int m, string s) {
	//base
	if (skip == -1) return;
	if (n == 0 && m == 0) {
		if (skip == 0) cout << s << "\n";
		skip--;
		return;
	}
	if (bino[n + m][n] <= skip) {
		skip -= bino[n + m][n];
		return;
	}
	//step
	if (n > 0) morse_ex(n - 1, m, s + '-');
	if (m > 0) morse_ex(n, m - 1, s + 'o');
}

string morse_rec(int n, int m, int k) { //장조 n개, 단조 m개로 만들 수 있는 문자열 중 k 번째 문자열을 반환
	//base
	if (n == 0) return string(m, 'o');
	if (m == 0) return string(n, '-');
	//step
	if (bino[n + m - 1][m] < k) return 'o' + morse_rec(n, m - 1, k - bino[n + m - 1][m]);
	return '-' + morse_rec(n - 1, m, k);
}

void precalc() {
	for (int i = 0; i < 201; i++) bino[i][0] = 1;
	for (int i = 1; i < 201; i++)
		for (int j = 1; j < 101; j++) 
			bino[i][j] = min(MAXK + 1, bino[i - 1][j] + bino[i - 1][j - 1]);
}