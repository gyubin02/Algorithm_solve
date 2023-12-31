//¹®Á¦ ID : JLIS
#include <iostream>
using namespace std;
int jlis(int curA, int curB);

const long long NEGINF = -9999999999;
int n, m, A[100], B[100];
int cache[101][101];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases-- > 0) {
		cin >> n >> m;
		for (int i = 0; i < n; i++) cin >> A[i];
		for (int i = 0; i < m; i++) cin >> B[i];
		for (int i = 0; i < 101; i++)
			for (int j = 0; j < 101; j++)
				cache[i][j] = -1;
		cout << jlis(-1, -1)-2 << "\n";
	}
}

int jlis(int curA, int curB) {
	int& ret = cache[curA + 1][curB + 1];
	if (ret != -1) return ret;
	ret = 2;
	long long a = (curA == -1 ? NEGINF : A[curA]);
	long long b = (curB == -1 ? NEGINF : B[curB]);
	long long maxElement = max(a, b);
	for (int nextA = curA + 1; nextA < n; nextA++)
		if (maxElement < A[nextA])
			ret = max(ret, jlis(nextA, curB) + 1);
	for (int nextB = curB + 1; nextB < m; nextB++)
		if (maxElement < B[nextB])
			ret = max(ret, jlis(curA, nextB) + 1);

	return ret;
}