//문제 ID : NERDS
#include <iostream>
#include <vector>
using namespace std;

struct vector2 {
	double x, y;
	explicit vector2(double x_ = 0, double y_ = 0) :x(x_), y(y_) {}
	bool operator ==(const vector2& rhs) {
		return x == rhs.x && y == rhs.y;
	}
	bool operator <(const vector2& rhs) {
		return (x != rhs.x) ? x < rhs.x : y < rhs.y;
	}
	vector2 operator -(const vector2& rhs) {
		return vector2(x - rhs.x, y - rhs.y);
	}
	double norm() const{
		return sqrt(x * x + y * y);
	}
	double cross(const vector2& rhs) {
		return x * rhs.y - y * rhs.x;
	}
};
bool solve();
double ccw(vector2 a, vector2 b);
double ccw(vector2 a, vector2 b, vector2 c);
vector<vector2> wrap(vector<vector2>& poly);
bool isIntersect(vector2 a, vector2 b, vector2 c, vector2 d);
bool isInside(vector2 p, vector<vector2>& poly);
bool isPolyIntersect(vector<vector2>& polyA, vector<vector2>& polyB);

vector<vector2> nerd, no_nerd;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int C;
	cin >> C;
	while (C-- > 0) {
		nerd.clear(); no_nerd.clear();
		int N;
		cin >> N;
		for (int i = 0; i < N; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			if (a == 1)
				nerd.push_back(vector2(b, c));
			else
				no_nerd.push_back(vector2(b, c));
			bool ret = solve();
			if (ret) cout << "THEORY HOLDS";
			else cout << "THEORY IS INVALID";
			cout << "\n";
		}
	}
}

bool solve() {
	vector<vector2> polyA = wrap(nerd);
	vector<vector2> polyB = wrap(no_nerd);
	return !isPolyIntersect(polyA, polyB);
}

double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}

double ccw(vector2 a, vector2 b, vector2 c) {
	return ccw(b - a, c - a);
}

vector<vector2> wrap(vector<vector2>& poly) { //gift wrapping 알고리즘
	vector<vector2> convex_hull;
	vector2 last = *min_element(poly.begin(), poly.end());
	convex_hull.push_back(last);
	while (true) {
		last = convex_hull.back();
		vector2 next = poly[0];
		for (int i = 1; i < poly.size(); i++) {
			double cc = ccw(last, next, poly[i]);
			double nn = (next - last).norm();
			double pp = (poly[i] - last).norm();
			if (cc > 0 || (cc == 0 && pp > nn))
				next = poly[i];
		}
		if (next == convex_hull.front())
			break;
		convex_hull.push_back(next);
	}
	return convex_hull;
}

bool isIntersect(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);

	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

bool isInside(vector2 p, vector<vector2>& poly) {
	int count = 0;
	int a = poly.size();
	for (int i = 0; i < a; i++) {
		int j = (i + 1) % a;
		if ((p.y > poly[i].y) != (p.y > poly[j].y)) {
			double atX = (p.y - poly[i].x) * (poly[i].x - poly[j].x) / (poly[i].y - poly[j].y) + poly[i].x;
			if (atX > p.x) count++;
		}
	}
	return count % 2 != 0;
}

bool isPolyIntersect(vector<vector2>& polyA, vector<vector2>& polyB) {
	int a = polyA.size();
	int b = polyB.size();
	if (isInside(polyA[0], polyB) || isInside(polyB[0], polyA))
		return true;
	for (int i = 0; i < a; i++)
		for (int j = 0; j < b; j++)
			if (isIntersect(polyA[i], polyA[(i + 1) % a], polyB[j], polyB[(j + 1) % b]))
				return true;
	return false;
}