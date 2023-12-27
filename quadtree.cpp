//¹®Á¦ ID : QUADTREE
#include <iostream>
using namespace std;
string func(string::iterator& it);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases-- > 0) {
		string input;
		cin >> input;
		string::iterator it = input.begin();
		cout << func(it) << "\n";
	}
	return 0;
}

string func(string::iterator& it) {
	char head = *it;
	it++;
	//base
	if (head == 'w' || head == 'b') return string(1, head);
	//step
	string upperLeft = func(it);
	string upperRight = func(it);
	string lowerLeft = func(it);
	string lowerRight = func(it);
	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}