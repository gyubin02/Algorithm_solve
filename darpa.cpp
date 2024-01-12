//���� ID : DARPA
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

//�߰���� ��ġ locations�� ��ġ�Ϸ��� ī�޶��� �� cameras�� �־��� ��, ���� ����� �� ī�޶� �� �Ÿ��� gap �̻��� �ǵ��� ��ġ ������ �� ���θ� ��ȯ
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

//�߰���� ��ġ locations�� ��ġ�Ϸ��� ī�޶��� �� cameras�� �־��� ��, 
//ī�޶� ���� ����� �� ���� ����� �� ī�޶� �� �Ÿ��� �ִ밡 �Ǵ� ��츦 ã�´�.
//�ִ밪 ��ȯ
//decision(locations, cameras, gap)�� ��ȯ���� �ٲ�� gap�� ã�´�
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