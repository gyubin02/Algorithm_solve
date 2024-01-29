//문제 ID : INSERTION
#include <iostream>
#include <vector>
using namespace std;

typedef int keyType;
struct Node {
	keyType key;
	int priority, size;
	Node* left, * right;
	Node(keyType& _key) :key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}
	void setLeft(Node* node) { left = node; calcSize(); }
	void setRight(Node* node) { right = node; calcSize(); }
	void calcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};

typedef pair<Node*, Node*> NodePair;

NodePair split(Node* root, keyType key) {
	//base
	if (root == NULL) return NodePair(NULL, NULL);
	//step
	if (root->key < key) {
		NodePair r = split(root->right, key);
		root->setRight(r.first);
		return NodePair(root, r.second);
	}
	NodePair l = split(root->left, key);
	root->setLeft(l.second);
	return NodePair(l.first, root);
}

Node* insert(Node* root, Node* node) {
	//base
	if (root == NULL) return node;
	//step
	if (root->priority > node->priority) {
		if (root->key > node->key)
			root->setLeft(insert(root->left, node));
		else
			root->setRight(insert(root->right, node));
		return root;
	}
	NodePair sub = split(root, node->key);
	node->setLeft(sub.first);
	node->setRight(sub.second);
	return node;
}

Node* merge(Node* L, Node* R) { //L->key < R->key 라고 가정
	//base
	if (L == NULL) return R;
	if (R == NULL) return L;
	//step
	if (L->priority > R->priority) {
		L->setRight(merge(L->right, R));
		return L;
	}
	R->setLeft(merge(L, R->left));
	return R;
}

Node* erase(Node* root, keyType key) { //root를 루트로 하는 트립에서 key를 지운 결과 트립의 루트를 반환한다.
	if (root == NULL) return NULL;
	if (root->key == key) {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if (root->key < key)
		root->setRight(erase(root->right, key));
	else
		root->setLeft(erase(root->left, key));
	return root;
}

Node* findK(Node* root, int k) { //root를 루트로 하는 트립의 노드들을 key의 오름차순으로 정렬했을 때 k 번째 노드를 반환한다.
	int L = 0;
	if (root->left != NULL)
		L = root->left->size;
	if (k <= L) return findK(root->left, k);
	if (k == L + 1) return root;
	return findK(root->right, k - L - 1);
}

int countLessThan(Node* root, int x) { //root를 루트로 하는 트립에서 key 값이 x보다 작은 노드의 개수를 반환한다.
	if (root == NULL) return 0;
	if (root->key >= x)
		return countLessThan(root->left, x);
	int a = root->left ? root->left->size : 0;
	return a + 1 + countLessThan(root->right, x);
}

Node* find(Node* root, int x) { //root를 루트로 하는 트립에서 key 값이 x인 노드를 반환한다.
	if (root == NULL) return NULL;
	if (root->key == x) return root;
	if (root->key < x) return find(root->right, x);
	return find(root->left, x);
}

vector<int> solve(vector<int>& arr, Node* root) {
	vector<int> ret(arr.size());
	for (int i = arr.size() - 1; i >= 0; i--) {
		int a = findK(root, root->size - arr[i])->key;
		ret[i] = a;
		root = erase(root, a);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int C;
	cin >> C;
	while (C-- > 0) {
		int N;
		cin >> N;
		Node* tree = NULL;
		for (int i = 1; i <= N; i++)
			tree = insert(tree, new Node(i));
		vector<int> arr(N);
		for (int i = 0; i < N; i++)
			cin >> arr[i];
		vector<int> ret = solve(arr, tree);
		for (int i = 0; i < N; i++)
			cout << ret[i] << " ";
		cout << "\n";
	}
}