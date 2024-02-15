//문제 ID : FIRETRUCKS
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int V = 1000;
const int INF = 9999999;
vector<vector<pair<int, int>>> adj(V); //(가중치, 정점 번호)
vector<int> dijk2(int s) {
	vector<int> dist(V, INF);
	priority_queue<pair<int, int>> pq; //(dist, 정점 번호)
	dist[s] = 0;
	pq.push(make_pair(0, s));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].second;
			int weight = adj[here][i].first;
			if (dist[there] > cost + weight) {
				dist[there] = cost + weight;
				pq.push(make_pair(-dist[there], there));
			}
		}
	}
	return dist;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int C;
	cin >> C;
	while (C-- > 0) {
		int v, e;
		cin >> v >> e;
		adj = vector<vector<pair<int, int>>>(v+1);
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < e; i++) {
			int a, b, t;
			cin >> a >> b >> t;
			a -= 1; b -= 1;
			adj[a].push_back(make_pair(t, b));
			adj[b].push_back(make_pair(t, a));
		}
		vector<int> city(n);
		for (int i = 0; i < n; i++) {
			cin >> city[i];
			city[i] -= 1;
		}
		while (m-- > 0) {
			int station;
			cin >> station;
			station -= 1;
			adj[v].push_back(make_pair(0, station));
		}
		vector<int> dist = dijk2(v);
		int sum = 0;
		for (int i = 0; i < city.size(); i++)
			sum += dist[city[i]];
		cout << sum << "\n";
	}
}