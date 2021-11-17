#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

vvi g(10);
void addEdge(int start, int end, bool isBidirect) {
    g[start].push_back(end);
    cout << "\n";
}