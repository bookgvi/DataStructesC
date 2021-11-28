#include <bits/stdc++.h>

using namespace std;

class Vertex {
public:
    string label;
    string suffix;
    unordered_map<string, Vertex *> toNext;
    vector<Vertex *> outArr;
    Vertex *suffLink;
    bool isVisited;
    bool isTerminal;

    Vertex(string label, string suffix) {
        this->label = label;
        this->suffix = suffix;
        this->suffLink = nullptr;
        this->isVisited = false;
        this->isTerminal = false;
    }
};

class Bor {
private:
    Vertex *root = new Vertex("root", "");

    void addKeyWord(string &keyWord) {
        Vertex *curVertex = root;
        string suffix;
        for (int i = 0, len = (int) keyWord.length(); i < len; i += 1) {
            string ch = keyWord.substr(i, 1);
            suffix += ch;
            if (!curVertex->toNext.count(ch)) curVertex->toNext[ch] = new Vertex(ch, suffix);
            curVertex = curVertex->toNext[ch];
        }
        curVertex->isTerminal = true;
    }

    unordered_map<string, vector<int>> analizeText(string &text) {
        unordered_map<string, vector<int>> wordsPos;
        Vertex *curVertex = root;
        int index = 0;
        for (int i = 0, len = (int) text.length(); i < len; i += 1) {
            string ch = text.substr(i, 1);
            index += 1;
            curVertex = delta(ch, curVertex);
            if (curVertex == root) {
                if (!curVertex->toNext.count(ch)) continue;
                else curVertex->toNext[ch];
            }
            isOut(curVertex, wordsPos, index);
        }
        return wordsPos;
    }

    Vertex *delta(const string& ch, Vertex *curVertex) {
        if (!curVertex->toNext.count(ch) && curVertex->suffLink->toNext.count(ch))
            return curVertex->suffLink->toNext[ch];
        else if (curVertex->toNext.count(ch))
            return curVertex->toNext[ch];
        return root;
    }

    static void isOut(Vertex *curVertex, unordered_map<string, vector<int>> &wordsPos, int index) {
        for (auto outV : curVertex->outArr) fillWordsPos(outV, wordsPos, index);
    }

    static void fillWordsPos(Vertex *outV, unordered_map<string, vector<int>> &wordsPos, int index) {
        int pos = index - (int) outV->suffix.length();
        vector<int> positions;
        if (wordsPos.count(outV->suffix)) positions = wordsPos[outV->suffix];
        positions.push_back(pos);
        wordsPos[outV->suffix] = positions;
    }

    void init() {
        Vertex *startVertex = root, *curVertex, *nextVertex;
        queue<Vertex *> vQ;
        setRootSuffLink();
        startVertex->isVisited = true;
        vQ.push(startVertex);
        while (!vQ.empty()) {
            curVertex = vQ.front();
            vQ.pop();
            while ((nextVertex = getUnvisited(curVertex)) != nullptr) {
                nextVertex->isVisited = true;
                vQ.push(nextVertex);
                setSuffLink(curVertex, nextVertex);
            }
        }
        setOutArr(root);
        setUnvisited(root);
    }

    void setOutArr(Vertex *curVertex) {
        for (const auto& nextV : curVertex->toNext) {
            if (nextV.second != NULL) {
                fillOutArr(nextV.second, nextV.second->outArr);
                setOutArr(nextV.second);
            }
        }
    }

    void fillOutArr(Vertex *curVertex, vector<Vertex *> &outArr) {
        if (curVertex->isTerminal) outArr.push_back(curVertex);
        if (curVertex->suffLink == root) return;
        fillOutArr(curVertex->suffLink, outArr);
    }

    void setSuffLink(Vertex *parentV, Vertex *curV) {
        Vertex *parentSuffLink = parentV->suffLink;
        if (curV->suffLink == nullptr) {
            curV->suffLink = parentSuffLink->toNext[curV->label];
            if (curV->suffLink == nullptr) curV->suffLink = root;
        }
    }

    void setRootSuffLink() {
        root->suffLink = root;
        for (const auto& firstAfterRoot : root->toNext) firstAfterRoot.second->suffLink = root;
    }

    static void setUnvisited(Vertex *curVertex) {
        if (curVertex != nullptr) {
            curVertex->isVisited = false;
            for (const auto& nextV : curVertex->toNext)
                setUnvisited(nextV.second);
        }
    }

    static Vertex *getUnvisited(Vertex *curVertex) {
        for (const auto& nextV : curVertex->toNext) {
            if (!nextV.second->isVisited) return nextV.second;
        }
        return nullptr;
    }

public:
    void work() {
        vector<string> keyWords = {"a", "abba", "aca"};
        string text = "abacabba";
        for (auto keyWord: keyWords) addKeyWord(keyWord);
        init();
        unordered_map<string, vector<int>> res = analizeText(text);
        for (const auto& kv : res) {
            printf("%s = [ ", kv.first.c_str());
            for (auto i : kv.second) {
                printf("%d ", i);
            }
            cout << "]\n";
        }
    }
};