#ifndef TICTACTOE_H
#define TICTACTOE_H


class TicTacToe
{
public:
    TicTacToe();

private:
    enum class GameStatus {
        CONTINUES, DRAW, WON
    };
    enum class Marker : char {
        BLANK = ' ', X = 'X', O = 'O'
    };

    static const int BOARDSIZE {3};
    static const int BOARDAREA {BOARDSIZE * BOARDSIZE};
    static const int MINROUNDS {BOARDSIZE * 2 - 1};
    Marker board[BOARDSIZE][BOARDSIZE];
    int round;
    bool player;

    void init();
    GameStatus checkBoard();
    bool isCrossedHorizontally(int row);
    bool isCrossedVertically(int col);
    bool isCrossedDiagonally();
    bool isCrossedAntidiagonally();
};

#endif // TICTACTOE_H
