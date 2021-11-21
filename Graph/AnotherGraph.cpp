#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

class AnotherGraph {
private:
    vvi g;
    vi cycle;
    int time = 0, cycle_start, cycle_end, isCycle;
    int used[7], time_in[7], time_out[7], p[7], mst[7];

    void addEdge(int start, int end) {
        g[start].push_back(end);
    }

    void setUnused() {
        memset(used, 0, 7 * sizeof(int));
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
        for (size_t i = 0; i < g[v].size(); i += 1) {
            int next = g[v][i];
            if (used[next] == 0) {
                p[next] = v;
                dfs(next);
            } else if (used[next] == 1 && next != p[v]) {
                cycle_start = next;
                cycle_end = v;
                isCycle = true;
            }
        }
        time_out[v] = time++;
        used[v] = 2;
    }

    void getCycle() {
        while (cycle_end != cycle_start) {
            cycle.push_back(cycle_end);
            cycle_end = p[cycle_end];
        }
        cycle.push_back(cycle_start);
    }

    void bfs(int start) {
        setUnused();
        int current, next;
        queue<int> vertexQueue;
        used[start] = 1;
        vertexQueue.push(start);
        while(!vertexQueue.empty()) {
            current = vertexQueue.front();
            vertexQueue.pop();
            used[current] = 2;
            for (auto i = 0; i < g[current].size(); i += 1) {
                next = g[current][i];
                if (used[next] == 0) {
                    used[next] = 1;
                    vertexQueue.push(next);
                    printf("%d->%d ", current, next);
                }
            }
        }
        cout << "\n";
    }

public:
    AnotherGraph() : g(7) {};

    void work() {
        build();
        setUnused();
        dfs(0);
        for (auto i : mst)
            printf("%d(%d, %d)\n", mst[i], time_in[i], time_out[i]);
        getCycle();
        for (auto i = cycle.rbegin(); i != cycle.rend(); i += 1) {
            printf("%d ", *i);
        }
        cout << "\n";
        bfs(0);
    }
};