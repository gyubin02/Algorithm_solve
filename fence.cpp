//¹®Á¦ ID : FENCE
#include <iostream>
#include <vector>
using namespace std;
int func(int start, int end, vector<int>& fence);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases-- > 0) {
		int N;
		cin >> N;
		vector<int> fence(N, 0);
		for (int i = 0; i < N; i++) cin >> fence[i];
		cout << func(0, N - 1, fence) << "\n";
	}
}

int func(int start, int end, vector<int>& fence) {
	//base
	if (start == end) return fence[start];
	//step
	int half = (start + end) / 2;
	int left = func(start, half, fence); //left sub problem
	int right = func(half + 1, end, fence); //right sub problem
	int lo = half; int hi = half + 1;
	int height = min(fence[lo], fence[hi]);
	int ret = max(max(left, right), 2 * height);

	while (lo > start || hi < end) {
		if (hi < end && (lo == start || fence[hi + 1] > fence[lo - 1])) {
			hi++;
			height = min(height, fence[hi]);
		}
		else {
			lo--;
			height = min(height, fence[lo]);
		}
		int area = (hi - lo + 1) * height;
		ret = max(ret, area);
	}
	return ret;
}