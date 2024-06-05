#include <iostream>

#define SAFE '.'
#define MINE '*'
#define MAX_SIZE 100

class Minesweeper {
    char field[MAX_SIZE][MAX_SIZE];
    size_t row, col;
public:
    Minesweeper() : row(0), col(0) {};
    Minesweeper(int _m, int _n) : col(_n), row(_m) {};

    void setRow(int _m) {
        row = (_m > 0 && _m < MAX_SIZE) ? _m : throw std::invalid_argument("");
    }

    void setCol(int _m) {
        col = (_m > 0 && _m < MAX_SIZE) ? _m : throw std::invalid_argument("");
    }

    void inputField() {
        size_t i, j;
        for (i = 0; i < row; ++i) 
            for(j = 0; j < col; ++j) 
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

    int lookAround(int y,  int x) {
        int i, j;
        int count = 0;

        if (!x && !y) 
            count = (field[y][x + 1] == MINE) + (field[y + 1][x] == MINE) + (field[y + 1][x + 1] == MINE);
        else if(!x && y + 1 == row) 
            count = (field[y][x + 1] == MINE) + (field[y - 1][x] == MINE) + (field[y - 1][x + 1] == MINE);
        else if (x + 1 == col && y + 1 == row) 
            count = (field[y - 1][x] == MINE) + (field[y - 1][x - 1] == MINE) + (field[y][x - 1] == MINE);
        else if (x + 1 == col && !y)
            count = (field[y][x - 1] == MINE) + (field[y + 1][x - 1] == MINE) + (field[y + 1][x] == MINE);
        else 
            for (i = y - !(!y); i < y + 1 + (y + 1 != row); ++i) 
                for (j = x - !(!x); j < x + 1 + (x + 1 != col); ++j)
                    count += (field[i][j] == MINE);
        return count;
    }


};

int main() {
    Minesweeper sweeper;
    int n, m, nCase = 0;
    while (std::cin >> m >> n && (m + n)) {
        sweeper = Minesweeper(m, n);
        sweeper.inputField();
        sweeper.sweepField(&nCase);
    }
    return 0;
}
