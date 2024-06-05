#include <iostream>
#include <vector>

class Grid {
    std::vector<std::vector<char>> g;
    int row, col;
public:
    Grid() : row(0), col(0) {}
    Grid(int _m, int _n) : row(_m), col(_n) {
        g.resize(row, std::vector<char>(col));
    }

    void setRow(int m) {
        row = m;
        g.resize(row, std::vector<char>(col));
    }

    void setCol(int n) {
        col = n;
        for (auto &r: g)
            r.resize(col);
    }

    void inputGrid() {
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                std::cin >> g[i][j];
    }

    bool isValidSquare(int r, int c, int sideLength) {
        char ch = g[r][c];
        int half = sideLength / 2;
        for (int i = r - half; i <= r + half; ++i) {
            for (int j = c - half; j <= c + half; ++j) {
                if (g[i][j] != ch) return false;
            }
        }
        return true;
    }

    int getSquareDim() {
        int r, c;
        std::cin >> r >> c;
        
        int maxLength = 1;
        int sideLength = 1;

        while (true) {
            int half = sideLength / 2;
            if (r - half < 0 || r + half >= row || c - half < 0 || c + half >= col) break;
            if (!isValidSquare(r, c, sideLength)) break;

            maxLength = sideLength;
            sideLength += 2;
        }

        return maxLength;
    }
};

int main() {
    int testCases, m, n, q;
    std::cin >> testCases;

    while (testCases--) {
        std::cin >> m >> n >> q;
        Grid g(m, n);
        g.inputGrid();

        std::cout << m << " " << n << " " << q << std::endl;

        while (q--) {
            std::cout << g.getSquareDim() << std::endl;
        }
    }

    return 0;
}
