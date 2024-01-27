//문제 ID : FORTRESS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
	vector<TreeNode*> children;
};
int height(TreeNode* root);
bool Enclose(int a, int b);
bool isParent(int a, int b);
TreeNode* getTree(int root);

int longest = 0 ,N;
vector<int> x, y, r;

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		cin >> N;
		x.resize(N); y.resize(N); r.resize(N);
		for (int i = 0; i < N; i++)
			cin >> x[i] >> y[i] >> r[i];
		TreeNode* root = getTree(0);
		int ret = height(root);
		ret = max(ret, longest);
		cout << ret << "\n";
	}
}

int height(TreeNode* root) { //longest에 잎-잎 노드의 최장 경로 길이 저장,잎-루트 반환
	vector<int> v;
	for (int i = 0; i < root->children.size(); i++)
		v.push_back(1 + height(root->children[i]));
	sort(v.begin(), v.end());
	if (v.empty()) return 0;
	if (v.size() >= 2) longest = max(longest, v[v.size()-1] + v[v.size()-2]);
	return v.back();
}

//a가 b를 포함하는가?
bool Enclose(int a, int b) {
	return (r[a] > r[b]) &&
		((r[a] + r[b]) * (r[a] + r[b]) > (x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
}

//a가 b의 부모인가?
bool isParent(int a, int b) {
	if (!Enclose(a, b)) return false;
	for (int wall = 0; wall < N; wall++)
		if (wall != a && wall != b && Enclose(a, wall) && Enclose(wall, b))
			return false;
	return true;
}

TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();
	for (int wall = 0; wall < N; wall++)
		if (isParent(root, wall))
			ret->children.push_back(getTree(wall));
	return ret;
}