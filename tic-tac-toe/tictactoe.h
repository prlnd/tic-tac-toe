#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <utility>

class TicTacToe
{
public:
    TicTacToe();
    enum Board {
        SIZE = 3,
        AREA = SIZE * SIZE,
        MINROUNDS = SIZE * 2 - 1
    };
    enum class Icon : char {
        BLANK = ' ', X = 'X', O = 'O'
    };
    enum class GameStatus {
        CONTINUES, DRAW, WON
    };

    Icon get(int row, int col);
    Icon move(int row, int col);
    GameStatus checkBoard();
    Icon getLastPlayerIcon();
    Icon getNextPlayerIcon();
    const std::pair<int, int> *getCross();
    
private:
    Icon board[Board::SIZE][Board::SIZE];
    int round;
    bool player;
    std::pair<int, int> cross[Board::SIZE];

    bool isCrossedHorizontally(int row);
    bool isCrossedVertically(int col);
    bool isCrossedDiagonally();
    bool isCrossedAntidiagonally();
};

#endif // TICTACTOE_H
