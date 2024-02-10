//¹®Á¦ ID : GALLERY
#include <iostream>
#include <vector>
using namespace std;

const int CAM = 0;
const int DOM = 1;
const int UNDOM = 2;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> camera;
int func(int here) {
	visited[here] = true;
	int children[3] = { 0,0,0 };
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];
		if (!visited[there])
			children[func(there)]++;
	}
	if (children[UNDOM]) {
		camera.push_back(here);
		return CAM;
	}
	if (children[CAM])
		return DOM;
	return UNDOM;
}

void start(int N) {
	visited = vector<bool>(N, false);
	camera = vector<int>();
	for (int i = 0; i < adj.size(); i++)
		if (!visited[i] && func(i) == UNDOM)
			camera.push_back(i);
	cout << camera.size() << "\n";
}

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		int g, h;
		cin >> g >> h;
		adj = vector<vector<int>>(g);
		for (int i = 0; i < h; i++) {
			int x, y;
			cin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		start(g);
	}
}