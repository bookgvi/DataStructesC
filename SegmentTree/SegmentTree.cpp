#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

vi arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int len = arr.size();
const int N = 1e5;
int st[N * 2];

void build() {
    memset(st, 0, N * 2 * sizeof(int));
    for (int i = len - 1; i >= 0; i -= 1) {
        st[i + len] = arr[i];
    }
    for (int i = len - 1; i > 0; i -= 1) {
        st[i] = st[i << 1] + st[i << 1 | 1];
    }
}

void modify(int p, int value) {
    for (st[p += len] = value; p > 1; p >>= 1)
        st[p >> 1] = st[p] + st[p ^ 1];
}

int query(int l, int r) {
    int res = 0;
    r += 1;
    for (l += len, r += len; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += st[l++];
        if (r & 1) res += st[--r];
    }
    return res;
}
