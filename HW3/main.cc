#include <iostream>
using namespace std;

class Game {
    static constexpr int size = 100;

    int board[size][size] = {0};
    int m, n;

    bool Paint(int id) {
        return false;
    }

public:
    Game(int m, int n): m(m), n(n) {}

    bool tour() {
        if (m > size || n > size) return false;

        // Both m and n are odd.
        if (m & n & 1) return false;

        return Paint(0);
    }

    friend ostream& operator << (ostream& os, const Game &g);
};

ostream& operator << (ostream& os, const Game &g) {
    for (int i = 0; i < g.m; i++) {
        for (int j = 0; j < g.n; j++) {
            os << g.board[i][j] << '\t';
        }
        os << endl;
    }
    return os;
}

int main() {
    return 0;
}