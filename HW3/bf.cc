#include <iostream>
#include <vector>
using namespace std;

class Pos {
public:
    int x, y;
    Pos() = default;
    Pos(int x, int y): x(x), y(y) {}
};

class Game {
    static constexpr int size = 16;
    static constexpr int start_x = 0;
    static constexpr int start_y = 0;

    Pos knight = Pos(start_x, start_y);
    int board[size][size] = {0};
    int m, n;

    bool can_move(Pos pos) const {
        if (0 <= pos.x && pos.x < m && 0 <= pos.y && pos.y < n) {
            if (board[pos.x][pos.y] == 0) {
                return true;
            }
        }
        return false;
    }

    vector<Pos> move() const {
        vector<Pos> result;
        Pos pos;
        pos.x = knight.x + 4;
        pos.y = knight.y + 3;
        if (can_move(pos)) {
            result.push_back(pos);
        }
        pos.x = knight.x + 3;
        pos.y = knight.y + 4;
        if (can_move(pos)) {
            result.push_back(pos);
        }
        pos.x = knight.x + 4;
        pos.y = knight.y - 3;
        if (can_move(pos)) {
            result.push_back(pos);
        }
        pos.x = knight.x + 3;
        pos.y = knight.y - 4;
        if (can_move(pos)) {
            result.push_back(pos);
        }
        pos.x = knight.x - 4;
        pos.y = knight.y + 3;
        if (can_move(pos)) {
            result.push_back(pos);
        }
        pos.x = knight.x - 3;
        pos.y = knight.y + 4;
        if (can_move(pos)) {
            result.push_back(pos);
        }
        pos.x = knight.x - 4;
        pos.y = knight.y - 3;
        if (can_move(pos)) {
            result.push_back(pos);
        }
        pos.x = knight.x - 3;
        pos.y = knight.y - 4;
        if (can_move(pos)) {
            result.push_back(pos);
        }
        return result;
    }

    bool DFS(int depth) {
        if (depth == 0) {
            if (knight.x == start_x && knight.y == start_y) {
                return true;
            }
            return false;
        }

        auto movelist = move();
        for (auto pos : movelist) {
            knight = pos;
            board[pos.x][pos.y] = depth;
            bool value = DFS(depth-1);
            if (value) {
                return true;
            }
            board[pos.x][pos.y] = 0;
        }
        return false;
    }

public:
    Game(int m, int n): m(m), n(n) {}

    bool tour() {
        int depth = m*n;
        return DFS(depth);
    }
};

int main() {
    int m, n;
    while (cin >> m >> n) {
        Game g(m, n);
        cout << g.tour() << endl;
    }
    return 0;
}