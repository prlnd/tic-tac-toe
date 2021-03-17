#include "tictactoe.h"
#include <QPushButton>
#include <algorithm>

TicTacToe::TicTacToe() : round(0), player(false)
{
    for (auto &row : this->board) {
        std::fill(std::begin(row), std::end(row), Marker::BLANK);
    }
}

TicTacToe::Marker TicTacToe::get(int row, int col)
{
    return this->board[row][col];
}

TicTacToe::Marker TicTacToe::move(int row, int col)
{
    auto &position = this->board[row][col];
    if (position != Marker::BLANK)
        return Marker::BLANK;

    ++this->round;
    this->player = !this->player;
    position = getLastPlayerMarker();

    return position;
}

TicTacToe::Marker TicTacToe::getLastPlayerMarker()
{
    return this->player ? Marker::X : Marker::O;
}

TicTacToe::Marker TicTacToe::getNextPlayerMarker()
{
    return this->player ? Marker::O : Marker::X;
}

TicTacToe::GameStatus TicTacToe::checkBoard()
{
    if (this->round < this->MINROUNDS)
        return GameStatus::CONTINUES;

    for (int i = 0; i < this->Board::SIZE; ++i) {
        if (isCrossedHorizontally(i) || isCrossedVertically(i))
            return GameStatus::WON;
    }

    if (isCrossedDiagonally() || isCrossedAntidiagonally())
        return GameStatus::WON;

    return this->round < this->Board::AREA
            ? GameStatus::CONTINUES
            : GameStatus::DRAW;
}

bool TicTacToe::isCrossedHorizontally(int row)
{
    if (this->board[row][0] == Marker::BLANK)
        return false;

    for (int i = 0; i < this->Board::SIZE - 1; ++i) {
        if (this->board[row][i] != this->board[row][i + 1])
            return false;
    }

    return true;
}

bool TicTacToe::isCrossedVertically(int col)
{
    if (this->board[0][col] == Marker::BLANK)
        return false;

    for (int i = 0; i < this->Board::SIZE - 1; ++i) {
        if (this->board[i][col] != this->board[i + 1][col])
            return false;
    }

    return true;
}

bool TicTacToe::isCrossedDiagonally()
{
    if (this->board[0][0] == Marker::BLANK)
        return false;

    for (int i = 0; i < this->Board::SIZE - 1; ++i) {
        if (this->board[i][i] != this->board[i + 1][i + 1])
            return false;
    }

    return true;
}

bool TicTacToe::isCrossedAntidiagonally()
{
    const int n {this->Board::SIZE - 1};

    if (this->board[0][n] == Marker::BLANK)
        return false;

    for (int i = 0; i < n; ++i) {
        if (this->board[i][n - i] != this->board[i + 1][n - i - 1])
            return false;
    }

    return true;
}
