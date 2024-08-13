// https://codeforces.com/gym/102428/problem/D
// Given a set of stars, find a direction on which their brightness is non-increasing.
// Use complex to represent 2d points (vectors).
#include <bits/stdc++.h>
using namespace std;

using pt = complex<int>;

bool above(pt p) {
    return imag(p) > 0 || (imag(p) == 0 && real(p) > 0);
}
int dot(pt a, pt b) { // dot product
    return real(conj(a)*b);
}
int cross(pt a, pt b) { // cross product
    return imag(conj(a)*b);
}

struct Star {
    pt p;
    int b;
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<Star> star(n);
    for (auto &s: star) {
        int x, y;
        cin >> x >> y >> s.b;
        s.p = {x, y};
    }

    vector<pt> dirs;
    for (auto &s: star) {
        for (auto &t: star) {
            if (s.b < t.b) dirs.push_back(s.p-t.p);
        }
    }
    if (dirs.size() < 2) {
        cout << "Y\n";
        return 0;
    }
    sort(begin(dirs), end(dirs), [&](pt a, pt b) {
        if (above(a) != above(b)) return above(a);
        return cross(a, b) > 0;
    });
    dirs.push_back(dirs.front());

    for (auto it = dirs.begin(); next(it) != dirs.end(); ++it) {
        pt p = *it, q = *next(it);
        // cout << p << ' ' << q << endl;
        int c = cross(p, q);
        if (c < 0 || (c == 0 && dot(p, q) < 0)) { // if p -> q is >= π
            cout << "Y\n";
            return 0;
        }
    }
    cout << "N\n";

    return 0;
}
