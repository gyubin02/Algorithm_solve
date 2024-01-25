//¹®Á¦ ID : PALINDROMIZE
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> getP(const string& N);
int palindromize(const string& N);

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		string s;
		cin >> s;
		cout << s.size() + palindromize(s) << "\n";
	}
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

int palindromize(const string& N) {
	vector<int> p = getP(N);
	string N_rev = N;
	reverse(N_rev.begin(), N_rev.end());
	int begin = 0, matched = 0;
	while (begin < N.size()) {
		for (; matched + begin < N.size(); matched++) {
			if (N[matched + begin] != N_rev[matched])
				break;
		}
		if ((matched + begin) == N.size())
			return begin;
		if (matched == 0) begin++;
		else {
			begin += (matched - p[matched - 1]);
			matched = p[matched - 1];
		}
	}
	return N.size();
}