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
    vi cycle, topo, bfsV;
    int used[6], time_in[6], time_out[6], p[6],
            time = 0, isCycle = 0, cycle_start, cycle_end;

    void addEdge(int start, int end) {
        g[start].push_back(end);
//        if (!isDirect) g[end].push_back(start);
    }

    void setUnused() {
        memset(used, 0, 6 * sizeof(int));
    }

    vvi build() {
        addEdge(0, 1);
        addEdge(0, 4);
        addEdge(4, 5);
        addEdge(1, 2);
        addEdge(1, 3);
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

    void bfs(int startVertex) {
        time = 0;
        setUnused();
        queue<int> vertexQueue;
        used[startVertex] = 1;
        time_in[startVertex] = time++;
        vertexQueue.push(startVertex);
        while(!vertexQueue.empty()) {
            int cur = vertexQueue.front();
            vertexQueue.pop();
            bfsV.push_back(cur);
            time_out[cur] = time++;
            for (auto next : g[cur]) {
                if (used[next] == 0) {
                    used[next] = 1;
                    time_in[next] = time++;
                    vertexQueue.push(next);
                }
            }
        }
    }

    vi getCycle() {
        while (cycle_end != cycle_start) {
            cycle.push_back(cycle_end);
            cycle_end = p[cycle_end];
        }
        cycle.push_back(cycle_start);
        return cycle;
    }

    void display(vi graph, bool revert, string title) {
        cout << title << ":\n";
        if (revert) {
            for (auto v = graph.rbegin(); v != graph.rend(); v += 1)
                printf("%d(%d, %d)\n", *v, time_in[*v], time_out[*v]);
        } else {
            for (auto v = graph.begin(); v != graph.end(); v += 1)
                printf("%d(%d, %d)\n", *v, time_in[*v], time_out[*v]);
        }
    }

public:
    AnotherGraph() : g(6) {}

    void work() {
        build();
        for (auto i = 0; i < 6 && !isCycle; i += 1)
            if (!used[i]) {
                dfs(0);
            }
        if (isCycle) {
            getCycle();
            display(cycle, true, "Cycle");
        } else display(topo, true, "Topo sort");

        bfs(0);
        display(bfsV, false, "BFS");
    }
};