#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

/*
*
*         0 ---------- 2
*        / \
*       /   \
*      /     \
*     /       \
*   1 -------- 4
*     \       /
*      \     /
*       \   /
*        \ /
*         3
*
* */

class AnotherGraphII {
private:
    vvi g;
    vi used, p, time_in, time_out, cycle, mstD, mstB;
    int n = 5, time = 0, isCycle = 0, cycle_start, cycle_end;

    void addVertex(int start, int end) {
        g[start].push_back(end);
        g[end].push_back(start);
    }

    void build() {
        addVertex(0, 1);
        addVertex(0, 4);
        addVertex(0, 2);
        addVertex(1, 4);
        addVertex(1, 3);
        addVertex(4, 3);
    }

    void init() {
        g = vvi(n, vi({}));
        used = vi(n), p = vi(n), time_in = vi(n), time_out = vi(n);
        time = 0, isCycle = 0, cycle_start = 0, cycle_end = 0;
        build();
    }

    void dfs(int v) {
        used[v] = 1;
        time_in[v] = time++;
        for (auto next : g[v]) {
            if (used[next] == 0) {
                p[next] = v;
                dfs(next);
            } else if (used[v] == 1 && next != p[v]) {
                isCycle = 1;
                cycle_start = v;
                cycle_end = next;
            }
        }
        mstD.push_back(v);
        time_out[v] = time++;
        used[v] = 2;
    }

    void bfs(int v) {
        init();
        queue<int> q;
        used[v] = 1;
        q.push(v);
        time_in[v] = time++;
        while (!q.empty()) {
            int cur = q.front();
            mstB.push_back(cur);
            q.pop();
            time_out[cur] = time++;
            for (auto next : g[cur]) {
                if (used[next] == 0) {
                    used[next] = 1;
                    q.push(next);
                    time_in[next] = time++;
                }
            }
        }
    }

    void getCycle() {
        if (isCycle) {
            while (cycle_end != cycle_start) {
                cycle.push_back(cycle_end);
                cycle_end = p[cycle_end];
            }
            cycle.push_back(cycle_start);
        }
    }

    void display(vi &arrV, int isReverse) {
        if (isReverse) reverse(arrV.begin(), arrV.end());
        for (auto i = arrV.begin(); i != arrV.end(); ++i) {
            printf("%d (%d, %d)\n", *i, time_in[*i], time_out[*i]);
        }
    }

public:
    void work() {
        init();
        dfs(1);
        cout << "mstD:\n";
        display(mstD, 1);
        if (isCycle) getCycle();
        cout << "Cycle:\n";
        display(cycle, 1);
        bfs(1);
        cout << "mstB:\n";
        display(mstB, 0);
        cout << "fin\n";
    }
};