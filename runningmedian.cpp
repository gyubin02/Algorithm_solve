//문제 ID : RUNNINGMEDIAN
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef unsigned long long ull;
struct rns {
	ull seed = 1983, a, b;
	rns(int a, int b) :a(a), b(b){}
	int next() {
		ull ret = seed;
		seed = (seed * a + b) % 20090711;
		return ret;
	}
};

int findMedian(priority_queue<int>& maxHeap, priority_queue<int, vector<int>, greater<int>>& minHeap, int key) { //key가 추가됐을 때, 수열의 중간값 반환
	//1번 조건
	if (maxHeap.size() == minHeap.size())
		maxHeap.push(key);
	else
		minHeap.push(key);
	//2번 조건
	if (!minHeap.empty() && maxHeap.top() > minHeap.top()) {
		int a = maxHeap.top(), b = minHeap.top();
		maxHeap.pop(); minHeap.pop();
		maxHeap.push(b); minHeap.push(a);
	}
	return maxHeap.top();
}

int main() {
	int MOD = 20090711;
	int C;
	cin >> C;
	while (C-- > 0) {
		int N, a, b;
		cin >> N >> a >> b;
		rns r(a, b);
		priority_queue<int, vector<int>, less<int>> maxHeap;
		priority_queue<int, vector<int>, greater<int>> minHeap;
		int ret = 0;
		for (int i = 1; i <= N; i++) {
			ret += findMedian(maxHeap, minHeap, r.next());
			ret %= MOD;
		}
		cout << ret << "\n";
	}
}