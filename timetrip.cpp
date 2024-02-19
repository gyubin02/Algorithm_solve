//문제 ID : TIMETRIP
#include <iostream>
#include <vector>
using namespace std;

const int INF = 30000000;
const int M = 20000000;
int V, t;
vector<int> bellman(int s, vector<vector<pair<int, int>>>& adj, bool& hasCy) {
	vector<int> upper(V, INF);
	upper[s] = 0;
	bool isRelaxed;
	for (int i = 0; i < V; i++) {
		isRelaxed = false;
		for(int here = 0; here<V; here++)
			for (int e = 0; e < adj[here].size(); e++) {
				int there = adj[here][e].second;
				int weight = adj[here][e].first;
				if (upper[there] > upper[here] + weight) {
					upper[there] = upper[here] + weight;
					isRelaxed = true;
					t = there;
				}
			}
		if (!isRelaxed) break;
	}
	if (isRelaxed) hasCy = true;
	return upper;
}

void dfs(vector<vector<pair<int, int>>>& adj, vector<int>& visited, int s) {
	visited[s] = true;
	for (int i = 0; i < adj[s].size(); i++) {
		int there = adj[s][i].second;
		if (!visited[there])
			dfs(adj, visited, there);
	}
}

int main() {
	int c;
	cin >> c;
	while (c-- > 0) {
		int w;
		cin >> V >> w;
		vector<vector<pair<int, int>>> adj(V), adjNeg(V);
		for (int i = 0; i < w; i++) {
			int a, b, d;
			cin >> a >> b >> d;
			adj[a].push_back(make_pair(d, b));
			adjNeg[a].push_back(make_pair(-d, b));
		}
		bool hasCy1 = false, hasCy2 = false;
		vector<int> minDist = bellman(0, adj, hasCy1);
		int past = t; //첫 번째 벨만 포드에서 마지막으로 완화된 정점의 번호
		vector<int> maxDist = bellman(0, adjNeg, hasCy2);
		int future = t;
		bool pastInfinite = false, futureInfinite = false, isUnreachable = false;
		if (minDist[1] > M) isUnreachable = true;
		if (hasCy1) { //첫 번째 그래프에 음수 사이클이 존재하는 경우
			vector<int> visited(V, false); //s에서 시작하는 경로가 존재하는 지 여부
			vector<int> visited2(V, false); //past에서 시작하는 경로가 존재하는 지 여부
			dfs(adj, visited, 0);
			dfs(adj, visited2, past);
			if (visited[past] && visited2[1])
				pastInfinite = true;
		}
		if (hasCy2) { //두 번째 그래프에 음수 사이클이 존재하는 경우
			vector<int> visited(V, false); //s에서 시작하는 경로가 존재하는 지 여부
			vector<int> visited2(V, false); //future에서 시작하는 경로가 존재하는 지 여부
			dfs(adjNeg, visited, 0);
			dfs(adjNeg, visited2, future);
			if (visited[future] && visited2[1])
				futureInfinite = true;
		}
		if (isUnreachable) {
			cout << "UNREACHABLE" << "\n";
			continue;
		}
		else {
			if (pastInfinite) cout << "INFINITY" << " ";
			else cout << minDist[1] << " ";
			if (futureInfinite) cout << "INFINITY" << "\n";
			else cout << -maxDist[1] << "\n";
		}
	}
	
}
