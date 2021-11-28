#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

class SuffixArrayV2 {
public:
    vi p;
    vvi cList;

    vi suffixArray(string &str) {
        int len = (int) str.length(), b = 8;
        vi p(len, 0), c(len, 0), count(1 << b, 0);
        for (int i = 0; i < len; i += 1)
            count[str[i] - 'a' + 1] += 1;
        for (int i = 1; i < 1 << b; i += 1)
            count[i] += count[i - 1];
        for (int i = len - 1; i >= 0; i -= 1)
            p[--count[str[i] - 'a' + 1]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < len; i += 1) {
            if (str[p[i]] != str[p[i - 1]]) classes += 1;
            c[p[i]] = classes - 1;
        }
        cList.push_back(c);
        vi pn(len, 0), cn(len, 0);
        for (int h = 0; 1 << h < len; h += 1) {
            for (int i = 0; i < len; i += 1) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0) pn[i] += len;
            }
            count = vi(1 << b, 0);
            for (int i = 0; i < len; i += 1)
                count[c[pn[i]]] += 1;
            for (int i = 1; i < 1 << b; i += 1)
                count[i] += count[i - 1];
            for (int i = len - 1; i >= 0; i -= 1)
                p[--count[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < len; i += 1) {
                int mid1 = (p[i] + (1 << h)) % len, mid2 = (p[i - 1] + (1 << h)) % len;
                if (c[p[i]] != c[p[i - 1]] || c[mid1] != c[mid2]) classes += 1;
                cn[p[i]] = classes - 1;
            }
            cList.push_back(cn);
            for (int i = 0; i < len; i += 1)
                c[i] = cn[i];
        }
        return p;
    }

    void work() {
        string str = "bobrabrakadabra";
        vi p = suffixArray(str);
        for (int index : p)
            cout << str.substr(index) << "\n";
    }
};