#include <iostream>
#include <vector>

using namespace std;

const int N = 10;
char grid[N][N] = {
    {'.', '.', '.', '.', '.', '.', '.', 'T', '.', '.'},
    {'.', '.', 'T', '.', '.', '.', '.', '.', '.', 'T'},
    {'.', '.', '.', '.', '.', 'T', '.', '.', '.', '.'},
    {'T', '.', '.', '.', 'T', '.', '.', 'T', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', 'T', '.', '.'},
    {'.', 'T', 'T', '.', '.', 'T', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', 'T', '.'},
    {'.', '.', '.', '.', 'T', '.', '.', 'T', '.', 'T'},
    {'.', '.', 'T', '.', 'T', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', 'T', '.', '.', '.', '.', '.'}
};

int rowTents[N] = {2, 1, 2, 2, 1, 2, 2, 1, 4, 1};
int colTents[N] = {1, 2, 1, 3, 1, 2, 2, 2, 1, 3};

bool isSafe(int r, int c, const vector<vector<char>>& board) {
    if (r < 0 || c < 0 || r >= N || c >= N) return false;
    if (board[r][c] != '.') return false;

    for (int dr = -1; dr <= 1; ++dr)
        for (int dc = -1; dc <= 1; ++dc)
            if (dr != 0 || dc != 0) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nc >= 0 && nr < N && nc < N && board[nr][nc] == 'A')
                    return false;
            }

    return true;
}

bool countCheck(const vector<vector<char>>& board) {
    for (int r = 0; r < N; ++r) {
        int cnt = 0;
        for (int c = 0; c < N; ++c)
            if (board[r][c] == 'A') cnt++;

        if (rowTents[r] > 0 && cnt > rowTents[r])
            return false;
    }

    for (int c = 0; c < N; ++c) {
        int cnt = 0;
        for (int r = 0; r < N; ++r)
            if (board[r][c] == 'A') cnt++;

        if (colTents[c] > 0 && cnt > colTents[c])
            return false;
    }

    return true;
}


bool solve(size_t index, vector<pair<int, int>>& trees, vector<vector<char>>& board) {
    if (index == trees.size()) return true;

    int r = trees[index].first;
    int c = trees[index].second;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d], nc = c + dc[d];
        if (isSafe(nr, nc, board)) {
            board[nr][nc] = 'A';
            if (countCheck(board) && solve(index + 1, trees, board))
                return true;
            board[nr][nc] = '.';
        }
    }

    return false;
}

int main() {
    vector<vector<char>> board(N, vector<char>(N));
    vector<pair<int, int>> trees;

    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c) {
            board[r][c] = grid[r][c];
            if (grid[r][c] == 'T')
                trees.emplace_back(r, c);
        }

    if (solve(0, trees, board)) {
        cout << "Розв'язок:\n";
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c)
                cout << board[r][c] << ' ';
            cout << endl;
        }
    } else {
        cout << "Розв'язок не знайдено.\n";
    }

    return 0;
}
