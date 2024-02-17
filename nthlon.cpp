//문제 ID : NTHLON
#include <iostream>
#include <vector>
using namespace std;

const int V = 399; // -199 => 0 // 0 => 199 // 199 => 398
vector<vector<pair<int, int>>> adj; //(Ai, 정점 번호)
void makeGraph(vector<int>& A, vector<int>& B) {
	int m = A.size();
	vector<int> C(m);
	for (int i = 0; i < m; i++)
		C[i] = A[i] - B[i];
	adj = vector<vector<pair<int, int>>>(V+1);
	
	for (int here = 0; here < V; here++)
		for (int i = 0; i < m; i++) {
			int there = here + C[i];
			if (there > V - 1 || there < 0) 
				continue;
			if (there == 199)
				there = V;

			adj[here].push_back(make_pair(A[i], there));
		}
}

bool checkPos(vector<int>& A, vector<int>& B) {
	vector<int> pn = { 0, 0 };
	for (int i = 0; i < A.size(); i++) {
		int c = A[i] - B[i];
		if (c == 0) return true;
		if (c > 0) pn[0]++;
		else pn[1]++;
	}
	return (pn[0] * pn[1] != 0);
}

const int INF = 999999;
vector<int> dijk(int s) {
	vector<int> dist(V + 1, INF);
	vector<int> visited(V + 1, false);
	dist[s] = 0;
	while (true) {
		int closest = INF, here;
		for (int i = 0; i < V + 1; i++)
			if (!visited[i] && closest > dist[i]) {
				closest = dist[i];
				here = i;
			}
		if (closest == INF) return dist;
		visited[here] = true;
		for (int i = 0; i < adj[here].size(); i++) {
			int weight = adj[here][i].first;
			int there = adj[here][i].second;
			if (!visited[there] && dist[here] + weight < dist[there])
				dist[there] = dist[here] + weight;
		}
	}
}

int solve(vector<int>& A, vector<int>& B) {
	if (!checkPos(A, B)) return -1;
	makeGraph(A, B);
	vector<int> dist = dijk(199);
	return dist[V];
}

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		int M;
		cin >> M;
		vector<int> A(M), B(M);
		for (int i = 0; i < M; i++)
			cin >> A[i] >> B[i];
		int result = solve(A, B);
		if (result == -1) cout << "IMPOSSIBLE" << "\n";
		else cout << result << "\n";
	}
}