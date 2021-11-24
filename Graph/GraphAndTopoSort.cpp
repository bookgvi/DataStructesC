#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> vvi;
typedef vector<int> vi;

/*
 *  0 -----> 1 ---> 2
 *  ^        ^ \
 *  |        |  \
 *  |        |   \
 *  3 -----> 4    5
 *
 * */
class GraphAndTopoSort {
    vvi g;
    vi topo, cycle;
    int time = 0, isCycle = 0, cycle_start, cycle_end;
    int used[6], time_in[6], time_out[6], p[6];

    void setUnused() {
        memset(used, 0, 6 * sizeof(int));
    }

    void addEdge(int start, int end) {
        g[start].push_back(end);
    }

    void build() {
        addEdge(0, 1);
        addEdge(1, 2);
        addEdge(1, 5);
        addEdge(3, 0);
        addEdge(3, 4);
        addEdge(4, 1);

        // create cycle for test
//        addEdge(0, 3);
//        addEdge(4, 3);
//        addEdge(1, 0);
//        addEdge(1, 4);

        setUnused();
    }

    void dfs(int v) {
        used[v] = 1;
        time_in[v] = time++;
        for (auto i = 0; i != g[v].size(); i += 1) {
            int next = g[v][i];
            if (used[next] == 0) {
                p[next] = v;
                dfs(next);
            } else if (used[next] == 1 && next != p[v]) {
                isCycle = 1;
                cycle_start = next;
                cycle_end = v;
            }
        }
        used[v] = 2;
        time_out[v] = time++;
        topo.push_back(v);
    }

    void getTopo() {
        for (int i = 0; i < 6 && !isCycle; i += 1) {
            if (!used[i]) dfs(i);
        }
        if (!isCycle) {
            cout << "topo sort:\n";
            for (auto i = topo.rbegin(); i != topo.rend(); i += 1) {
                printf("%d -> ", (*i));
            }
            cout << "exit\n";
        }
    }

    void getCycle() {
        while (cycle_end != cycle_start) {
            cycle.push_back(cycle_end);
            cycle_end = p[cycle_end];
        }
        cycle.push_back(cycle_start);
    }

public:
    GraphAndTopoSort() : g(6) {}

    void work() {
        build();
        getTopo();
        if (isCycle) {
            getCycle();
            cout << "Cycle:\n";
            for (auto i = cycle.rbegin(); i != cycle.rend(); i += 1)
                printf("%d(%d, %d) ", (*i), time_in[*i], time_out[*i]);
            cout << "\n";
        }
    }
};
