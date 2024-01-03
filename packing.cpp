//문제 ID : PACKING
#include <iostream>
#include <vector>
using namespace std;
int packing(int cur, int capacity);
void reconstruct(int cur, int capacity, vector<string>& choice);

const int MAXN = 100;
const int MAXW = 1000;
int A[MAXN][2]; //A[i][0] == i번째 물건의 부피, A[i][1] == i번째 물건의 절박도
string name[MAXN]; //name[i] == i번째 물건의 이름
int cache[MAXN][MAXW];
int N, W;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		//cache 초기화
		for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < MAXW; j++)
				cache[i][j] = -1;
		vector<string> choice;
		cin >> N >> W;
		for (int i = 0; i < N; i++)
			cin >> name[i] >> A[i][0] >> A[i][1];
		cout << packing(0, W) << " ";
		reconstruct(0, W, choice);
		//선택한 물건 출력
		cout << choice.size() << "\n";
		for (int i = 0; i < choice.size(); i++)
			cout << choice[i] << "\n";
	}
}

//남은 용량이 capacity일 때, name[cur]의 우측 물건들(name[cur] 포함) 중 선택하는 경우의 최대 절박도 합을 반환
//예시) cur이 2라고 가정하면 name[2], name[3] , ... ,name[N-1]를 후보로 함
int packing(int cur, int capacity) { //부수 효과 : choices에 선택 저장
	//base
	if (capacity == 0) return 0;
	if (cur == N) return 0;
	//check memo
	int& ret = cache[cur][capacity];
	if (ret != -1) return ret;
	//step : 1)name[cur]을 선택하는 경우 2)name[cur]을 선택하지 않는 경우
	int cand_1 = 0, cand_2;
	if(capacity >= A[cur][0])
		cand_1 = packing(cur + 1, capacity - A[cur][0]) + A[cur][1];
	cand_2 = packing(cur + 1, capacity);
	
	ret = max(cand_1, cand_2);
	return ret;
}

void reconstruct(int cur, int capacity, vector<string>& choice) { //name[cur]을 선택했다면 choice에 push
	//base
	if (cur == N) return;
	//step
	if (packing(cur, capacity) == packing(cur + 1, capacity))
		reconstruct(cur + 1, capacity, choice);
	else {
		choice.push_back(name[cur]);
		reconstruct(cur + 1, capacity - A[cur][0], choice);
	}
}