//문제 ID : MEASURETIME
#include <iostream>
#include <vector>
using namespace std;

int merge_sort(vector<int>& A, int left, int right) { //반전의 개수 반환
	//base
	if (left == right) return 0;
	//step
	vector<int> tmp(right - left + 1);
	int mid = (left + right) / 2, ret = 0;
	ret += merge_sort(A, left, mid);
	ret += merge_sort(A, mid + 1, right);
	int tmpIndex = 0, leftIndex = left, rightIndex = mid + 1;
	while (leftIndex <= mid || rightIndex <= right) {
		if (leftIndex <= mid && (rightIndex > right || A[leftIndex] <= A[rightIndex]))
			tmp[tmpIndex++] = A[leftIndex++];
		else {
			ret += mid - leftIndex + 1;
			tmp[tmpIndex++] = A[rightIndex++];
		}
	}
	for (int i = 0; i < tmp.size(); i++)
		A[left + i] = tmp[i];
	return ret;
}

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		int N;
		cin >> N;
		vector<int> A(N);
		for (int i = 0; i < N; i++)
			cin >> A[i];
		cout << merge_sort(A, 0, A.size() - 1) << "\n";
	}
}