//문제 ID : MATCHORDER
#include <iostream>
#include <vector>
#include <set>
using namespace std;
int order(vector<int>& korean, vector<int>& russian);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		int n;
		cin >> n;
		vector<int> korean(n);
		vector<int> russian(n);
		for (int i = 0; i < n; i++)
			cin >> korean[i];
		for (int i = 0; i < n; i++)
			cin >> russian[i];
		cout << order(korean, russian) << "\n";
	}
}

int order(vector<int>& korean, vector<int>& russian) { //한국 선수들과 러시아 선수들의 rating을 저장한 vector가 주어졌을 때, 최대 승수를 반환
	int wins = 0;
	multiset<int> bst(korean.begin(), korean.end());
	for (int rus = 0; rus < russian.size(); rus++) {
		if (*bst.rbegin() < russian[rus])
			bst.erase(bst.begin());
		else {
			bst.erase(bst.lower_bound(russian[rus]));
			wins++;
		}
	}
	return wins;
}