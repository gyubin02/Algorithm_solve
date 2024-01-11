//¹®Á¦ ID : ALLERGY
#include <iostream>
#include <vector>
#include <map>
using namespace std;
void search(int food, int canEat, int chosen);
int solve();

const int MAX_FRIEND = 20;
const int MAX_FOOD = 20;
const int INF = 99999999;
bool table[MAX_FRIEND][MAX_FOOD];
int best, m, n;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
}

void search(int food, int canEat, int chosen) {
	//pruning
	if (chosen >= best) return;
	//base
	if (canEat == (1 << n) - 1) {
		best = min(best, chosen);
		return;
	}
	if (food == m) {
		best = min(best, INF);
		return;
	}
	//step
	int who = 0;
	for (int fri = 0; fri < n; fri++) {
		if (table[fri][food])
			who += 1;
		who = who << 1;
	}
	search(food + 1, canEat | who, chosen + 1);
	search(food + 1, canEat, chosen);
}

void better_search(int canEat, int chosen) {
	//pruning
	if (chosen >= best) return;
	//base
	if (canEat = (1 << n) - 1) {
		best = min(best, chosen);
		return;
	}
	//step
	//find first friend who can't eat any food
	int first = 0;
	for (int fri = 0; fri < n; fri++) {
		if (canEat & (1 << n - 1 - fri))
			continue;
		first = fri;
		break;
	}
	//search
	for (int food = 0; food < m; food++) {
		if (!table[first][food])
			continue;
		//find people who can eat this food
		int who = 0;
		for (int fri = 0; fri < n; fri++) {
			if (table[fri][food])
				who += 1;
			who = who << 1;
		}
		better_search(canEat | who, chosen + 1);
	}

}

int solve() {
	best = INF;
	better_search(0 << (n - 1), 0);
	return best;
}
