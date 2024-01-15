//문제 ID : FOSSIL
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct point {
	double x, y;
};

double minX(const vector<point>& hull);
double maxX(const vector<point>& hull);
double search(const vector<point>& hull1, const vector<point>& hull2);
void decompose(const vector<point>& hull);
double vertical(double x);
bool between(point& a, point& b, double x0);
double evaluate(point& p1, point& p2, double x);

vector<pair<point, point>> upper, lower;

int main() {
	int C;
	cin >> C;
	while (C--) {
		int n, m;
		cin >> n >> m;
		vector<point> hull1(n), hull2(m);
		for (int i = 0; i < n; i++)
			cin >> hull1[i].x >> hull1[i].y;
		for (int i = 0; i < m; i++)
			cin >> hull2[i].x >> hull2[i].y;
		decompose(hull1); decompose(hull2);
		cout << search(hull1, hull2) << "\n";
	}
}

double minX(const vector<point>& hull) { //convex hull의 가장 왼쪽 점의 x 값을 반환한다.
	int n = hull.size();
	double ret = 1e20;
	for (int i = 0; i < n; i++)
		ret = min(ret, hull[i].x);
	return ret;
}

double maxX(const vector<point>& hull) { //convex hull의 가장 오른쪽 점의 x 값을 반환한다.
	int n = hull.size();
	double ret = -1e20;
	for (int i = 0; i < n; i++)
		ret = max(ret, hull[i].x);
	return ret;
}

double search(const vector<point>& hull1, const vector<point>& hull2) { //유니모달 함수의 지역 극대값을 반환한다.
	double lo = max(minX(hull1), minX(hull2));
	double hi = min(maxX(hull1), maxX(hull2));
	if (lo > hi) return 0;
	for (int it = 0; it < 100; it++) {
		double aab = (2 * lo + hi) / 3;
		double abb = (lo + 2 * hi) / 3;
		if (vertical(aab) >= vertical(abb))
			hi = abb;
		else if (vertical(aab) <= vertical(abb))
			lo = aab;
	}
	return max(0.0, vertical((lo + hi) / 2));
}

void decompose(const vector<point>& hull) { //다각형의 위 껍질 선분과 아래 껍질 선분을 각각 upper와 lower에 저장한다.
	int n = hull.size();
	for (int i = 0; i < n; i++) {
		if (hull[i].x > hull[(i + 1) % n].x)
			upper.push_back(make_pair(hull[(i + 1) % n], hull[i]));
		else if (hull[i].x < hull[(i + 1) % n].x)
			lower.push_back(make_pair(hull[i], hull[(i + 1) % n]));
	}
}

double vertical(double x) { //유니모달 함수
	double minUpper = 1e20, maxLower = -1e20;
	for (int i = 0; i < upper.size(); i++)
		if (between(upper[i].first, upper[i].second, x))
			minUpper = min(minUpper, evaluate(upper[i].first, upper[i].second, x));
	for (int i = 0; i < lower.size(); i++)
		if (between(lower[i].first, lower[i].second, x))
			maxLower = max(maxLower, evaluate(lower[i].first, lower[i].second, x));
	return minUpper - maxLower;
}

bool between(point& a, point& b, double x0) { //점 a와 b를 잇는 선분과 수직선 x=x0 가 교차하는지 여부를 반환
	return a.x <= x0 && x0 <= b.x;
}

double evaluate(point& p1, point& p2, double x) { //점 p1과 p2를 잇는 선형 함수 f에 대해 f(x)의 값을 반환한다.
	double dx = p1.x - p2.x;
	double dy = p1.y - p2.y;
	return (dx / dy) * (x - p1.x) + p1.y;
}