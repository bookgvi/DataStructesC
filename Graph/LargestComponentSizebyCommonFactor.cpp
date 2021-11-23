#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> vvi;
typedef vector<int> vi;

class LargestComponentSizebyCommonFactor {
private:
    vvi g, components;
    vi used, cc_num;
    int cc = 0;

    void addEdge(int start, int end) {
        g[start].push_back(end);
    }

    void dfs(int v) {
        used[v] = 1;
        cc_num.push_back(v);
        for (auto i = 0; i != g[v].size(); i += 1) {
            int next = g[v][i];
            if (!used[next])
                dfs(next);
        }
    }

    int gcd(int a, int b) {
        if (a == 0) return b;
        return gcd(b % a, a);
    }

    void generateGraph(vi &nums) {
        for (auto i = 0; i != nums.size(); i += 1) {
            for (auto j = i + 1; j != nums.size(); j += 1)
                if (gcd(nums[i], nums[j]) > 1) {
                    addEdge(nums[i], nums[j]);
                    addEdge(nums[j], nums[i]);
                }
        }
    }

public:
    int largestComponentSize(vector<int> &nums) {
        int maxLen = 0;
        used = vi(1e5 + 1);
        g = vvi(1e5 + 1);
        components = vvi(nums.size());
        generateGraph(nums);
        for (auto i = 0; i != nums.size(); i += 1) {
            if (!used[nums[i]]) {
                cc_num = vi();
                dfs(nums[i]);
                components[cc] = cc_num;
                cc += 1;
                maxLen = max(maxLen, (int) cc_num.size());
            }
        }
        return maxLen;
    }

    void work() {
        vi nums = {4, 6, 15, 35};
//        vi nums = {2, 3, 6, 7, 4, 12, 21, 39};
//        vi nums = {20,50,9,63};
        int res = largestComponentSize(nums);
        cout << res << "\n";
    }
};