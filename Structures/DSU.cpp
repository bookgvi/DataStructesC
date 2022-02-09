#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;


class DSUV2 {
public:
    vi parent, size;

    void setParent(int v) {
        parent[v] = v;
    }

    int find(int v) {
        if (parent[v] == v) return v;
        return parent[v] = find(parent[v]);
    }

    int unionSets(int a, int b) {
        a = find(a);
        b = find(b);

        if (a != b)
            if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return a;
    }
};