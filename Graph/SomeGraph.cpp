#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

class SomeGraph {
    vvi g;
    vi vInCycle;
    int time = 0, cycle = 0, cycle_st, cycle_end;
    int used[7], mst[7], time_in[7], time_out[7], p[7];

    void setUnused() {
        memset(used, 0, 7 * sizeof(int));
    }
public:
    SomeGraph() : g(7, vi(0)) {}

    void addEdge(int start, int end) {
        g[start].push_back(end);
    }

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

    void dfs(int v) {
        used[v] = 1;
        time_in[v] = time++;
        mst[v] = v;
        for (int i = 0; i != g[v].size(); i += 1) {
            int next = g[v][i];
            if (used[next] == 0) {
                p[next] = v;
                dfs(next);
            } else if (used[next] == 1 && p[v] != next) {
                cycle = 1;
                cycle_st = next;
                cycle_end = v;
            }
        }
        used[v] = 2;
        time_out[v] = time++;
    }

    void getCycle() {
        while(cycle_end != cycle_st) {
            vInCycle.push_back(cycle_end);
            cycle_end = p[cycle_end];
        }
        vInCycle.push_back(cycle_st);
    }

    void display() {
        for (auto i : mst) {
            printf("%d(%d, %d)\n", mst[i], time_in[i], time_out[i]);
        }
        for (auto v : vInCycle)
            printf("%d ", v);
        cout << "\n";
    }
};