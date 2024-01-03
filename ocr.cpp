//문제 ID : OCR
#include <iostream>
using namespace std;

const int MAXM = 500;
const int MAXN = 100;
int m, n, q;
double B[MAXM+1], T[MAXM+1][MAXM+1], M[MAXM+1][MAXM+1], cache[MAXN][MAXM];
int R[MAXM];
int choices[MAXN][MAXM];
string word[MAXM];

int main() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXM; j++)
			cache[i][j] = 1.0;

	cin >> m >> q;
	for (int i = 0; i < m; i++) cin >> word[i];
	for (int i = 0; i < m; i++) cin >> B[i];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			cin >> T[i][j];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			cin >> M[i][j];

}

//g(i) = T[Q[i-1]][Q[i]]M[Q[i]][R[i]]
double ocr(int words, int pre) { //Q[words-1] == pre일 때 g(words) + .. + g(n-1)의 최대값
	//base
	if (words == n) return 0;
	//check memo
	double& ret = cache[words][pre];
	if (ret != 1.0) return ret;
	//no memo
	ret = -1e200;
	for (int cur = 0; cur < n; cur++) {
		double g_words = T[pre][cur] * M[cur][R[words]];
		double cand = g_words + ocr(words + 1, cur);

		if (cand > ret) {
			ret = cand;
			choices[words][pre] = cur;
		}
	}
	return ret;
}