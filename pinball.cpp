//문제 ID : PINBALL
#include <iostream>
#include <vector>
using namespace std;

const double EPSILON = 1e-9;

struct vector2 {
	double x, y;
	explicit vector2(double x_ = 0, double y_ = 0) :x(x_), y(y_) {}
	vector2 operator +(const vector2& rhs) {
		return vector2(x + rhs.x, y + rhs.y);
	}
	vector2 operator -(const vector2& rhs) {
		return vector2(x - rhs.x, y - rhs.y);
	}
	vector2 operator *(double rhs) {
		return vector2(x * rhs, y * rhs);
	}
	double norm() const {
		return hypot(x, y);
	}
	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}
	double dot(const vector2& rhs) {
		return x * rhs.x + y * rhs.y;
	}
	double cross(const vector2& rhs) {
		return x * rhs.y - y * rhs.x;
	}
	vector2 project(const vector2& rhs) {
		vector2 r = rhs.normalize();
		return r * dot(r);
	}
};
bool func(vector2 start, vector2 velo, vector2 o, double r, double& t);
vector2 func2(vector2 velo, vector2 o, vector2 col);
void solve(vector2 start, vector2 velo, int count, vector<int>& ret);

int n;
vector2 start, velo;
vector2 circle_o[51];
double circle_radius[51];

//공의 시작 위치 start, 공의 방향 velo, 원의 중심 위치 o, 반지름 r이 주어질 때, 충돌하는 지 여부를 반환 (충돌 시간을 t에 저장)
bool func(vector2 start, vector2 velo, vector2 o, double r, double& t) {
	double a = velo.dot(velo);
	double b = 2 * velo.dot(start - o);
	double c = start.dot(start) - 2 * start.dot(o) + o.dot(o);
	double d = b * b - 4 * a * c;

	if (d < -EPSILON) return false;
	if (d < EPSILON) {
		t = -b / (2 * a);
		return true;
	}
	t = (-b - sqrt(d)) / (2 * a);
	return true;
}

//공의 속도 velo, 원의 중심 위치 o, 충돌 위치 col이 주어질 때, 공의 충돌 후 방향을 반환
vector2 func2(vector2 velo, vector2 o, vector2 col) {
	vector2 p = (velo*-1).project(col - o);
	return velo + p * 2;
}

void solve(vector2 start, vector2 velo, int count, vector<int>& ret) {
	//base
	if (count > 10) return;
	//step
	double cand;
	double time = 1e7;
	int first = -1;
	for (int i = 0; i < n; i++)
		if (func(start, velo, circle_o[i], circle_radius[i], cand))
			if (time > cand) {
				time = cand;
				first = i;
			}
	if (first == -1) return;
	ret.push_back(first);
	vector2 next_start = start + velo * time;
	vector2 next_velo = func2(velo, circle_o[first], next_start);
	solve(next_start, next_velo, count + 1, ret);
}

int main() {
	int cases;
	cin >> cases;
	while (cases--) {
		double x, y, dx, dy;
		cin >> x >> y >> dx >> dy >> n;
		start = vector2(x, y);
		velo = vector2(dx, dy).normalize();
		double x_c, y_c, r;
		for (int i = 0; i < n; i++) {
			cin >> x_c >> y_c >> r;
			circle_o[i] = vector2(x_c, y_c);
			circle_radius[i] = r + 1;
		}
		vector<int> ret;
		solve(start, velo, 0, ret);
		for (int i = 0; i < ret.size(); i++)
			cout << ret[i] << " ";
		cout << "\n";
	}
}