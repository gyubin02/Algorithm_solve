//문제 ID : FANMEETING
#include <iostream>
#include <vector>
using namespace std;
vector<int> multiply(vector<int>& members, vector<int>& fans);
int hugs(const string& m, const string& f);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases-- > 0) {
		string m, f;
		cin >> m >> f;

		cout << hugs(m, f) << "\n";
	}
}

int hugs(const string& m, const string& f) {
	int N = m.size(); int M = f.size();
	vector<int> A(N); vector<int> B(M);
	for (int i = 0; i < N; i++) A[i] = (m[i] == 'M');
	for (int i = 0; i < M; i++) B[M-i-1] = (f[i] == 'M');

	vector<int> multi = multiply(A, B);
	int sum = 0;
	for (int i = N - 1; i < M; i++)
		if (!multi[i]) sum++;
	return sum;
}

vector<int> multiply(vector<int>& A, vector<int>& B) { //O(n^2) = 400억 = 시간초과
	int a = A.size(); int b = B.size();
	vector<int> multi(a + b + 1);
	for (int i = 0; i < b; i++) {
		for (int j = 0; j < a; j++) {
			multi[i + j] += A[j] * B[i];
		}
	}
	return multi;
}

//카라츠바 알고리즘 필요 O(n^log3) = 약 1억