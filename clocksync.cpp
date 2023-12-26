//¹®Á¦ ID : CLOCKSYNC
#include <iostream>
using namespace std;
int func(int clock[16], int cur_switch);
void push(int clock[16], int cur_switch);

const int inf = 9999;
char switch_clock[10][17] = {
	"xxx.............",
	"...x...x.x.x....",
	"....x.....x...xx",
	"x...xxxx........",
	"......xxx.x.x...",
	"x.x...........xx",
	"...x..........xx",
	"....xx.x......xx",
	".xxxxx..........",
	"...xxx...x...x.."
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases-- > 0) {
		//
		int clock[16] = { 0 };
		//
		for (int i = 0; i < 16; i++) cin >> clock[i];
		int ret = func(clock, 0);
		if (ret == inf) cout << -1;
		else cout << ret;
		cout << "\n";
	}
}

int func(int clock[16], int cur_switch) {
	//base
	if (cur_switch == 10) {
		for (int i = 0; i < 16; i++) {
			if (clock[i] != 12) return inf;
		}
		return 0;
	}
	//step
	int ret = inf;
	for (int cnt = 0; cnt < 4; cnt++) {
		ret = min(ret, cnt + func(clock, cur_switch + 1));
		push(clock, cur_switch);
	}
	return ret;
}

void push(int clock[16], int cur_switch) {

	for (int clk = 0; clk < 16; clk++) {
		if (switch_clock[cur_switch][clk] == 'x') {
			clock[clk] += 3;
			if (clock[clk] == 15) clock[clk] = 3;
		}
	}
}