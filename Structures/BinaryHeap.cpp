#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

class BinaryHeapV2 {
public:
    vi heap;

    void siftDown(int v, vi &arr) {
        int len = (int) arr.size(), half = len >> 1;
        while(v < half) {
            int l = (v << 1) + 1;
            int r = l + 1;
            int t = r < len && arr[r] < arr[l] ? r : l;
            if (arr[v] <= arr[t]) break;
            swap(arr[v], arr[t]);
            v = t;
        }
    }

    void siftUp(int v, vi &arr) {
        while(v > 0 && arr[v] < arr[v >> 1]) {
            swap(arr[v], arr[v >> 1]);
            v >>= 1;
        }
    }

    vi build(vi &arr) {
        heap = arr;
        for (int i = (int) arr.size(); i >= 0; i -= 1)
            siftDown(i, heap);
        return heap;
    }

    void work() {
        vi nums = {3, 4, 6, 1, 23, 54, 100, 3, 2, 1, 0};
        build(nums);
    }
};
