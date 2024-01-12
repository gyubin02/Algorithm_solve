//문제 ID : DARPA
#include <iostream>
#include <vector>
using namespace std;
double select(int last, int cameras);

int N, M;
vector<double> locations;
double cache[201][101];
const double INF = 9999999;
const double NEGINF = -9999999;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int C;
	cin >> C;
	while (C-- > 0) {
		//initialize cache
		for (int i = 0; i < 201; i++)
			for (int j = 0; j < 101; j++)
				cache[i][j] = -1;
		cin >> N >> M;
		locations.resize(M);
		for (int i = 0; i < M; i++)
			cin >> locations[i];
		double ret = -1;
		for (int i = 0; i < M; i++)
			ret = max(ret, select(i, N));
		cout << ret << "\n";
	}
}

//마지막으로 카메라를 놓은 중계소의 번호 last와 앞으로 설치해야 할 카메라의 개수 cameras가 주어졌을 때,
//가장 가까운 두 카메라 간 거리가 최대가 되는 설치 방법을 찾는다
//최대값을 반환
double select(int last, int cameras) { 
	//base
	if (cameras == 0) return INF;
	if (last == M - 1) return NEGINF;
	//check memo
	double& ret = cache[last][cameras];
	if (ret != -1) return ret;
	//step
	for (int next = last + 1; next < N; next++) {
		double gap = locations[next] - locations[last];
		double cand = min(gap, select(next, cameras - 1));
		ret = max(ret, cand);
	}
	return ret;
}