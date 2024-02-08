//¹®Á¦ ID : DICTIONARY
/*
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> res;
void makeDAG(vector<string>& words) {
	adj = vector<vector<int>>(26);
	for (int i = 1; i < words.size(); i++) {
		int j = i - 1;
		int length = min(words[j].size(), words[i].size());
		for(int s = 0; s<length; s++)
			if (words[j][s] != words[i][j]) {
				int f = words[j][s] - 'a';
				int e = words[i][s] - 'a';
				adj[f].push_back(e);
				break;
			}
	}
}

void dfs(int here) {
	visited[here] = true;
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];
		if (!visited[there])
			dfs(there);
	}
	res.push_back(here);
}

void top_sort() {
	visited = vector<bool>(adj.size(), false);
	for (int i = 0; i < adj.size(); i++) {
		if (!visited[i])
			dfs(i);
	}
	reverse(res.begin(), res.end());
	for (int i = 0; i < res.size(); i++)
		for (int j = i + 1; j < res.size(); j++)
			for(int k = 0; k<adj[res[j]].size(); k++)
				if (adj[res[j]][k] == res[i]) {
					res = vector<int>();
					return;
				}
}

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		int N;
		cin >> N;
		vector<string> words(N);
		for (int i = 0; i < N; i++)
			cin >> words[i];
		makeDAG(words);
		res.clear();
		top_sort();
		if (res.empty()) cout << "INVALID HYPOTHESIS";
		for (int i = 0; i < res.size(); i++)
			cout << char(res[i]+'a');
		cout << "\n";
	}
}
*/