// UOJ179 线性规划

#include <cstring>
#include <iostream>

int const MAXN = 31;
using DB = long double;
#define double DB

class LP {
   public:
    int n, m;  // 变量个数，约束个数
    double cons
        [MAXN]
        [MAXN];  // 0维为c_i,
                 // 1~m维为约束条件，共m个，每个长度为n+1，第0维为b，1~n维为a_ij
    double const EPS = 1e-8;
    int idx[MAXN * 2];

    bool solve() {
        std::memset(idx, 0, sizeof(idx));
        for (int i = 1; i <= n; i++) idx[i] = i;
        for (;;) {
            int l = 0, e = 0;  // 换入、换出变量
            for (int i = 1; i <= m; i++) {
                if (cons[i][0] < -EPS && (!l || (rand() & 1)))
                    l = i;  // rand可以提升运行效率，避免TLE
            }
            if (!l) return Simplex();
            for (int j = 1; j <= n; j++) {
                if (cons[l][j] < -EPS && (!e || (rand() & 1))) e = j;
            }
            if (!e) {
                std::cout << "Infeasible\n";  // 无解
                return false;
            }
            Pivot(l, e);
        }
    }

    bool Simplex() {
        for (;;) {
            int l = 0, e = 0;
            for (int j = 1; j <= n; j++) {
                if (cons[0][j] > EPS) {
                    e = j;
                    break;
                }
            }
            if (!e) return true;
            double minv = 1e18;
            for (int i = 1; i <= m; i++) {
                if (cons[i][e] > EPS && cons[i][0] / cons[i][e] < minv) {
                    minv = cons[i][0] / cons[i][e];
                    l = i;
                }
            }
            if (!l) {
                std::cout << "Unbounded\n";
                return false;
            }
            Pivot(l, e);
        }
    }

    void Pivot(int l, int e) {
        std::swap(idx[n + l], idx[e]);
        double t = cons[l][e];
        cons[l][e] = 1.0;
        for (int j = 0; j <= n; j++) cons[l][j] /= t;
        for (int i = 0; i <= m; i++) {
            if (i != l && std::abs(cons[i][e]) > EPS) {
                t = cons[i][e];
                cons[i][e] = 0.0;
                for (int j = 0; j <= n; j++) {
                    cons[i][j] -= t * cons[l][j];
                }
            }
        }
    }
};

double ans[31];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    LP lp;
    std::cin >> lp.n >> lp.m;
    int type;
    std::cin >> type;

    for (int i = 1; i <= lp.n; i++) {
        std::cin >> lp.cons[0][i];
    }

    for (int i = 1; i <= lp.m; i++) {
        for (int j = 1; j <= lp.n; j++) {
            std::cin >> lp.cons[i][j];
        }
        std::cin >> lp.cons[i][0];
    }

    std::cout << std::fixed;
    std::cout.precision(10);

    if (lp.solve()) {
        std::cout << -lp.cons[0][0] << "\n";
        if (type) {
            for (int i = 1; i <= lp.m; i++)
                ans[lp.idx[i + lp.n]] = lp.cons[i][0];
            for (int i = 1; i <= lp.n; i++) std::cout << ans[i] << " ";
        }
    }

    return 0;
}
