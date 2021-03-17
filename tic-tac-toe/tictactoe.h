#ifndef TICTACTOE_H
#define TICTACTOE_H


class TicTacToe
{
public:
    TicTacToe();
    enum Board {
        SIZE = 3,
        AREA = SIZE * SIZE,
        MINROUNDS = SIZE * 2 - 1
    };
    enum class Marker : char {
        BLANK = ' ', X = 'X', O = 'O'
    };
    enum class GameStatus {
        CONTINUES, DRAW, WON
    };

    Marker get(int row, int col);
    Marker move(int row, int col);
    GameStatus checkBoard();
    Marker getLastPlayerMarker();
    Marker getNextPlayerMarker();
    
private:
    Marker board[Board::SIZE][Board::SIZE];
    int round;
    bool player;

    bool isCrossedHorizontally(int row);
    bool isCrossedVertically(int col);
    bool isCrossedDiagonally();
    bool isCrossedAntidiagonally();
};

#endif // TICTACTOE_H
