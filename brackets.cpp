//¹®Á¦ ID : BRACKETS2
#include <iostream>
#include <stack>
using namespace std;
bool func(const string& str);

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		string str;
		cin >> str;
		bool ret = func(str);
		if (ret) cout << "YES" << "\n";
		else cout << "NO" << "\n";
	}
}

bool func(const string& str) {
	stack<char> s;
	string opening("({["), closing(")}]");
	for (int i = 0; i < str.size(); i++) {
		//¿©´Â °ýÈ£ÀÎ °æ¿ì
		if (opening.find(str[i]) != -1)
			s.push(str[i]);
		//´Ý´Â °ýÈ£ÀÎ °æ¿ì
		else {
			if (s.empty()) return false;
			if (opening.find(s.top()) != closing.find(str[i])) return false;
			s.pop();
		}
	}
	return s.empty();
}