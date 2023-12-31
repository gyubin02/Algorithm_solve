//문제 ID : PI
#include <iostream>
using namespace std;
int classify(int cur, int end);
int func(int cur);

int cache[10000];
string N;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases-- > 0) {
		for (int i = 0; i < 10000; i++) cache[i] = -1;
		cin >> N;
		cout << func(0) << "\n";
	}
}

int classify(int cur, int end) { //N(cur)부터 N(end)까지 읽는 난이도
	string M = N.substr(cur, end - cur + 1);
	if (M == string(M.size(), M[0])) return 1;
	bool progressive = true;
	for (int i = 0; i < M.size() - 1; i++)
		if (M[i + 1] - M[i] != M[1] - M[0]) progressive = false;
	if (progressive && abs(M[1] - M[0]) == 1) return 2;
	bool alternating = true;
	for (int i = 0; i < M.size(); i++)
		if (M[i] != M[i % 2]) alternating = false;
	if (alternating) return 4;
	if (progressive) return 5;
	return 10;
}

int func(int cur) {
	//base
	if (cur == N.size()) return 0;
	//check memo
	int& ret = cache[cur];
	if (ret != -1) return ret;
	//step
	ret = 999999;
	for (int L = 3; L <= 5; L++)
		if(cur + L <= N.size())
			ret = min(ret, classify(cur, cur + L - 1) + func(cur + L));
	return ret;
}