//문제 ID : DARPA
#include <iostream>
#include <vector>
using namespace std;
bool decision(vector<double>& locations, int cameras, int gap);
int optimization(vector<double>& locations, int cameras);

int N, M;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int C;
	cin >> C;
	while (C-- > 0) {
		cin >> N >> M;
		vector<double> locations(M);
		for (int i = 0; i < M; i++)
			cin >> locations[i];
		cout << optimization(locations, N) << "\n";
	}
}

//중계소의 위치 locations와 설치하려는 카메라의 수 cameras가 주어질 때, 가장 가까운 두 카메라 간 거리가 gap 이상이 되도록 설치 가능한 지 여부를 반환
bool decision(vector<double>& locations, int cameras, double gap) {  
	int installed = 0;
	double limit = -1;
	for (int i = 0; i < locations.size(); i++)
		if (limit <= locations[i]) {
			installed++;
			limit = locations[i] + gap;
		}
	return installed >= cameras;
}

//중계소의 위치 locations와 설치하려는 카메라의 수 cameras가 주어질 때, 
//카메라를 놓는 방법들 중 가장 가까운 두 카메라 간 거리가 최대가 되는 경우를 찾는다.
//최대값 반환
//decision(locations, cameras, gap)의 반환값이 바뀌는 gap을 찾는다
int optimization(vector<double>& locations, int cameras) {
	double lo = 0, hi = 241;
	for (int i = 0; i < 100; i++) {
		double mid = (lo + hi) / 2;
		if (decision(locations, cameras, mid))
			lo = mid;
		else
			hi = mid;
	}
	return lo;
}