#include <iostream>

using namespace std;

void solve() {
	long long  a, b, n, m;
	long long res = 0;
	cin >> a >> b >> n >> m;
	if (n > m && a * m < b * (m + 1)) {
		res += a * (n / (m + 1)) * m;
		n -= (m + 1) * (n / (m + 1));
	}
	if (n)
		if (a < b)
			res += a * n;
		else
			res += b * n;
	cout << res << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--)
		solve();
}