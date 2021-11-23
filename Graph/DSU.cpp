#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

/*
 * You are given an integer array of unique positive integers nums. Consider the following graph:
 * There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
 * There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
 * Return the size of the largest connected component in the graph.
 *
 *
 * https://leetcode.com/problems/largest-component-size-by-common-factor/
 * */
class DSU {
public:
    vi parent, size;

    DSU(int n) : parent(n), size(n, 1) {
        iota(begin(parent), end(parent), 0);
    }

    void makeSet(int v) {
        parent[v] = v;
    }

    int find_set(int v) {
        if (parent[v] == v) return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
            if (size[a] < size[b])
                swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }

};

class SolutionForLCSCF {
public:
    int largestComponentSize(vector<int> &nums) {
        int n = nums.size(), maxV = 0;
        DSU ds(*max_element(begin(nums), end(nums)) + 1);
        for (int num : nums) {
            for (int i = 2; i * i <= num; i += 1) {
                if (num % i == 0)
                    ds.union_sets(num, i), ds.union_sets(num, num / i);
            }
        }
        unordered_map<int, int> counter;
        for (int i = 0; i < n; i += 1)
            maxV = max(maxV, counter[ds.find_set(nums[i])] += 1);
        return maxV;
    }

    void work() {
//        vi nums = {4, 6, 15, 35};
//        vi nums = {2, 3, 6, 7, 4, 12, 21, 39};
        vi nums = {20, 50, 9, 63};
        int res = largestComponentSize(nums);
    }
};
