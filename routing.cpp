//문제 ID : ROUTING
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

const int INF = 99999;
const int V = 10000;
vector<vector<pair<double, int>>> adj;

double dijk2(int s, int e) {
	vector<double> dist(V, INF);
	priority_queue<pair<double, int>> pq; //(dist, 정점 번호)
	dist[s] = 0;
	pq.push(make_pair(0, s));
	while (!pq.empty()) {
		double cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (here == e) return dist[here];
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].second;
			double weight = adj[here][i].first;
			if (dist[there] > cost + weight) {
				dist[there] = cost + weight;
				pq.push(make_pair(-dist[there], there));
			}
		}
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t-- > 0) {
		int n, m;
		cin >> n >> m;
		adj = vector<vector<pair<double, int>>>(n);
		for (int i = 0; i < m; i++) {
			int a, b;
			double c;
			cin >> a >> b >> c;
			adj[a].push_back(make_pair(log10(c), b));
			adj[b].push_back(make_pair(log10(c), a));
		}
		cout << fixed;
		cout.precision(10);
		cout << pow(10, dijk2(0, n - 1)) << "\n";
	}
}