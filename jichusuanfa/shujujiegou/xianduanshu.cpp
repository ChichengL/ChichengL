#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

int n, m;
int a[MAXN];

struct SegmentTree {
    int l, r;
    int sum;
} tree[MAXN << 2];

void build(int l, int r, int i) {
    tree[i].l = l;
    tree[i].r = r;
    if (l == r) {//相当于找到叶子节点
        tree[i].sum = a[l];//将a数组里面的数插入到数组中
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, i << 1 | 1);
    tree[i].sum = tree[i << 1].sum + tree[i << 1 | 1].sum;
}

void update(int x, int v, int i) {
    if (tree[i].l == tree[i].r) {
        tree[i].sum += v;
        return;
    }
    int mid = (tree[i].l + tree[i].r) >> 1;
    if (x <= mid) update(x, v, i << 1);
    else update(x, v, i << 1 | 1);
    tree[i].sum = tree[i << 1].sum + tree[i << 1 | 1].sum;
}

int query(int l, int r, int i) {
    if (l <= tree[i].l && tree[i].r <= r) return tree[i].sum;
    int mid = (tree[i].l + tree[i].r) >> 1;
    int res = 0;
    if (l <= mid) res += query(l, r, i << 1);
    if (r > mid) res += query(l, r, i << 1 | 1);
    return res;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, n, 1);
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            update(x, y, 1);
        } else {
            cout << query(x, y, 1) << endl;
        }
    }
    return 0;
}