//���� ID : NUMB3RS
#include <iostream>
using namespace std;
double func(int days, int start, int end);
void precalc();

int A[50][50];
int F[50]; //F[i] = i�� ��忡 ������ ����� ����
int N, D, P, T;
double cache[100][50][50];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases-- > 0) {
		cin >> N >> D >> P;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> A[i][j];
		precalc();
		cin >> T;
		for (int i = 0; i < T; i++) {
			int node;
			cin >> node;
			cout << func(D, P, node) << " ";
		}
		cout << "\n";
	}
}

double func(int days, int start, int end) { //start���� �����ؼ� days���� ���� �� end�� ���� Ȯ���� ��ȯ�Ѵ�.
	//base
	if (days == 0) {
		if (start == end) return 1.0;
		return 0.0;
	}
	//check memo
	double& ret = cache[days][start][end];
	if (ret != -1) return ret;
	//no memo
	ret = 0;
	for (int next = 0; next < N; next++)
		if (A[start][next] == 1)
			ret += func(days - 1, next, end) / F[start]; //�� ��° ����(end)�� ������ �����Ƿ� �κ� �������� ���� ����
	return ret;
}

void precalc() {
	//cache �ʱ�ȭ
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 50; j++)
			for (int k = 0; k < 50; k++)
				cache[i][j][k] = -1;
	//F �ʱ�ȭ
	for (int i = 0; i < N; i++) F[i] = 0;
	//F ���
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (A[i][j] == 1) F[i] += 1;
}