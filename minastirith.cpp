//¹®Á¦ ID : MINASTIRITH
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
void convert();
int solveLinear(double begin, double end);

const double pi = 2.0 * acos(0);
double x[100], y[100], r[100];
int n;
pair<double, double> point[100];
const int INF = 999999999;

void convert() {
	for (int i = 0; i < n; i++) {
		int loc = fmod(2 * pi + atan2(y[i], x[i]), 2 * pi);
		int range = 2 * asin(r[i] / 16);
		point[i] = make_pair(loc - range, loc + range);
	}
	sort(point, point + n);
}

int solveLinear(double begin, double end) {
	int idx = 0, used = 0;
	while (begin < end) {
		double next_begin = -1;
		while (idx < n && point[idx].first < begin) {
			next_begin = max(next_begin, point[idx].second);
			idx++;
		}
		if (next_begin < begin)
			return INF;
		begin = next_begin;
		used++;
	}
	return used;
}