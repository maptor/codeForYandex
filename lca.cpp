#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include <ctime>
#include <queue>
#include <deque>
#include <unordered_map>
#include <map>
#include <random>
#include <cstdio>
#include <string>
#include <cctype>

#define pb push_back
#define eb emplace_back
#define rs resize
#define ld long double
#define vi vector<int>
using namespace std;

struct Edge {
    int to, num;
    Edge* back;
    bool is_bridge;
    Edge() {}
    Edge(int to, int num) : to(to), num(num), is_bridge(false) {}
};

int n, m;
vector<vector<Edge*>> gr;
vector<vector<int>> cgr;
vector<bool> used;
vi d, dp, comp;
vi dpth, euler, firstpos;
vi logs;
vector<vector<int>> sparse;

void dfs(int v, Edge* p = nullptr) {
    used[v] = true;
    if (p == nullptr)d[v] = 0;
    else d[v] = d[p->back->to] + 1;
    dp[v] = d[v];
    for (auto& e : gr[v]) {
        if (!used[e->to]) {
            dfs(e->to, e);
            dp[v] = min(dp[v], dp[e->to]);
        }
        else if (p && e != p->back) {
            dp[v] = min(dp[v], d[e->to]);
        }
    }
    if (dp[v] == d[v] && p) {
        p->is_bridge = true;
        p->back->is_bridge = true;
    }
}

void dfsBiconnect(int v, int cur_comp) {
    used[v] = true;
    comp[v] = cur_comp;
    for (auto& e : gr[v]) {
        if (e->is_bridge) {
            if (used[e->to]) {
                cgr[cur_comp].pb(comp[e->to]);
                cgr[comp[e->to]].pb(cur_comp);
            }
        }

        else if (!used[e->to]) {
            dfsBiconnect(e->to, cur_comp);
        }
    }
}

void eulerDfs(int v, int p = -1) {
    if (p == -1)dpth[v] = 0;
    else dpth[v] = dpth[p] + 1;
    firstpos[v] = euler.size();
    euler.pb(v);
    for (auto u : cgr[v]) {
        if (u != p) {
            eulerDfs(u, v);
            euler.pb(v);
        }
    }
}

inline int MIN(int u, int v) {
    return dpth[u] < dpth[v] ? u : v;
}

int ask(int l, int r) {
    int level = logs[r - l + 1];
    return MIN(sparse[level][l], sparse[level][r - (1 << level) + 1]);
}

int lca(int u, int v) {
    u = firstpos[u];
    v = firstpos[v];
    if (u > v)swap(u, v);
    return ask(u, v);
}

void solve() {
    int start;
    cin >> n >> m >> start;
    start--;
    gr.rs(n);
    d.rs(n);
    dp.rs(n);
    comp.rs(n);
    used.rs(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        Edge* a = new Edge(u, i);
        Edge* b = new Edge(v, i);
        a->back = b;
        b->back = a;
        gr[v].pb(a);
        gr[u].pb(b);
    }
    dfs(start);
    fill(used.begin(), used.end(), false);
    int cur_comp = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            cgr.push_back(vi{});
            dfsBiconnect(i, cur_comp);
            cur_comp++;
        }
    }
    dpth.rs(cur_comp);
    firstpos.rs(cur_comp);
    start = comp[start];
    eulerDfs(start);
    int l = euler.size();
    logs.rs(l + 1);
    logs[1] = 0;
    for (int i = 2; i <= l; i++) {
        logs[i] = logs[i / 2] + 1;
    }
    sparse.rs(logs[l] + 1, vi(l));
    for (int i = 0; i < l; i++) {
        sparse[0][i] = euler[i];
    }
    for (int level = 1; (1 << level) <= l; level++) {
        for (int i = 0; i + (1 << level) <= l; i++) {
            sparse[level][i] = MIN(sparse[level - 1][i], sparse[level - 1][i + (1 << (level - 1))]);
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        u = comp[u]; v = comp[v];
        cout << dpth[lca(u, v)] << "\n";
    }
}


signed main() {
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed;
    cout.precision(30);
    solve();
    //   system("pause");
}