#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

class AnotherGraph {
private:
    vvi g;
    int used[7], time_in[7], time_out[7], mst[7], p[7];
    int time = 0, cycle_start, cycle_end;
    bool cycle = false;

    void addEdge(int v1, int v2) {
        g[v1].push_back(v2);
    }

    void setUnused() {
        size_t len = sizeof(used) / sizeof(used[0]);
        for (size_t i = 0; i < len; i += 1)
            used[i] = 0;
    }

public:
    AnotherGraph() : g(7, vi(0)) {}

    vvi build() {
        addEdge(0, 1);
        addEdge(1, 0);
        addEdge(1, 2);
        addEdge(2, 1);
        addEdge(2, 3);
        addEdge(3, 2);
        addEdge(3, 4);
        addEdge(4, 3);
        addEdge(4, 5);
        addEdge(5, 4);
        addEdge(5, 6);
        addEdge(6, 5);
        addEdge(3, 6);
        addEdge(6, 3);
        setUnused();
        return g;
    }

    void reset() {
        setUnused();
    }

    void dfs(int v) {
        used[v] = 1;
        time_in[v] = time++;
        mst[v] = v;
        for (size_t i = 0; i < g[v].size(); i += 1) {
            int next = g[v][i];
            if (used[next] == 0) {
                p[next] = v;
                dfs(next);
            } else if (used[next] == 1 && next != p[v]) {
                cycle_start = next;
                cycle_end = v;
                cycle = true;
            }
        }
        used[v] = 2;
        time_out[v] = time++;
    }

    vi getCycle() {
        vi cycleV;
        if (cycle) {
            while (cycle_end != cycle_start) {
                cycleV.push_back(cycle_end);
                cycle_end = p[cycle_end];
            }
            cycleV.push_back(cycle_start);
        }
        return cycleV;
    }

    void displayMST() {
        for (auto i : mst) {
            printf("%d(%d, %d)\n", mst[i], time_in[i], time_out[i]);
        }
    }
};