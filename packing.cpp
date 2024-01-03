//���� ID : PACKING
#include <iostream>
#include <vector>
using namespace std;
int packing(int cur, int capacity);
void reconstruct(int cur, int capacity, vector<string>& choice);

const int MAXN = 100;
const int MAXW = 1000;
int A[MAXN][2]; //A[i][0] == i��° ������ ����, A[i][1] == i��° ������ ���ڵ�
string name[MAXN]; //name[i] == i��° ������ �̸�
int cache[MAXN][MAXW];
int N, W;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		//cache �ʱ�ȭ
		for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < MAXW; j++)
				cache[i][j] = -1;
		vector<string> choice;
		cin >> N >> W;
		for (int i = 0; i < N; i++)
			cin >> name[i] >> A[i][0] >> A[i][1];
		cout << packing(0, W) << " ";
		reconstruct(0, W, choice);
		//������ ���� ���
		cout << choice.size() << "\n";
		for (int i = 0; i < choice.size(); i++)
			cout << choice[i] << "\n";
	}
}

//���� �뷮�� capacity�� ��, name[cur]�� ���� ���ǵ�(name[cur] ����) �� �����ϴ� ����� �ִ� ���ڵ� ���� ��ȯ
//����) cur�� 2��� �����ϸ� name[2], name[3] , ... ,name[N-1]�� �ĺ��� ��
int packing(int cur, int capacity) { //�μ� ȿ�� : choices�� ���� ����
	//base
	if (capacity == 0) return 0;
	if (cur == N) return 0;
	//check memo
	int& ret = cache[cur][capacity];
	if (ret != -1) return ret;
	//step : 1)name[cur]�� �����ϴ� ��� 2)name[cur]�� �������� �ʴ� ���
	int cand_1 = 0, cand_2;
	if(capacity >= A[cur][0])
		cand_1 = packing(cur + 1, capacity - A[cur][0]) + A[cur][1];
	cand_2 = packing(cur + 1, capacity);
	
	ret = max(cand_1, cand_2);
	return ret;
}

void reconstruct(int cur, int capacity, vector<string>& choice) { //name[cur]�� �����ߴٸ� choice�� push
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