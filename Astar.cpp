#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ctime>
#include <cmath>

using namespace std;
struct node {
    string s;
    int ptr, pre, F, depth;
};

node ori;
node des;
unordered_map<char, int> pos;
unordered_map<string, bool> visited;
vector<node> q;
int times = 0;


bool cmp(const node& a, const node& b) {
    return a.F > b.F;
}

int H(node& n) {
    int H = 0;
    for (int i = 0; i < n.s.length(); i++) {
        if (n.s[i] != des.s[i]) {
            H += fabs(i % 3 - pos[n.s[i]] % 3) + fabs(i / 3 - pos[n.s[i]] / 3);
        }
    }
    return H;
}

int F(node& n) {
    return H(n) + n.depth;
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

void init() {
    des.s = "1238-4765";
    des.ptr = 4;
    for (int i = 0; i < des.s.length(); i++) {
        pos[des.s[i]] = i;
    }
    ori.s = "5674283-1";
    for (int i = 0; i < ori.s.length(); i++) {
        if (ori.s[i] == '-') {
            ori.ptr = i;
            break;
        }
    }
    ori.pre = -1;
    ori.depth = 0;
    ori.F = F(ori);
}

bool isVisited(node& n) {
    if (visited.count(n.s) == 0) {
        return false;
    }
    return true;
}

node swap(node n, const int a, const int b) {
    char temp = n.s[a];
    n.s[a] = n.s[b];
    n.s[b] = temp;
    n.ptr = n.s[a] == '-' ? a : b;
    n.depth++;
    return n;
}

void process(int front, int arg) {
    node temp = swap(q[front], q[front].ptr, q[front].ptr + arg);
    temp.pre = front;
    if (!isVisited(temp)) {
        visited[temp.s] = true;
        temp.F = F(temp);
        q.push_back(temp);
        push_heap(q.begin() + front + 1, q.end(), cmp);
    }
}

void up(int front) {
    if (q[front].ptr - 3 >= 0) {
        process(front, -3);
    }
}

void down(int front) {
    if (q[front].ptr + 3 <= 8) {
        process(front, 3);
    }
}

void left(int front) {
    int ptr = q[front].ptr;
    if (ptr != 0 && ptr != 3 && ptr != 6) {
        process(front, -1);
    }
}

void right(int front) {
    int ptr = q[front].ptr;
    if (ptr != 2 && ptr != 5 && ptr != 8) {
        process(front, 1);
    }
}

void show(node& n) {
    cout << "Found" << endl;
    vector<node> ans;
    while (n.pre != -1) {
        ans.push_back(n);
        n = q[n.pre];
    }
    ans.push_back(ori);
    for (auto it = ans.rbegin(); it != ans.rend(); it++) {
        printf("--------- Depth = %d, F = %d\n", it->depth, it->F);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << it->s[3 * i + j] << "  ";
            }
            cout << endl;
        }
    }
    cout << "Total times: " << times << endl;
}

int main() {
    clock_t start = clock();
    init();
    if (check(ori.s) != check(des.s)) {
        cout << "No solution" << endl;
        return 0;
    }
    q.push_back(ori);
    make_heap(q.begin(), q.end(), cmp);
    for (int front = 0; front < q.size(); front++) {
        times++;
        if (q[front].s == des.s) {
            show(q[front]);
            break;
        }
        left(front);
        up(front);
        right(front);
        down(front);
    }
    clock_t end = clock();
    cout << "Total cost: " << (double)(end - start) / CLOCKS_PER_SEC << " second" << endl;
    return 0;
}
