#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>

using namespace std;
struct node {
    string s;
    int ptr;
};
//最大递归深度
const int maxDepth = 33;
int times = 0;
bool isFound = false;

node ori;
node des;
vector<node> stack;
unordered_map<string, bool> visited;

void dfs(node n, int count);

void init() {
    ori.s = "5674-8321";
    for (int i = 0; i < ori.s.length(); i++) {
        if (ori.s[i] == '-') {
            ori.ptr = i;
            break;
        }
    }
    des.s = "1238-4765";
    des.ptr = 4;
    stack.push_back(ori);
}

bool check(string s) {
    int sum = 0;
    for (int j = 0; j < s.length(); j++) {
        for (int w = 0; w < j; w++) {
            if (s[w] != '-' && s[j] != '-' && s[w] > s[j]) {
                sum++;
            }
        }
    }
    if (sum % 2 == 0) {
        return true;

    }
    else {
        return false;
    }
}

node swap(node& n, const int a, const int b) {
    node next = n;
    char temp = next.s[a];
    next.s[a] = next.s[b];
    next.s[b] = temp;
    next.ptr = next.s[a] == '-' ? a : b;
    return next;
}

bool isVisited(node& n) {
    if (visited.count(n.s) == 0) {
        return false;
    }
    return true;
}

void process(node& n, int arg, int count) {
    node temp = swap(n, n.ptr, n.ptr + arg);
    if (!isFound && !isVisited(temp) && count < maxDepth) {
        stack.push_back(temp);
        visited[temp.s] = true;
        dfs(temp, count + 1);
        stack.pop_back();
        visited.erase(temp.s);
    }
}

void up(node& n, int count) {
    if (n.ptr - 3 >= 0) {
        process(n, -3, count);
    }
}

void down(node& n, int count) {
    if (n.ptr + 3 <= 8) {
        process(n, 3, count);
    }
}

void left(node& n, int count) {
    int ptr = n.ptr;
    if (ptr != 0 && ptr != 3 && ptr != 6) {
        process(n, -1, count);
    }
}

void right(node& n, int count) {
    int ptr = n.ptr;
    if (ptr != 2 && ptr != 5 && ptr != 8) {
        process(n, 1, count);
    }
}

void show(node* n) {
    cout << "Found" << endl;
    int depth = 0;
    for (auto it = stack.begin(); it != stack.end(); it++) {
        cout << "--------- Depth = " << depth++ << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << it->s[3 * i + j] << "  ";
            }
            cout << endl;
        }
    }
}

void dfs(node n, int count) {
    if (n.s == des.s) {
        isFound = true;
        show(&n);
        return;
    }
    times++;
    left(n, count);
    up(n, count);
    right(n, count);
    down(n, count);
}

int main() {
    clock_t start = clock();
    init();
    if (check(ori.s) != check(des.s)) {
        cout << "No solution" << endl;
        return 0;
    }
    dfs(ori, 0);
    clock_t end = clock();
    cout << "Total times = " << times << endl;
    cout << "Total cost: " << (double)(end - start) / CLOCKS_PER_SEC << " second" << endl;
    return 0;
}
