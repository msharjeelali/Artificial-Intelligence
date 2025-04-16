#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int boardSize = 8;
const int totalMoves = 8;
int states = 1;

// Function to print the board
void printBoard(int board[boardSize][boardSize]) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
}

// Function to count valid onward moves (Warnsdorff’s Heuristic)
int heuristic(int board[boardSize][boardSize], int x, int y) {

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

// Recursive Best First Search
bool BestFirstSearch(int board[boardSize][boardSize], int x, int y, int step) {
    
    cout << "State: " << states++ << endl;

    // Goal state reached
    if (step == boardSize * boardSize) {
        return true; 
    }

    // Store possible moves and their heuristic values
    vector<pair<int, pair<int, int>>> nextMoves;

    int moves[totalMoves][2] = {
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1},
        {-1, -2}, {1, -2}, {-1, 2}, {1, 2}
    };

    for (int i = 0; i < totalMoves; i++) {
        int newX = x + moves[i][0];
        int newY = y + moves[i][1];

        if (newX >= 0 && newX < boardSize && newY >= 0 && newY < boardSize && board[newX][newY] == -1) {
            int heuristicValue = heuristic(board, newX, newY);
            nextMoves.push_back({ heuristicValue, {newX, newY} });
        }
    }

    // Sort moves based on Warnsdorff’s heuristic (ascending order)
    sort(nextMoves.begin(), nextMoves.end());

    // Try each move in sorted order
    for (auto& move : nextMoves) {
        int newX = move.second.first;
        int newY = move.second.second;

        board[newX][newY] = step + 1;

        // Solution found
        if (BestFirstSearch(board, newX, newY, step + 1)) {
            return true; 
        }

        // Backtrack
        board[newX][newY] = -1;
    }

    // No valid moves found
    return false; 
}

// Struct to store board state
struct State {
    int x = 0, y = 0;
    int step = 0;
    int heu = 0;
    int board[boardSize][boardSize];

    State(int x, int y, int step, int board[boardSize][boardSize]) {
        this->x = x;
        this->y = y;
        this->step = step;
        
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                this->board[i][j] = board[i][j];
            }
        }

        this->heu = heuristic(this->board, this->x, this->y);
    }

    State(const State& other) {
        this->x = other.x;
        this->y = other.y;
        this->step = other.step;
        this->heu = other.heu;

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                this->board[i][j] = other.board[i][j];
            }
        }
    }

    bool operator>(const State& other) const {
        return heu > other.heu;
    }

    void calHeu() {
        this->heu = heuristic(board, x, y);
    }
};

bool BestFirstSearch(int board[boardSize][boardSize], int startX, int startY) {
    int moves[totalMoves][2] = {
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1},
        {-1, -2}, {1, -2}, {-1, 2}, {1, 2}
    };

    // Priority queue with min-heap behavior (smallest heuristic first)
    priority_queue<State, vector<State>, greater<State>> pq;

    // Push initial state
    pq.push(State(startX, startY, 1, board));

    int states = 1;

    while (!pq.empty()) {
        // Get state with best heuristic
        State copy(pq.top());
        pq.pop();
        cout << "State: " << states++ << endl;
        cout << "Moved to: ( " << copy.x << " , " << copy.y << " ) " << endl;

        // Goal state check
        if (copy.step == boardSize * boardSize) {
            printBoard(copy.board);
            cout << "Knights Tour Found";
            return true;
        }
        printBoard(copy.board);

        // Store valid next moves
        vector<pair<int, pair<int, int>>> nextMoves;
        for (int i = 0; i < totalMoves; i++) {
            int newX = copy.x + moves[i][0];
            int newY = copy.y + moves[i][1];

            if (newX >= 0 && newX < boardSize && newY >= 0 && newY < boardSize &&
                copy.board[newX][newY] == -1) {
                int heuristicValue = heuristic(copy.board, newX, newY);
                nextMoves.push_back({ heuristicValue, {newX, newY} });
            }
        }

        // Sort moves based on heuristic (smallest first)
        sort(nextMoves.begin(), nextMoves.end());

        // Expand the best moves first
        for (auto& move : nextMoves) {
            int newX = move.second.first;
            int newY = move.second.second;

            State child(copy);
            child.x = newX;
            child.y = newY;
            child.step = copy.step + 1;
            child.board[newX][newY] = child.step; 
            child.calHeu();

            // Push to priority queue
            pq.push(child);
            break;
        }
    }

    cout << "No solution found.\n";
    return false;
}


int main() {
    int board[boardSize][boardSize];

    // Initialize board with -1
    for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
            board[i][j] = -1;

    int startX = 0, startY = 0;
    board[startX][startY] = 1;

    if (BestFirstSearch(board, startX, startY)) {
        
    }
    else {
        cout << "No solution found." << endl;
    }

    return 0;
}