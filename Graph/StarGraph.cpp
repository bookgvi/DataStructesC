#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

class StarGraph {
private:
    vector<vector<int>> g = {};

    vi mst = {};
    int used[5], time_start[5], time_end[5];
    int timeInVertex = 0;

public:
    void addEdge(int start, int end, bool isBidirect) {
        g[start].push_back(end);
        if (isBidirect) g[end].push_back(start);
    }

    void dfs(int vertex) {
        used[vertex] = 1;
        time_start[vertex] = timeInVertex++;
        mst[vertex] = vertex;
        for (auto i = g[vertex].begin(); i != g[vertex].end(); i += 1) {
            if (!used[*i]) dfs(*i);
        }
        time_end[vertex] = timeInVertex++;
    }

    void buildStar() {
        addEdge(0, 2, 1);
        addEdge(0, 3, 1);
        addEdge(1, 3, 1);
        addEdge(1, 4, 1);
        addEdge(2, 4, 1);
    }

//    void displayDFS() {
//        for (int i = mst.begin(); i != mst.end(); i += 1) {
//            printf("%d(%d, %d)\n", mst[*i], time_start[*i], time_end[*i]);
//        }
//    }
};