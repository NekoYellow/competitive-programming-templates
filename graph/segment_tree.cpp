/* poj 3468 "A Simple Problem with Integers" */
#include <iostream>
using namespace std;
typedef long long ll;
const char nl = '\n';
const int N = 1e5+10;

// segment tree allowing interval modifying
ll sum[N<<2], add[N<<2]; // 4x space
void push_up(int rt) { // update upwards
    sum[rt] = sum[rt<<1] + sum[rt<<1|1]; // rt*2, rt*2+1
}
void push_down(int rt, int m) { // update children of rt  m: number of elements belonging to node rt
    if (add[rt]) {
        add[rt<<1] += add[rt];
        add[rt<<1|1] += add[rt];
        sum[rt<<1] += (m-(m>>1))*add[rt];
        sum[rt<<1|1] += (m>>1)*add[rt];
        add[rt] = 0; // cancel tagging
    }
}
// left subtree
#define ltree l, mid, rt<<1
// right subtree
#define rtree mid+1, r, rt<<1|1
void build(int l, int r, int rt) { // build the segment tree using a full bst
    add[rt] = 0;
    if (l == r) { // leaf, assign value
        cin >> sum[rt];
        return;
    }
    int mid = l + ((r-l)>>1);
    build(ltree); build(rtree);
    push_up(rt); // update interval sum upwards
}
void update(int a, int b, ll c, int l, int r, int rt) {
    if (a <= l && b >= r) {
        sum[rt] += (r-l+1)*c;
        add[rt] += c; // tagging
        return;
    }
    push_down(rt, r-l+1); // updating downwards
    int mid = l + ((r-l)>>1);
    if (a <= mid) update(a, b, c, ltree); // require updating in the left subtree
    if (b > mid)  update(a, b, c, rtree); // require updating in the right subtree
    push_up(rt);
}
ll query(int a, int b, int l, int r, int rt) {
    if (a <= l && b >= r) return sum[rt]; // lazy is satisfied, return directly
    push_down(rt, r-l+1); // cannot lazy anymore
    int mid = l + ((r-l)>>1);
    ll ans = 0;
    if (a <= mid) ans += query(a, b, ltree);
    if (b > mid)  ans += query(a, b, rtree);
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    build(1, n, 1);
    while (m--) {
        char s;
        cin >> s;
        int a, b; ll c;
        if (s == 'C') {
            cin >> a >> b >> c;
            update(a, b, c, 1, n, 1);
        } else {
            cin >> a >> b;
            cout << query(a, b, 1, n, 1) << nl;
        }
    }
    return 0;
}
