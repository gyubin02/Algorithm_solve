//¹®Á¦ ID : TRAVERSAL
#include <iostream>
#include <vector>
using namespace std;
void GetPostOrder(vector<int> preOrder, vector<int> inOrder);
vector<int> slice(vector<int> v, int a, int b);

int main() {
	int C;
	cin >> C;
	while (C-- > 0) {
		int N;
		cin >> N;
		vector<int> preOrder(N), inOrder(N);
		for (int i = 0; i < N; i++)
			cin >> preOrder[i];
		for (int i = 0; i < N; i++)
			cin >> inOrder[i];
		GetPostOrder(preOrder, inOrder);
		cout << "\n";
	}
}

void GetPostOrder(vector<int> preOrder, vector<int> inOrder) {
	int n = preOrder.size();
	if (preOrder.empty()) return;
	int root = preOrder[0];
	int L = find(inOrder.begin(), inOrder.end(), root) - inOrder.begin();
	GetPostOrder(slice(preOrder, 1, L+1), slice(inOrder, 0, L));
	GetPostOrder(slice(preOrder, L+1, n), slice(inOrder, L+1, n));
	cout << root << " ";
}

vector<int> slice(vector<int> v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin() + b);
}