#include <bits/stdc++.h>

using namespace std;

class BinaryHeap {
public:
    int * sort(int *arr, int len) {
        int sorted[len];
        memset(sorted, 0, len * sizeof(int));
        build(arr, len);
        for (int i = 0; i < len; i += 1) {
            sorted[i] = arr[0];
            arr[0] = INT_MAX;
            siftDown(0, arr, len);
        }
        for (int i = 0; i < len; i += 1)
            cout << sorted[i] << " ";
        cout << "\n";
        return sorted;
    }

    void build(int *arr, int len) {
        for (int i = len - 1; i >= 0; i -= 1)
            siftDown(i, arr, len);
    }

    void siftDown(int v, int *arr, int len) {
        int half = len >> 1;
        while (v < half) {
            int l = (v << 1) + 1;
            int r = l + 1;
            int t = r < len && arr[r] < arr[l] ? r : l;
            if (arr[v] <= arr[t]) break;
            swap(v, t, arr);
            v = t;
        }
    }

    void swap(int i, int j, int *arr) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

};
