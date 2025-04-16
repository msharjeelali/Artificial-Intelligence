#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int boardSize = 8;
const int totalMoves = 8;

// Function to count valid onward moves (Warnsdorff’s Heuristic)
int heuristic(vector<vector<int>> board, int x, int y) {

    int moves[totalMoves][2] = { {-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {1, -2}, {-1, 2}, {1, 2} };

    int count = 0;
    for (int i = 0; i < totalMoves; i++) {
        int newX = x + moves[i][0];
        int newY = y + moves[i][1];
        if (newX >= 0 && newX < boardSize && newY >= 0 && newY < boardSize && board[newX][newY] == -1) {
            count++;
        }
    }
    return count;
}

// Struct to store board state
struct State {
    int x = 0, y = 0;
    int step = 0;
    int heu = 0;
    int f = 0;
    vector<vector<int>> board;

    State(int _x, int _y, int _step, vector<vector<int>> _board){
        x = _x;
        y = _y;
        step = _step;
        board = move(_board);
        heu = heuristic(board, x, y);
        f = step + heu;
    }

    bool operator>(const State& other) const {
        return f > other.f;
    }
};

// Function to print board
void printBoard(const vector<vector<int>>& board) {
    for (int i = 0; i< board.size();i++) {
        for (int j = 0;j<board[i].size();j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
}

// A* Algorithm for Knight’s Tour
bool aStar(vector<vector<int>> board, int startX, int startY) {

    board[startX][startY] = 1;

    int moves[totalMoves][2] = {
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1},
        {-1, -2}, {1, -2}, {-1, 2}, {1, 2}
    };

    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push(State(startX, startY, 1, board));

    int states = 1;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (current.step == boardSize * boardSize) {
            cout << "Moved to: ( " << current.x << " , " << current.y << " ) " << endl;
            cout << "Step: " << current.step << endl;
            printBoard(current.board);
            cout << "Knights Tour Completed:\n";
            return true;
        }

        cout << "Moved to: ( " << current.x << " , " << current.y << " ) " << endl;
        cout << "Step: " << current.step << endl;
        printBoard(current.board);
        cout << endl;

        vector<pair<int, pair<int, int>>> nextMoves;
        for (int i = 0; i < totalMoves; i++) {
            int newX = current.x + moves[i][0];
            int newY = current.y + moves[i][1];

            if (newX >= 0 && newX < boardSize && newY >= 0 && newY < boardSize &&
                current.board[newX][newY] == -1) {
                int heuristicValue = heuristic(current.board, newX, newY);
                nextMoves.push_back({ heuristicValue, {newX, newY} });
            }
        }

        // Sort moves based on heuristic (Warnsdorff’s Rule)
        sort(nextMoves.begin(), nextMoves.end());

        // Expand the best moves
        for (auto& ite : nextMoves) {
            int newX = ite.second.first, newY = ite.second.second;
            vector<vector<int>> newBoard = current.board;
            newBoard[newX][newY] = current.step + 1;
            pq.push(State(newX, newY, current.step + 1, newBoard));
            break;
        }
    }

    cout << "No solution found.\n";
    return false;
}

int main() {
    vector<vector<int>> board(boardSize, vector<int>(boardSize, -1));
    int startX = 0, startY = 0;
    
    aStar(board, startX, startY);
    
    return 0;
}
