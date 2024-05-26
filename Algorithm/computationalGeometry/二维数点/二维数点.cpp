// Luogu P2163
// 时间复杂度 nlogn
// 给定平面上n个点，m次查询，查询一个矩阵内有多少点
// 由于坐标范围很大，不能直接用前缀和
#include <algorithm>
#include <iostream>

int const MAXN = 500005;

struct Point {
    int x, y;
    int tag;  // 用于区分实际的点和查询时的虚点

    bool operator<(Point const& p) {
        if (x != p.x) return x < p.x;
        if (y != p.y) return y < p.y;
        return tag < p.tag;
    }
} pts[MAXN * 5];  // 实点和查询矩阵的点都放在这里面

int b[MAXN * 5];
int bit[MAXN];
int ans[MAXN][5];
int tot[MAXN];

inline int lowbit(int n) { return n & (-n); }

void update(int p, int k, int n) {
    for (; p <= n; p += lowbit(p)) {
        bit[p] += k;
    }
}

int query(int p) {
    int ret = 0;
    for (; p; p -= lowbit(p)) {
        ret += bit[p];
    }
    return ret;
}

inline int lsh(int x, int cnt) {  // 离散化函数
    return std::lower_bound(b + 1, b + cnt + 1, x) - b;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;  // 点数，查询数

    for (int i = 1; i <= n; i++) {
        std::cin >> pts[i].x >> pts[i].y;  // 所有实点的坐标
        pts[i].tag = 0;
    }

    for (int i = 1; i <= m; i++) {
        int x1, x2, y1, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;  // 查询的长方形的左下角和右上角

        pts[++n].x = x1 - 1, pts[n].y = y1 - 1, pts[n].tag = i;
        pts[++n].x = x2, pts[n].y = y2, pts[n].tag = i;
        pts[++n].x = x2, pts[n].y = y1 - 1, pts[n].tag = i;
        pts[++n].x = x1 - 1, pts[n].y = y2, pts[n].tag = i;
    }

    std::sort(pts + 1, pts + 1 + n);
    for (int i = 1; i <= n; i++) b[i] = pts[i].y;
    std::sort(b + 1, b + 1 + n);
    int cnt = std::unique(b + 1, b + 1 + n) - b - 1;  // 把所有y离散化

    for (int i = 1; i <= n; i++) {
        if (pts[i].tag) {
            ans[pts[i].tag][++tot[pts[i].tag]] = query(lsh(pts[i].y, cnt));
        } else {
            update(lsh(pts[i].y, cnt), 1, cnt);
        }
    }

    for (int i = 1; i <= m; i++) {
        std::cout << ans[i][4] - ans[i][3] - ans[i][2] + ans[i][1] << "\n";
    }

    return 0;
}
