//문제 ID : GRADUATION
#include <iostream>
#include <vector>
using namespace std;
int brute(int semester, int mask, int count);
int dynamic(int semester, int mask);

int N, K, M, L, mask;
vector<vector<int>> pre, sem;
int cache[50][2 ^ 12];

int main() {
	int cases;
	cin >> cases;
	while (cases-- > 0) {
		//cache 초기화
		for (int i = 0; i < 50; i++)
			for (int j = 0; j < (2 ^ 12); j++)
				cache[i][j] = -1;

		cin >> N >> K >> M >> L;
		pre.resize(N); sem.resize(M);
		//pre 입력
		for (int i = 0; i < N; i++) {
			int R; cin >> R;
			for (int j = 0; j < R; j++) {
				int num; cin >> num;
				pre[i].push_back(num);
			}
		}
		//sem 입력
		for (int i = 0; i < M; i++) {
			int C; cin >> C;
			for (int j = 0; j < C; j++) {
				int num; cin >> num;
				sem[i].push_back(num);
			}
		}

		int ret = dynamic(0, 0);
		if (ret > M) cout << "IMPOSSIBLE" << "\n";
		else cout << ret << "\n";
	}
}

int brute(int semester, int mask, int count) {
	//base
	if (mask == (1 << N) - 1) return count;
	if (semester >= M) return -1;
	//step
	bool registered = false;
	int willRegister = 0;
	for (int sub = 0; sub < sem[semester].size(); sub++) {
		int subject = sem[semester][sub]; //후보
		if (mask & (1 << subject)) continue; //이미 수강했다면 continue
		bool isEligible = true;
		for (int psub = 0; psub < pre[subject].size(); psub++)
			if ((mask & (1 << pre[subject][psub])) == false) isEligible = false;
		if (!isEligible) continue; //수강하지 못하는 과목이라면 continue
		willRegister |= (1 << subject);
		registered = true;
	}
	if (registered) count++;
	return brute(semester + 1, mask|willRegister, count);
}

int dynamic(int semester, int mask) { //앞으로 최소 몇 학기만에 졸업 가능한지 반환
	//base
	if (semester >= M) {
		if (mask != (1 << N) - 1) return 999;
		else return 0;
	}
	//check memo
	int& ret = cache[semester][mask];
	if (ret != -1) return ret;
	//step
	bool registered = false;
	int willRegister = 0;
	for (int sub = 0; sub < sem[semester].size(); sub++) {
		int subject = sem[semester][sub]; //후보
		if (mask & (1 << subject)) continue; //이미 수강했다면 continue
		bool isEligible = true;
		for (int psub = 0; psub < pre[subject].size(); psub++)
			if ((mask & (1 << pre[subject][psub])) == false) isEligible = false;
		if (!isEligible) continue; //수강하지 못하는 과목이라면 continue
		willRegister |= (1 << subject);
		registered = true;
	}
	if (registered) return ret = 1 + dynamic(semester + 1, mask | willRegister);
	return ret = dynamic(semester + 1, mask);
}