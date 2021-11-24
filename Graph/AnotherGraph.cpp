#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

/*
 *      0
 *     / \
 *    1---2
 *    | x |
 *    3---4
 *
 * */
class AnotherGraph {
private:
    vvi g;
    vi cycle, topo;
    int used[5], time_in[5], time_out[5], p[5],
            time = 0, isCycle = 0, cycle_start, cycle_end;

    void addEdge(int start, int end, bool isDirect) {
        g[start].push_back(end);
        if (!isDirect) g[end].push_back(start);
    }

    void setUnused() {
        memset(used, 0, 5 * sizeof(int));
    }

    vvi build() {
        addEdge(0, 1, true);
        addEdge(0, 2, true);
        addEdge(1, 2, true);
        addEdge(1, 3, true);
        addEdge(1, 4, true);
        addEdge(2, 3, true);
        addEdge(2, 4, true);
        addEdge(3, 4, true);
        setUnused();
        return g;
    }

    void dfs(int v) {
        used[v] = 1;
        time_in[v] = time++;
        for (auto next : g[v]) {
            if (used[next] == 0) {
                p[next] = v;
                dfs(next);
            } else if (used[next] == 1 && p[v] != next) {
                isCycle = 1;
                cycle_start = next;
                cycle_end = v;
            }
        }
        used[v] = 2;
        time_out[v] = time++;
        topo.push_back(v);
    }

    vi getCycle() {
        while (cycle_end != cycle_start) {
            cycle.push_back(cycle_end);
            cycle_end = p[cycle_end];
        }
        cycle.push_back(cycle_start);
        return cycle;
    }

    void display(vi graph, string title) {
        cout << title << ":\n";
        for (auto v = graph.rbegin(); v != graph.rend(); v += 1)
            printf("%d(%d, %d)\n", *v, time_in[*v], time_out[*v]);
    }

public:
    AnotherGraph() : g(5) {}

    void work() {
        build();
        for (auto i = 0; i < 5 && !isCycle; i += 1)
            if (!used[i]) {
                dfs(0);
            }
        if (isCycle) {
            getCycle();
            display(cycle, "Cycle");
        } else display(topo, "Topo sort");
    }
};