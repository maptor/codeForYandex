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
#define vpii vector<pair<int, int>>
#define ull unsigned long long 

using namespace std;

const int INF = 1e9 + 228;


inline int SuperRand() {
    if (RAND_MAX == (1 << 15) - 1) {
        return (rand() << 15) + rand();
    }
    return rand();
}

struct Node {
    Node* l, * r;
    int key, prior, sz, minn;
    Node() : l(nullptr), r(nullptr), minn(INF){}
    Node(int key) : l(nullptr), r(nullptr), key(key), prior(SuperRand()), sz(1), minn(key){}
};

typedef Node* PNode;

inline int get_sz(PNode root) {
    if (!root)return 0;
    return root->sz;
}

inline int get_minn(PNode root) {
    if (!root)return INF;
    return root->minn;
}

inline void update(PNode root) {
    root->sz = get_sz(root->l) + get_sz(root->r) + 1;
    root->minn = min({ get_minn(root->l), get_minn(root->r), root->key });
}

void split(PNode root, PNode& l, PNode& r, int k) {
    if (!root) {
        l = r = nullptr;
        return;
    }
    if (get_sz(root->l) >= k) {
        split(root->l, l, root->l, k);
        r = root;
        update(r);
    }
    else {
        split(root->r, root->r, r, k - get_sz(root->l) - 1);
        l = root;
        update(l);
    }
}

void merge(PNode& root, PNode l, PNode r) {
    if (!l || !r) {
        if (!l)root = r;
        else root = l;
        return;
    }
    if (l->prior > r->prior) {
        merge(l->r, l->r, r);
        root = l;
    }
    else {
        merge(r->l, l, r->l);
        root = r;
    }
    update(root);
}

PNode tmp1, tmp2, tmp3;

void insert(PNode& root, int pos, int val) {
    split(root, tmp1, tmp2, pos);
    merge(tmp1, tmp1, new Node(val));
    merge(root, tmp1, tmp2);
}

void erase(PNode& root, int pos) {
    split(root, tmp1, tmp3, pos);
    split(tmp1, tmp1, tmp2, pos - 1);
    merge(root, tmp1, tmp3);
}

void print(PNode root) {
    if (!root)return;
    print(root->l);
    cout << root->key << "\n";
    print(root->r);
}

int ask(PNode root, int askl, int askr, int l = 0){
    if (!root)return INF;
    int r = l + root->sz;
    if (l >= askr || r <= askl) {
        return INF;
    }
    if (l >= askl && r <= askr) {
        return root->minn;
    }
    int ansl = ask(root->l, askl, askr, l);
    int ansr = ask(root->r, askl, askr, l + get_sz(root->l) + 1);
    int pos = l + get_sz(root->l);
    int ansroot = INF;
    if (pos >= askl && pos < askr) {
        ansroot = root->key;
    }
    return min({ ansroot, ansl, ansr });
}

void solve() {
    int n;
    cin >> n;
    PNode root = nullptr;
    while (n--) {
        char type;
        cin >> type;
        if (type == '+') {
            int pos, val;
            cin >> pos >> val;
            insert(root, pos, val);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << ask(root, l - 1, r) << "\n";
        }
    }
}


signed main() {
    //freopen("rmq.in", "r", stdin);
    //freopen("rmq.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed;
    cout.precision(30);
    int t = 1;
    //cin >> t;
    while (t--)
        solve();
    //   system("pause");
}