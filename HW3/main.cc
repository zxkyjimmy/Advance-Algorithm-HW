#include <iostream>
#include <ctime>
using namespace std;

class Game {
    static constexpr int size = 100;

    int board[size][size] = {0};
    int m, n;

    int Paint2n(int id, int base) {
        if (base == m) return id;
        board[base][0] = id++;
        board[base+1][0] = id++;
        id = Paint2n(id, base+2);
        for (int i = 1; i < n; i++) {
            board[base+1][i] = id++;
        }
        for (int i = n-1; i >= 1; i--) {
            board[base][i] = id++;
        }
        return id;
    }

    int Paintm2(int id, int base) {
        if (base == n) return id;
        board[0][base] = id++;
        board[0][base+1] = id++;
        id = Paintm2(id, base+2);
        for (int i = 1; i < m; i++) {
            board[i][base+1] = id++;
        }
        for (int i = m-1; i >= 1; i--) {
            board[i][base] = id++;
        }
        return id;
    }

    bool both_odd() const {
        return n & m & 1;
    }

    void Paint() {
        if ((m & 1) == 0) {
            Paint2n(1, 0);
        } else if ((n & 1) == 0) {
            Paintm2(1, 0);
        }
    }

public:
    Game(int m, int n): m(m), n(n) {}

    bool tour() {
        if (m > size || n > size) return false;
        if (m < 2 || n < 2) return false;
        if (both_odd()) return false;

        Paint();

        return true;
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
    int m, n;
    time_t start, stop;
    while (true) {
        cout << "Hint: if m = 0 or n = 0, then program quit." << endl;
        cout << "input m --->";
        cin >> m;
        if (m == 0) break;
        cout << "input n --->";
        cin >> n;
        if (n == 0) break;
        cout << endl;
        Game g(m, n);
        start = clock();
        if (g.tour()) {
            cout << g << endl;
        } else {
            cout << "No close path." << endl;
        }
        stop = clock();
        cout << "Use Time: " << (stop-start)*1000/CLOCKS_PER_SEC << "ms." << endl << endl;
    }
    return 0;
}