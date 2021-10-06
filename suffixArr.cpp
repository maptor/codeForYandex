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
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <random>
#include <cstdio>
#include <string>
#include <numeric>
#include <cctype>
#include <cassert>

#define double long double
#define eb emplace_back
#define rs resize
#define ld long double
#define vi vector<int>
#define vpii vector<pair<int, int>>
#define ull unsigned long long


using namespace std;



void radix_sort(vector<pair<pair<int, int>, int>>& a) {
    int n = a.size();
    {
        vi cnt(n);
        for (auto x : a) {
            cnt[x.first.second]++;
        }
        vector<pair<pair<int, int>, int>> a_new(n);
        vi pos(n);
        for (int i = 1; i < n; i++) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }

        for (auto x : a) {
            int i = x.first.second;
            a_new[pos[i]] = x;
            pos[i]++;
        }
        a = a_new;
    }
    {
        vi cnt(n);
        for (auto x : a) {
            cnt[x.first.first]++;
        }
        vector<pair<pair<int, int>, int>> a_new(n);
        vi pos(n);
        for (int i = 1; i < n; i++) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }

        for (auto x : a) {
            int i = x.first.first;
            a_new[pos[i]] = x;
            pos[i]++;
        }
        a = a_new;
    }
}



void solve() {
    string s;
    cin >> s;
    s += "$";

    int n = s.size();
    vi p(n), c(n);
    {
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = { s[i], i };
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            p[i] = a[i].second;
        }
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first)c[p[i]] = c[p[i - 1]];
            else c[p[i]] = c[p[i - 1]] + 1;
        }
    }

    int k = 0;
    while ((1 << k) < n) {
        vector<pair<pair<int, int>, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = { {c[i], c[(i + (1 << k)) % n]}, i };
        }
        radix_sort(a);

        for (int i = 0; i < n; i++) {
            p[i] = a[i].second;
        }
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first)c[p[i]] = c[p[i - 1]];
            else c[p[i]] = c[p[i - 1]] + 1;
        }
        k++;
    }

    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        int l = 0, r = n;
        while (r - l > 1) {
            int m = (l + r) / 2;
            bool good = true;
            for (int i = 0, j = p[m]; i < t.size(); i++, j++) {
                if (t[i] > s[j])break;
                if (s[j] > t[i]) {
                    good = false;
                    break;
                }
            }
            //cout << p[m] << ' ' << good << ' ' << m << " " << l << ' ' << r << "\n";
            if (good)l = m;
            else r = m;
        }
        bool good = true;
        for (int i = 0, j = p[l]; i < t.size(); i++, j++) {
            if (s[j] != t[i]) {
                good = false;
                break;
            }
        }

        if (!good) {
            cout << "0\n";
            continue;
        }

        int l1 = -1, r1 = n;
        while (r1 - l1 > 1) {
            int m = (l1 + r1) / 2;
            bool good1 = true, eq = false;
            for (int i = 0, j = p[m]; i < t.size(); i++, j++) {
                if (t[i] > s[j])break;
                if (s[j] > t[i]) {
                    good1 = false;
                    break;
                }
                if (i + 1 == t.size())eq = true;
            }
            //cout << p[m] << ' ' << good << ' ' << m << " " << l << ' ' << r << "\n";
            if (eq)r1 = m;
            else if (good1)l1 = m;
            else r1 = m;
        }
        cout << l - r1 + 1 << "\n";
    }
}


signed main() {
    // freopen("‪", "r", stdin);
    //freopen("C:\\Users\\Asus\\Desktop\\input.txt", "w", stdout);
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