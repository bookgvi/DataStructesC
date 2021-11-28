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
    vi topo, mst, cycle, distance;
    int used[n], time_in[n], time_out[n], p[n],
            time = 0, isCycle = 0, cycle_start, cycle_end;

    void resetAll() {
        time = 0;
        isCycle = 0;
        memset(used, 0, n * sizeof(int));
        memset(time_in, 0, n * sizeof(int));
        memset(time_out, 0, n * sizeof(int));
        memset(p, 0, n * sizeof(int));
    }

    void addEdge(int start, int end, bool direct) {
        g[start].push_back(end);
        if (!direct) g[end].push_back(start);
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

    void dfs(int v) {
        used[v] = 1;
        time_in[v] = time++;
        for (auto next : g[v]) {
            if (!used[next]) {
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
        resetAll();
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

    void displayGraph(vi graph, string label, bool isRevert) {
        if (isRevert) reverse(graph.begin(), graph.end());
        cout << label << ":\n";
        for (auto v = graph.begin(); v != graph.end(); v += 1)
            printf("\t%d(%d, %d) - %d\n", *v, time_in[*v], time_out[*v], distance[*v]);
    }

    vi getCycle() {
        while (cycle_end != cycle_start) {
            cycle.push_back(cycle_end);
            cycle_end = p[cycle_end];
        }
        cycle.push_back(cycle_start);
    }

public:
    Deikstra() : g(n), distance(n, 0) {}

    void work() {
        build();
        for (auto i = 0; i < n && !isCycle; i += 1)
            if (!used[i]) dfs(i);
        if (isCycle) {
            getCycle();
            displayGraph(cycle,"cycle", true);
        } else {
            displayGraph(topo, "topo sort", true);
        }
        bfs(0);
        displayGraph(mst, "bfs", false);
    }
};
