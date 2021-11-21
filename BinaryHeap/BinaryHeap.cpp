#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

class BinaryHeap {
    vi heap = {3, 4, 6, 1, 23, 54, 100, 3, 2, 1, 0};

    void siftUp(int v) {
        while (v > 0 && heap[v] < heap[v >> 1]) {
            swap(heap[v], heap[v >> 1]);
            v >>= 1;
        }
    }

    void siftDown(int v) {
        int len = heap.size(), half = len >> 1;
        while (v < half) {
            int l = (v << 1) + 1;
            int r = l + 1;
            int t = r < len && heap[r] < heap[l] ? r : l;
            if (heap[v] < heap[t]) break;
            swap(heap[v], heap[t]);
            v = t;
        }
    }

    void build() {
        for (int i = heap.size(); i >= 0; i -= 1)
            siftDown(i);
    }

public:

    vi sort() {
        int len = heap.size();
        vi sortedArr(len);
        build();
        for (int i = 0; i < len; i += 1) {
            sortedArr[i] = heap[0];
            heap[0] = INT_MAX;
            siftDown(0);
        }
        return sortedArr;
    }

};
