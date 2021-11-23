#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

class DSU {
private:
    vi parent;

    void makeSet(int v) {
        parent[v] = v;
    }

    int find_set(int v) {
        if (parent[v] == v) return v;
        return find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
            parent[b] = a;
    }

public:
    DSU() : parent(10) {}
};
