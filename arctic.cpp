//¹®Á¦ ID : ARCTIC
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

double dist[101][101];
int n;

bool decision(double d) {
	vector<bool> visited(n, false);
	visited[0] = true;
	queue<int> q;
	q.push(0);
	int seen = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		seen++;
		for(int there=0; there<n; there++)
			if (!visited[there] && dist[here][there] <= d) {
				visited[there] = true;
				q.push(there);
			}
	}
	return seen == n;
}

int optimize() {
	int lo = 0, hi = 1415;
	for (int it = 0; it < 100; it++) {
		int mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return (lo + hi) / 2;
}