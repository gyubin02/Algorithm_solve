//문제 ID : KLIS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int lis(int cur);
long long lis_count(int cur);
void reconstruct(int cur, int k, vector<int>& seq);

const int MAX_N = 500;
const long long MAX_K = 2500000000;
int n;
long long k;
int A[MAX_N], cache[MAX_N];
long long cache_cnt[MAX_N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	while (cases--) {
		for (int i = 0; i < MAX_N; i++)
			cache[i] = cache_cnt[i] = -1;
		cin >> n >> k;
		for (int i = 0; i < n; i++)
			cin >> A[i];
		int ret = 0;
		for (int i = 0; i < n; i++)
			ret = max(ret, lis(i));
		cout << ret << "\n";
		vector<int> seq;
		reconstruct(-1, k, seq);
		for (int i = 0; i < seq.size(); i++)
			cout << seq[i] << " ";
		cout << "\n";
	}
}

int lis(int cur) { //A[cur]을 시작으로 하는 lis의 길이를 반환
	//check memo
	int& ret = cache[cur];
	if (ret != -1) return ret;
	//step
	ret = 1;
	for (int next = cur + 1; next < n; next++)
		if(A[cur] < A[next]) ret = max(ret, lis(next) + 1);
	return ret;
}

long long lis_count(int cur) { //A[cur]을 시작으로 하는 lis의 개수를 반환
	//base
	if (lis(cur) == 1) return 1;
	//check memo
	long long& ret = cache_cnt[cur];
	if (ret != -1) return ret;
	//step
	ret = 0;
	for (int next = cur + 1; next < n; next++)
		if (A[cur] < A[next] && lis(cur) == lis(next) + 1)
			ret = min(ret + lis_count(next), MAX_K);
	return ret;
}

void reconstruct(int cur, int k, vector<int>& seq) { //A[cur]을 시작으로 하는 k 번째 seq를 반환
	if(cur != -1) seq.push_back(A[cur]);
	vector<pair<int, int>> f;
	for (int next = cur + 1; next < n; next++)
		if (cur == -1 || A[cur] < A[next] && lis(cur) == lis(next) + 1)
			f.push_back(make_pair(A[next], next));
	sort(f.begin(), f.end());

	for (int i = 0; i < f.size(); i++) {
		if (lis_count(f[i].second) < k)
			k -= lis_count(f[i].second);
		else {
			reconstruct(f[i].second, k, seq);
			break;
		}
	}
}