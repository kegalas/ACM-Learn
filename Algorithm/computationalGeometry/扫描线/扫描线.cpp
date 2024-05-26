// Luogu P5490
// 复杂度 nlogn
// 求平面所有平行于坐标轴的矩形的面积重叠和
#include <algorithm>
#include <iostream>

using ll = long long;

int const MAXN = 2000005;

struct Line {
    ll l, r, h;
    int tag;
    Line() {}
    Line(ll l, ll r, ll h, int tag) : l(l), r(r), h(h), tag(tag) {}

    bool operator<(Line const& rhs) const { return h < rhs.h; }
} line[MAXN * 2];

ll st[MAXN * 4 +
      2];  // 对于一颗线段树，n个数所组成的树最多有4n-5个节点，开大了一点
ll posX[MAXN * 2];
ll len[MAXN * 4 + 2];

void update(int l, int r, int s, int t, int p, ll c) {  // c表示加减的数值
    if (posX[t + 1] <= l || r <= posX[s]) return;
    if (l <= posX[s] && posX[t + 1] <= r) {
        st[p] += c;
        if (st[p]) {
            len[p] = posX[t + 1] - posX[s];
        } else {
            len[p] = len[p * 2] + len[p * 2 + 1];
        }

        return;
    }

    int m = s + ((t - s) >> 1);
    if (l <= posX[m]) update(l, r, s, m, p * 2, c);
    if (r > posX[m]) update(l, r, m + 1, t, p * 2 + 1, c);
    if (st[p]) {
        len[p] = posX[t + 1] - posX[s];
    } else {
        len[p] = len[p * 2] + len[p * 2 + 1];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;  // 矩形个数
    ll x1, x2, y1, y2;

    for (int i = 1; i <= n; i++) {
        std::cin >> x1 >> y1 >> x2 >> y2;  // 输入每个矩形的左下角和右上角
        posX[2 * i - 1] = x1, posX[2 * i] = x2;
        line[2 * i - 1] = Line(x1, x2, y1, 1),
                     line[2 * i] = Line(x1, x2, y2, -1);
    }

    n *= 2;  // 方便起见

    std::sort(line + 1, line + n + 1);
    std::sort(posX + 1, posX + n + 1);

    int sumSeg =
        std::unique(posX + 1, posX + 1 + n) - posX - 1 - 1;  // 去重求出线段总数
    ll ans = 0;

    for (int i = 1; i < n; i++) {  // 最后一条边不用管
        update(line[i].l, line[i].r, 1, sumSeg, 1, line[i].tag);
        ans += len[1] * (line[i + 1].h - line[i].h);
    }

    std::cout << ans << "\n";  // 输出矩形的并集的总面积

    return 0;
}
