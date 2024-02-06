//¹®Á¦ ID : NH
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int cache[1100][110];
int nu = 0;
const int Alphabet = 26;
int toNumber(const char ch) {
	return ch - 'a';
}
struct Tri {
	int terminal, number;
	Tri* children[Alphabet];
	Tri* fail;
	vector<int> output;
	Tri() :terminal(-1),number(nu++), fail(NULL) {
		for (int i = 0; i < Alphabet; i++)
			children[i] = 0;
	}
	~Tri() {
		for (int i = 0; i < Alphabet; i++)
			if (children[i])
				delete(children[i]);
	}
	void insert(const char* key, int id) {
		if (*key == 0) {
			terminal = id;
			return;
		}
		int next = toNumber(*key);
		if (children[next] == NULL)
			children[next] = new Tri();
		children[next]->insert(key + 1, id);
	}
	Tri* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == NULL)
			return NULL;
		return children[next]->find(key + 1);
	}
};

void computeFail(Tri* root) {
	queue<Tri*> q;
	root->fail = root;
	q.push(root);
	while (!q.empty()) {
		Tri* here = q.front();
		q.pop();
		for (int i = 0; i < Alphabet; i++) {
			Tri* child = here->children[i];
			if (!child) continue;
			Tri* t = here->fail;
			while (t != root && t->children[i] == NULL)
				t = t->fail;
			if (t->children[i]) t = t->children[i];
			child->fail = t;

			child->output = child->fail->output;
			if (child->terminal != -1)
				child->output.push_back(child->terminal);
			q.push(child);
		}
	}
}

vector<pair<int, int>> ahoCorasick(const string& str, Tri* root) {
	vector<pair<int, int>> ret;
	Tri* state = root;
	for (int i = 0; i < str.size(); i++) {
		int num = toNumber(str[i]);
		while (state != root && state->children[num] == NULL)
			state = state->fail;
		if (state->children[num])
			state = state->children[num];
		for (int j = 0; j < state->output.size(); j++)
			ret.push_back(make_pair(i, state->output[j]));
	}
	return ret;
}

int func(Tri* node, int L) {
	//base
	if (node->terminal != -1) return 0;
	if (L == 0) return 1;
	//check memo
	int& ret = cache[node->number][L];
	if (ret != -1) return ret;
	//no memo
	ret = 0;
	for (int i = 0; i < Alphabet; i++) {
		Tri* state = node;
		while (state != state->fail && state->children[i] == NULL)
			state = state->fail;
		if (state->children[i]) state = state->children[i];
		ret += func(state, L - 1);
		ret %= 10007;
	}
	return ret;
}

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		for (int i = 0; i < 1100; i++)
			for (int j = 0; j < 110; j++)
				cache[i][j] = -1;
		int N, M;
		cin >> N >> M;
		Tri* root = new Tri();
		for (int i = 0; i < M; i++) {
			char buf[11];
			cin.ignore();
			scanf("%s", buf);
			root->insert(buf, i);
		}
		computeFail(root);
		cout << func(root, N) << "\n";
		delete(root);
	}
}