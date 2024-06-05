#include <iostream>
#include <stdexcept>
#include <vector>

#define SAFE '.'
#define MINE '*'
#define MAX_SIZE 100

class Minesweeper {
    std::vector<std::vector<char>> field;
    size_t row, col;
public:
    Minesweeper() : row(0), col(0) {};
    Minesweeper(int _m, int _n) : col(_n), row(_m) {
        field.resize(row, std::vector<char>(col));
    };

    void setRow(int _m) {
        row = (_m > 0 && _m < MAX_SIZE) ? _m : throw std::invalid_argument("");
        field.resize(row, std::vector<char>(col));
    }

    void setCol(int _m) {
        col = (_m > 0 && _m < MAX_SIZE) ? _m : throw std::invalid_argument("");
        for(auto& r : field)
            r.resize(col);
    }

    void inputField() {
        for (size_t i = 0; i < row; ++i)
            for (size_t j = 0; j < col; ++j)
                std::cin >> field[i][j];
    }

    void sweepField(int* nCase) {
        ++(*nCase);
        if (*nCase > 1) {
            std::cout << std::endl;
        }
        std::cout << "Field #" << *nCase << ":" << std::endl;
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                if (field[i][j] != MINE) {
                    std::cout << lookAround(i, j);
                } else {
                    std::cout << MINE;
                }
            }
            std::cout << std::endl;
        }
    }

    int lookAround(int y, int x) {
        int count = 0;
        for (int i = y - 1; i <= y + 1; ++i) {
            for (int j = x - 1; j <= x + 1; ++j) {
                if (i >= 0 && i < row && j >= 0 && j < col && field[i][j] == MINE) {
                    count++;
                }
            }
        }
        return count;
    }
};

int main() {
    Minesweeper sweeper;
    int n, m, nCase = 0;
    while (std::cin >> n >> m && (n + m)) {
        sweeper = Minesweeper(n, m);
        sweeper.inputField();
        sweeper.sweepField(&nCase);
    }
    return 0;
}
