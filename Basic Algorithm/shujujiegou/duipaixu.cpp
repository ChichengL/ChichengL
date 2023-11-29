#include <iostream>
using namespace std;

const int N = 100010;

int n, m, h[N], s;
void down(int x) {
	int t = x;
	if (x * 2 <= s && h[x * 2] < h[t])
		t = x * 2;
	if (x * 2+1 <= s && h[x * 2 + 1] < h[t])
		t = x * 2 + 1;
	if (x != t) {
		swap(h[x], h[t]);
		down(t);
	}
}
void up(int x)
{
  while(u/2&&h[u/2]>h[u]){
    swap(h[u/2],h[u]);
    u=u/2;
  }
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &h[i]);
	s = n;

	for (int i = n / 2; i; i--)
		down(i);

	while (m--) {
		printf("%d ", h[1]);
		h[1] = h[s--];
		down(1);
	}
	return 0;
}