//¹®Á¦ ID : ITES
#include <iostream>
#include <queue>
using namespace std;

int N, K;

struct RNG {
	unsigned seed;
	RNG() :seed(1983){}
	unsigned next() {
		unsigned ret = seed;
		seed = (seed * 214013) + 2531011;
		return (ret % 10000) + 1;
	}
};
int func();

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		cin >> N >> K;
		cout << func() << "\n";
	}
}

int func() {
	RNG r; 
	queue<int> q; 
	int sum = 0, count = 0;

	for (int i = 0; i < N; i++) {
		int num = r.next();
		q.push(num);
		sum += num;
		while (sum > K) {
			sum -= q.front();
			q.pop();
		}
		if (sum == K) count++;
	}
	return count;
}