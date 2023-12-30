#include <iostream>
#include <vector>
using namespace std;
int func(int cur);
int func_memo(int cur);

int n;
vector<int> A;
int cache[500];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		cin >> n;
		A.resize(n);
		for (int i = 0; i < n; i++) { cin >> A[i]; cache[i] = -1; }
		int res = -1;
		for (int i = 0; i < n; i++) res = max(res, func_memo(i));
		cout << res << "\n";
	}
}

int func(int cur) {
	//base
	if (cur == n - 1) return 1;
	//step
	int ret = 1; //A[cur]은 무조건 포함되기 때문에 반환 값은 최소 -1
	for (int next = cur + 1; next < n; next++) { 
		if (A[next] > A[cur]) ret = max(ret, 1 + func(next)); //func(0) => func(1) .... func(n-1)// func(1) => func(2)....func(n-1)// ... //func(n-1)
	}
	return ret;
}

//동적 계획법
int func_memo(int cur) {
	//base
	if (cur == n - 1) return 1;
	int& ret = cache[cur];
	if (ret != -1) return ret;
	//step
	ret = 1; //A[cur]은 무조건 포함되기 때문에 반환 값은 최소 -1
	for (int next = cur + 1; next < n; next++) {
		if (A[next] > A[cur]) ret = max(ret, 1 + func(next)); //func(0) => func(1) .... func(n-1)// func(1) => func(2)....func(n-1)// ... //func(n-1)
	}
	return ret;
}