//문제 ID : SOLONG
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int Alphabet = 26;
const int maxC = 250000;
int toNumber(char ch) {
	return ch - 'A';
}
struct Tri {
	Tri* children[Alphabet];
	bool terminal;
	int recommend;
	Tri() :terminal(false), recommend(-1) {
		for (int i = 0; i < Alphabet; i++)
			children[i] = 0;
	}
	~Tri() {
		for (int i = 0; i < Alphabet; i++)
			if (children[i])
				delete(children[i]);
	}
	void insert(const char* key, int id) {
		if (recommend == -1)
			recommend = id;
		if (*key == 0) {
			terminal = true;
			return;
		}
		int next = toNumber(*key);
		if (children[next] == NULL)
			children[next] = new Tri();
		children[next]->insert(key + 1, id);
	}
	Tri* find(const char* key) {
		if (*key == 0)
			return this;
		int next = toNumber(*key);
		if (children[next] == NULL)
			return NULL;
		return children[next]->find(key + 1);
	}
	int type(const char* key, int id) { //find(key) == true && find(key)->terminal == true라고 가정
		if (*key == 0) return 0;
		if (recommend == id) return 1;
		int next = toNumber(*key);
		return 1 + children[next]->type(key + 1, id);
	}
	int count(const char* key) {
		Tri* node = find(key);
		if (!node || !(node->terminal)) return strlen(key);
		return type(key, node->recommend);
	}
};

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		int N, M;
		cin >> N >> M;
		//단어 입력
		vector<pair<int, string>> input;
		for (int i = 0; i < N; i++) {
			char buf[11];
			int freq;
			scanf(" %s %d", buf, &freq);
			input.push_back(make_pair(-freq, buf));
			cin.ignore();
		}
		sort(input.begin(), input.end());
		Tri* t = new Tri();
		for (int i = 0; i < N; i++)
			t->insert(input[i].second.c_str(), i);
		t->recommend = -1;
		//문장 입력
		int ret = 0;
		char buf[maxC];
		scanf("%[^\n]", buf);
		char* ptr = strtok(buf, " ");
		while (ptr != NULL) {
			ret += t->count(ptr);
			ret += 1;
			ptr = strtok(NULL, " ");
		}
		ret -= 1;
		cout << ret << "\n";
	}
}