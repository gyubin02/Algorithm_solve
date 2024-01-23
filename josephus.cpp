//¹®Á¦ ID : JOSEPHUS
#include <iostream>
#include <list>
using namespace std;
void func();

int N, K;

int main() {
	int cases;
	cin >> cases;
	while (cases-- > 0) {
		cin >> N >> K;
		func();
	}
}

void func() {
	list<int> p;
	int size = N;
	for (int num = 1; num <= N; num++)
		p.push_back(num);
	list<int>::iterator kill = p.begin();
	while (size > 2) {
		kill = p.erase(kill);
		if (kill == p.end()) kill = p.begin();
		size--;
		for (int i = 0; i < K - 1; i++) {
			kill++;
			if (kill == p.end()) kill = p.begin();
		}
	}
	cout << p.front() << " " << p.back() << "\n";
}