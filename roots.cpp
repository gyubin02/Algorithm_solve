//���� ID : ROOTS
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
vector<double> search(vector<double>& poly);
double evaluate(vector<double>& poly, double x);
vector<double> differentiate(vector<double>& poly);
vector<double> solveNaive(vector<double>& poly);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int C;
	cin >> C;
	while (C-- > 0) {
		int n;
		cin >> n;
		vector<double> poly(n+1);
		for (int i = 0; i < n + 1; i++)
			cin >> poly[i];
		vector<double> ret = search(poly);
		for (int i = 0; i < ret.size(); i++)
			cout << ret[i] << " ";
		cout << "\n";
	}
}

vector<double> search(vector<double>& poly) { //���� �������� ��� poly�� �־����� ��, �ظ� ������ vector ��ȯ
	int n = poly.size() - 1;
	//base
	if (n <= 2)
		return solveNaive(poly);
	//step
	vector<double> diff = differentiate(poly);
	vector<double> pole = search(diff);
	pole.insert(pole.begin(), -10);
	pole.insert(pole.end(), 10);
	vector<double> ret;
	for (int i = 0; i + 1 < pole.size(); i++) {
		double x1 = pole[i], x2 = pole[i + 1];
		double y1 = evaluate(poly, x1), y2 = evaluate(poly, x2);
		if (y1 * y2 > 0) continue;
		if (y1 > y2) swap(x1, x2); //f(x1) <= 0 < f(x2)
		for (int it = 0; it < 100; it++) {
			double mx = (x1 + x2) / 2;
			if (evaluate(poly, mx) > 0)
				x2 = mx;
			else
				x1 = mx;
		}
		ret.push_back((x1 + x2) / 2);
	}
	sort(ret.begin(), ret.end());
	return ret;
}

double evaluate(vector<double>& poly, double x) { //���� ������ f�� ��� poly�� x���� �־����� ��, f(x)�� ��ȯ
	int n = poly.size() - 1;
	double ret = 0;
	for (int i = 0; i <= n; i++)
		ret += poly[i] * pow(x, n - i);
	return ret;
}

vector<double> differentiate(vector<double>& poly) { //���� �������� ��� poly�� �־����� ��, ���Լ��� ����� ������ vector ��ȯ
	int n = poly.size() - 1;
	vector<double> ret;
	for (int i = 0; i < n; i++)
		ret.push_back(poly[i] * (n - i));
	return ret;
}

vector<double> solveNaive(vector<double>& poly) { //1�� �Ǵ� 2�� �������� ��� poly�� �־����� ��, �ظ� ������ vector ��ȯ 
	int n = poly.size() - 1;
	vector<double> ret;
	if (n == 2) {
		ret.push_back((-poly[1] - sqrt(pow(poly[1], 2) - 4 * poly[0] * poly[2])) / 2 * poly[0]);
		ret.push_back((-poly[1] + sqrt(pow(poly[1], 2) - 4 * poly[0] * poly[2])) / 2 * poly[0]);
	}
	else
		ret.push_back(-poly[1] / poly[0]);
	return ret;
}