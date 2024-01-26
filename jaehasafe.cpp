//문제 ID : JAEHASAFE
#include <iostream>
#include <vector>
using namespace std;
int kmp(const string& H, const string& N);
vector<int> getP(const string& N);
int solve(const string& original, const string& target);

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		int N;
		cin >> N;
		vector<string> state(N + 1);
		for (int i = 0; i <= N; i++)
			cin >> state[i];
		int ret = 0;
		for (int i = 0; i < N; i++) {
			if (i % 2 > 0)
				ret += solve(state[i], state[i + 1]);
			else
				ret += solve(state[i + 1], state[i]);
		}
		cout << ret << "\n";
	}
}

int solve(const string& original, const string& target) { //반시계 방향으로 돌려야 하는 횟수 반환
	return kmp(original + original, target);
}

int kmp(const string& H, const string& N) { //O(|H|)
	vector<int> p = getP(N), ret;
	int begin = 0, matched = 0;
	while (begin <= H.size() - N.size()) {
		for (; matched < N.size(); matched++)
			if (H[begin + matched] != N[matched])
				break;
		if (matched == N.size()) ret.push_back(begin);
		if (matched == 0) begin++;
		else {
			begin += (matched - p[matched - 1]);
			matched = p[matched - 1];
		}
	}
	return ret[0];
}

vector<int> getP(const string& N) {
	vector<int> ret(N.size(), 0);
	int begin = 1, matched = 0;
	while (begin < N.size()) {
		for (; begin + matched < N.size(); matched++) {
			if (N[begin + matched] != N[matched])
				break;
			ret[begin + matched] = matched + 1;
		}
		if (matched == 0) begin++;
		else {
			begin += (matched - ret[matched - 1]);
			matched = ret[matched - 1];
		}
	}
	return ret;
}