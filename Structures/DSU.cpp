#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;


class DSUV2 {
public:
    vi parent, size;

    DSUV2() : parent(10), size(10) {}

    void set_tree(int v) {
        parent[v] = v;
    }

    int find_set(int v) {
        if (parent[v] == v) return v;
        return parent[v] = find_set(parent[v]);
    }

    int union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return a;
    }
};