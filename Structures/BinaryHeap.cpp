#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

class BinaryHeapV2 {
public:
    vi heap;

    void siftDown(int v, vi &ar1) {
        int len = (int) ar1.size(), half = len >> 1;
        while (v < half) {
            int l = (v << 1) + 1;
            int r = l + 1;
            int tmp = r < len && ar1[r] < ar1[l] ? r : l;
            if (ar1[v] <= ar1[tmp]) break;
            swap(ar1[v], ar1[tmp]);
            v = tmp;
        }
    }

    void siftUp(int v, vi &arr1) {
        while (v > 0 && arr1[v] < arr1[v >> 1]) {
            swap(arr1[v], arr1[v >> 1]);
            v >>= 1;
        }
    }

    void build(vi &arr1) {
        for (int i = (int) arr1.size() - 1; i >= 0; i -= 1)
            siftDown(i, arr1);
    }

    void work() {
        vi nums = {1, 16, 11, 9, 10, 5, 6, 8, 1, 2, 4, 10, 4, 0};
        build(nums);
    }
};
