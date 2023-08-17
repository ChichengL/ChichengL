#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1e4 + 10;
int h[N], e[N], w[N], ne[N], idx, C[N];
int t[N];
int n, m;
typedef pair<int, int> PII;
bool st[N];

void add(int a, int b, int c) {
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}

int dijkstra() {
	memset(t, 0x3f, sizeof t);
	t[1] = 0;

	priority_queue<PII, vector<PII>, greater<PII>>q;
	q.push({0, 1});
	while (q.size()) {
		auto p = q.top();
		q.pop();

		int ver = p.second;
		if (st[ver])
			continue;
		st[ver] = true;
		for (int i = h[ver]; i != -1; i = ne[i]) {
			int j = e[i];
			if (t[j] > t[ver] + w[i] ) {
				t[j] = t[ver] + w[i];
				q.push({t[j], j});
			}
		}
	}
	return t[n];
}

int main() {
	cin >> n >> m;
	memset(h, -1, sizeof h);
	for (int i = 1; i <= n; i ++)
		scanf("%d", &C[i]);
	while (m--) {
		int u, v, c;
		cin >> u >> v >> c;
		add(u, v, c+C[v]), add(v, u, c+C[u]);
	}
	int t = dijkstra() - C[n];
	cout << t;
}
