//���� ID : PICNIC
#include <iostream>
using namespace std;
int func(bool areFriends[10][10], bool taken[10], int n);
int func_wrong(bool areFriends[10][10], bool taken[10], int n);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;

	cin >> cases;
	while (cases-- > 0) {
		//�ʱ�ȭ
		int n = 0; //n �ʱ�ȭ
		int pairs = 0; //pairs �ʱ�ȭ
		int arr[90] = { 0 }; //arr �ʱ�ȭ, pairs�� �ִ밪�� 45�̹Ƿ� arr�� 90ĭ�Դϴ�.
		bool areFreinds[10][10] = { false };
		bool taken[10] = { false };
		//
		cin >> n >> pairs;
		for (int i = 0; i < 2 * pairs; i++) cin >> arr[i];
		for (int i = 0; i < pairs; i++) {
			int x = i * 2;
			int hanni = arr[x];
			int minji = arr[x + 1];
			areFreinds[hanni][minji] = areFreinds[minji][hanni] = true;
		}
		cout << func(areFreinds, taken, n) << "\n";
	}
	return 0;
}

int func(bool areFriends[10][10], bool taken[10], int n) {
	//base case
	int first = -1;
	for (int i = 0; i < n; i++) {
		if (!taken[i]) {
			first = i;
			break;
		}
	}
	if (first == -1) return 1;

	//step
	int sum = 0;
	for (int i = first + 1; i < n; i++) {
		if (!taken[i] && areFriends[i][first]) {
			taken[first] = taken[i] = true;
			sum += func(areFriends, taken, n);
			taken[first] = taken[i] = false;
		}
	}
	return sum;
}

int func_wrong(bool areFriends[10][10], bool taken[10], int n) {
	//base case
	bool finished = true;
	for (int i = 0; i < n; i++) {
		if (!taken[i]) finished = false;
	}
	if (finished) return 1;

	//step
	int sum = 0;
	for (int i = 0; i < n; i++) { //�ٸ� ������ ¦���� �ִ� ��찡 �ߺ��˴ϴ�.
		for (int j = i + 1; j < n; j++) {
			if (!taken[i] && !taken[j] && areFriends[i][j]) {
				taken[i] = taken[j] = true;
				sum += func(areFriends, taken, n);
				taken[i] = taken[j] = false;
			}
		}
	}
	return sum;
}