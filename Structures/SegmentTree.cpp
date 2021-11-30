#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

class SegmentTreeV2 {
public:
    vi st;
    int n = 0;

    void build(vi &nums) {
        n = (int) nums.size();
        st = vi(n << 1, 0);
        for (int i = 0; i < n; i += 1)
            st[i + n] = nums[i];
        for (int i = n - 1; i > 0; i -= 1)
            st[i] = st[i << 1] + st[i << 1 | 1];
    }

    void modify(int v, int value) {
        for (st[v += n] = value; v > 0; v >>= 1)
            st[v >> 1] = st[v] + st[v ^ 1];
    }

    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += st[l++];
            if (r & 1) res += st[--r];
        }
        return res;
    }

    void work() {
        vi nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        build(nums);
        int r1 = query(1, 6);
        modify(1, 10);
        int r2 = query(1, 5);
    }
};