//문제 ID : SNAIL
#include <iostream>
using namespace std;
double func(int days, int sum);

const int MAX_DAYS = 1000;
int n, m; //우물의 깊이 : n , 장마 기간 : m
double cache[MAX_DAYS][MAX_DAYS * 2];

int main() {
	int cases;
	cin >> cases;
	while (cases--) {
		for (int i = 0; i < MAX_DAYS; i++)
			for (int j = 0; j < MAX_DAYS * 2; j++)
				cache[i][j] = -1.0;

		cin >> n >> m;
		cout << func(m, 0) << "\n";
	}
}

double func(int days, int sum) { //days일 동안 높이 n-sum 이상 올라갈 확률
	//base
	if (days == 0) return (sum >= n ? 1.0 : 0.0);
	//check memo
	double& ret = cache[days][sum];
	if (ret != -1.0) return ret;
	//no memo
	return ret = 0, 25 * func(days - 1, sum + 1) + 0.75 * func(days - 1, sum + 2);
}

