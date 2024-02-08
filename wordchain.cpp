//¹®Á¦ ID : WORDCHAIN
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<string> graph[26][26];
vector<int> indegree, outdegree;
void makeGraph(const vector<string>& words) {
	//initialize
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			graph[i][j].clear();
	indegree = vector<int>(26, 0);
	outdegree = vector<int>(26, 0);
	//make graph
	for (int i = 0; i < words.size(); i++) {
		int f = words[i][0] - 'a';
		int e = words[i][words[i].size() - 1] - 'a';
		adj[f][e]++;
		graph[f][e].push_back(words[i]);
		outdegree[f]++;
		indegree[e]++;
	}
}

bool checkEuler() {
	int start = 0, end = 0;
	for (int i = 0; i < 26; i++) {
		int a = indegree[i] - outdegree[i];
		if (a > 1 || a < -1) return false;
		if (a == 1) start++;
		if (a == -1) end++;
	}
	return (start == 1 && end == 1) || (start == 0 && end == 0);
}

void EulerCircuit(int here, vector<int>& res) {
	for (int there = 0; there < adj.size(); there++) {
		while (adj[here][there] > 0) {
			adj[here][there]--;
			EulerCircuit(there, res);
		}
	}
	res.push_back(here);
}

vector<int> startEuler() {
	vector<int> res;
	for (int i = 0; i < adj.size(); i++) {
		if (indegree[i] + 1 == outdegree[i]) {
			EulerCircuit(i, res);
			return res;
		}
	}
	for (int i = 0; i < adj.size(); i++)
		if (outdegree[i] > 0) {
			EulerCircuit(i, res);
			return res;
		}
}

void solve(const vector<string>& words) {
	makeGraph(words);
	if (!checkEuler()) {
		cout << "IMPOSSIBLE" << "\n";
		return;
	}
	vector<int> ret = startEuler();
	if (ret.size() - 1 != words.size()) {
		cout << "IMPOSSIBLE" << "\n";
		return;
	}
	reverse(ret.begin(), ret.end());
	string s = "";
	for (int i = 1; i < ret.size(); i++) {
		int a = ret[i], b = ret[i - 1];
		if (s.size()) s += " ";
		s += graph[b][a].back();
		graph[b][a].pop_back();
	}
	cout << s << "\n";
}

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		int n;
		cin >> n;
		vector<string> words(n);
		for (int i = 0; i < n; i++)
			cin >> words[i];
		solve(words);
	}
}