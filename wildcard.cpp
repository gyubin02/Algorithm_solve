//���� ID : WILDCARD
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool match(string::iterator& it, string::iterator& it2);
bool match2(const string& s1, const string& s2);
int match3(int x, int y);

string s1, s2;
int cache[101][101];


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases = 0;
	cin >> cases;
	while (cases-- > 0) {

		cin >> s1;
		int n;
		cin >> n;
		vector<string> ans;
		while (n-- > 0) {
			//���� ��ȹ��
			for (int i = 0; i < 101; i++)
				for (int j = 0; j < 101; j++)
					cache[i][j] = -1;

			cin >> s2;
			/*
			string::iterator it = s1.begin();
			string::iterator it2 = s2.begin();
			if (match(it, it2)) cout << s2 << "\n";
			*/
			/*
			if (match2(s1, s2)) ans.push_back(s2);*/
			if (match3(0, 0)) ans.push_back(s2);
		}
		sort(ans.begin(), ans.end());
		for (int i = 0; i < ans.size(); i++) cout << ans[i] << "\n";
	}
}

bool match(string::iterator& it, string::iterator& it2) {
	//base
	if (it == s1.end() && it2 == s2.end()) return true;
	char ch = *it++;
	if (ch == '*' || it2 == s2.end()) return match(it, it2);
	if (it == s1.end() || it2 == s2.end()) return false;
	char ch2 = *it2++;
	string::iterator it_copy = it; string::iterator it2_copy = it2;
	if (ch == '?') return match(it, it2);
	if (ch == '*') return match(it, it2) || match(--it_copy, it2) || match(it, --it2_copy);
	//step
	if (ch == ch2) return match(it, it2);
	if (ch != ch2) return false;
	else return false;
}

//���� Ž��
bool match2(const string& s1, const string& s2) {
	int pos = 0;
	while (pos < s1.size() && pos < s2.size() && (s1[pos] == s2[pos] || s1[pos] == '?')) pos++;
	if (pos == s1.size())
		return pos == s2.size();
	if (s1[pos] == '*')
		for (int skip = 0; pos + skip <= s2.size(); skip++)
			if (match2(s1.substr(pos + 1), s2.substr(pos + skip))) return true;
	return false;
}

//���� ��ȹ�� O(n^3)
int match3(int x, int y) {
	int& ret = cache[x][y];
	if (ret != -1) return ret;
	while (x < s1.size() && y < s2.size() && (s1[x] == s2[y] || s1[x] == '?')) { x++; y++; }
	if (x == s1.size())
		return ret = (y == s2.size());
	if (s1[x] == '*')
		for (int skip = 0; y + skip <= s2.size(); skip++)
			if(match3(x+1, y+skip)) return ret = 1;
	return ret = 0;
}