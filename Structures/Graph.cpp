#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

/*
 * 0 --- 1
 * |     |
 * 2 --- 3
 * */
class GraphV2 {
public:
    int n = 4;
    vvi g;
    vi topo, cycle, mst,
            used, p, time_in, time_out;
    int isCycle = 0, time = 0, cycle_start, cycle_end;

    void init() {
        g = vvi(n, vi({}));
        used = vi(n, 0), p = vi(n, 0), time_in = vi(n, 0), time_out = vi(n, 0);
    }

    void addEdge(int start, int end) {
        g[start].push_back(end);
        g[end].push_back(start);
    }

    void build() {
        addEdge(0, 1);
        addEdge(0, 2);
        addEdge(3, 2);
        addEdge(3, 1);
    }

    void setUnused() {
        used = vi(n, 0), p = vi(n, 0), time_in = vi(n, 0), time_out = vi(n, 0);
        time = 0;
        isCycle = 0;
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
        topo.push_back(v);
        time_out[v] = time++;
    }

    void storeCycle() {
        while(cycle_end != cycle_start) {
            cycle.push_back(cycle_end);
            cycle_end = p[cycle_end];
        }
        cycle.push_back(cycle_start);
    }

    void bfs(int start) {
        setUnused();
        queue<int> vq;
        used[start] = 1;
        vq.push(start);
        time_in[start] = time++;
        while(!vq.empty()) {
            int cur = vq.front();
            vq.pop();
            time_out[cur] = time++;
            mst.push_back(cur);
            for (auto next : g[cur]) {
                if (used[next] == 0) {
                    used[next] = 1;
                    time_in[next] = time++;
                    vq.push(next);
                }
            }
        }
    }

    void work() {
        init();
        build();
        for (auto i = 0; i != n && !isCycle; i += 1)
            if (!used[i]) dfs(i);
        if(isCycle) storeCycle();
        bfs(0);
    }
};