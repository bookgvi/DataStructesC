#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

class BinaryHeapV2 {
public:
    vi heap;

    static void siftDown(int v, vi &arr1) {
        int len = (int) arr1.size(), half = len >> 1;
        while (v < half) {
            int l = (v << 1) + 1;
            int r = l + 1;
            int t = r < len && arr1[r] < arr1[l] ? r : l;
            if (arr1[v] <= arr1[t]) break;
            swap(arr1[v], arr1[t]);
            v = t;
        }
    }

    void siftUp(int v, vi &arr1) {
        while (v > 0 && arr1[v] < arr1[v >> 1]) {
            swap(arr1[v], arr1[v >> 1]);
            v >>= 1;
        }
    }

    void build(vi &nums) {
        for (int i = (int) nums.size() - 1; i >= 0; i -= 1)
            siftDown(i, nums);
    }

    void work() {
        vi nums = {1, 16, 11, 9, 10, 5, 6, 8, 1, 2, 4, 10, 4, 0};
        build(nums);
    }
};
