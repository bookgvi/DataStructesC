#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> vvi;
typedef vector<int> vi;
typedef vector<vector<pair<int, int>>> vvpii;

const int n = 5;

/*
 *
 *      0
 *    / | \
 *   1--4  2
 *    \ |
 *     \|
 *      3
 *
 * */
class Deikstra {
private:
    vvi g;
    vi topo, cycle, mst, distance;
    int used[n], time_in[n], time_out[n], p[n],
            cycle_start, cycle_end,
            time = 0, isCycle = 0;

    void resetAll() {
        isCycle = 0, time = 0;
        memset(used, 0, n * sizeof(int));
        memset(time_in, 0, n * sizeof(int));
        memset(time_out, 0, n * sizeof(int));
        memset(p, 0, n * sizeof(int));
    }

    void addEdge(int start, int end, bool isDirect) {
        g[start].push_back(end);
        if (!isDirect) g[end].push_back(start);
    }

    void addEdge(int start, int end) {
        addEdge(start, end, true);
    }

    void build() {
        resetAll();
        addEdge(0, 1);
        addEdge(0, 4);
        addEdge(0, 2);
        addEdge(1, 4);
        addEdge(1, 3);
        addEdge(4, 3);
    }

    void dfsStart(int v) {
        memset(used, 0, n * sizeof(int));
        memset(p, 0, n * sizeof(int));
        dfs(v);
    }

    void bfsStart(int v) {
        resetAll();
        bfs(v);
    }

    void dfs(int v) {
        used[v] = 1;
        time_in[v] = time++;
        for (auto next : g[v]) {
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

    void bfs(int v) {
        queue<int> vertexQueue;
        used[v] = 1;
        time_in[v] = time++;
        vertexQueue.push(v);
        while (!vertexQueue.empty()) {
            int cur = vertexQueue.front();
            vertexQueue.pop();
            time_out[cur] = time++;
            mst.push_back(cur);
            for (auto next : g[cur]) {
                if (!used[next]) {
                    distance[next] = distance[cur] + 1;
                    time_in[next] = time++;
                    used[next] = 1;
                    vertexQueue.push(next);
                }
            }
        }
    }

    void getCycle() {
        while(cycle_end != cycle_start) {
            cycle.push_back(cycle_end);
            cycle_end = p[cycle_end];
        }
        cycle.push_back(cycle_start);
    }

    void display(vi graph, string title, bool revert) {
        cout << title << ":\n";
        if (revert) reverse(graph.begin(), graph.end());
        for (auto i = graph.begin(); i != graph.end(); i += 1)
            printf("%d(%d, %d)\n", *i, time_in[*i], time_out[*i]);
    }
public:
    Deikstra() : g(n), distance(n, -1) {}

    void work() {
        build();
        for (int i = 0; i < n && !isCycle; i += 1) {
            if (!used[i]) dfsStart(0);
        }
        if (isCycle) {
            getCycle();
            display(cycle, "Cycle", true);
        } else {
            display(topo, "topo sort", true);
        }
        bfsStart(0);
        display(mst, "BFS", false);
    }
};
