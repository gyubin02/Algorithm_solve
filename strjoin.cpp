//���� ID : STRJOIN
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int concat(vector<int>& length);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		int n;
		cin >> n;
		vector<int> length(n);
		for (int i = 0; i < n; i++)
			cin >> length[i];
		cout << concat(length) << "\n";
	}
}

int concat(vector<int>& length) { //���ڿ��� ���̸� ������ ����Ʈ�� �־����� ��, ���ڿ��� ��ġ�� �ּ� ����� ��ȯ
	priority_queue<int> pq;
	for (int i = 0; i < length.size(); i++)
		pq.push(-length[i]);
	int ret = 0;
	while (pq.size() > 1) {
		int a = pq.top(); pq.pop();
		int b = pq.top(); pq.pop();
		pq.push(a + b);
		ret = ret - (a + b);
	}
	return ret;
}