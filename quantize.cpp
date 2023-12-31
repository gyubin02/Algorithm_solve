#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int quantize(int cur, int parts);
int minimize(int start, int end);
int minimize2(int start, int end);
void preCalc();

int n, s;
vector<int> arr(100, 0);
int cache[101][11];
const int INF = 999999999;
int sum1[100];
int sum2[100];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 10; j++)
				cache[i][j] = -1;
		cin >> n >> s;
		for (int i = 0; i < n; i++) cin >> arr[i];
		sort(arr.begin(), arr.begin() + n);
		preCalc();
		cout << quantize(0, s) << "\n";
	}
}

int quantize(int cur, int parts) {
	//base
	if (cur == n) return 0;
	if (parts == 0) return INF;

	//check memo
	int& ret = cache[cur][parts];
	if (ret != -1) return ret;

	//step
	ret = INF;
	for (int partSize = 1; partSize + cur <= n; partSize++)
		ret = min(ret, minimize2(cur, cur + partSize - 1) + quantize(cur + partSize, parts - 1));
	return ret;
}

int minimize(int start, int end) { //arr[start]부터 arr[end]까지를 하나의 숫자로 양자화 했을 때 오차 제곱의 최소를 반환
	if (start == end) return 0;
	int ret = INF;
	for (int sub = arr[start]; sub <= arr[end]; sub++) {
		int sum = 0;
		for (int idx = start; idx <= end; idx++)
			sum += (arr[idx] - sub) * (arr[idx] - sub);
		ret = min(ret, sum);
	}
	return ret;
}

int minimize2(int start, int end) {
	if (start == end) return 0;
	int s1 = sum1[end] - (start == 0 ? 0 : sum1[start - 1]);
	int s2 = sum2[end] - (start == 0 ? 0 : sum2[start - 1]);
	int m = int(0.5 + (double)s1 / (end - start + 1));
	int ret = s2 - (2 * m * s1) + m * m * (end - start + 1);
	return ret;
}

void preCalc() {
	sum1[0] = arr[0];
	sum2[0] = arr[0] * arr[0];
	for (int i = 1; i < n; i++) {
		sum1[i] = sum1[i - 1] + arr[i];
		sum2[i] = sum2[i - 1] + arr[i] * arr[i];
	}
}