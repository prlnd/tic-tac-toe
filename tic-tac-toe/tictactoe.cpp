#include "tictactoe.h"
#include <array>

TicTacToe::TicTacToe() : round(0), player(false)
{
    for (auto &row : this->board) {
        std::fill(std::begin(row), std::end(row), Icon::BLANK);
    }
    std::fill(std::begin(this->cross), std::end(this->cross), std::make_pair(-1, -1));
}

TicTacToe::Icon TicTacToe::get(int row, int col)
{
    return this->board[row][col];
}

TicTacToe::Icon TicTacToe::move(int row, int col)
{
    auto &position {this->board[row][col]};
    if (position != Icon::BLANK)
        return Icon::BLANK;

    position = getNextPlayerIcon();
    ++this->round;
    this->player = !this->player;

    return position;
}

TicTacToe::Icon TicTacToe::getLastPlayerIcon()
{
    return this->player ? Icon::X : Icon::O;
}

TicTacToe::Icon TicTacToe::getNextPlayerIcon()
{
    return this->player ? Icon::O : Icon::X;
}

const std::pair<int, int> *TicTacToe::getCross()
{
    return this->cross->first >= 0 ? this->cross : nullptr;
}

TicTacToe::GameStatus TicTacToe::checkBoard()
{
    if (this->round < this->MINROUNDS)
        return GameStatus::CONTINUES;

    for (int i {0}; i < this->Board::SIZE; ++i) {
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
    if (this->board[row][0] == Icon::BLANK)
        return false;

    for (int i {0}; i < this->Board::SIZE - 1; ++i) {
        if (this->board[row][i] != this->board[row][i + 1])
            return false;
    }

    for (int i {0}; i < this->Board::SIZE; ++i) {
        this->cross[i] = {row, i};
    }

    return true;
}

bool TicTacToe::isCrossedVertically(int col)
{
    if (this->board[0][col] == Icon::BLANK)
        return false;

    for (int i {0}; i < this->Board::SIZE - 1; ++i) {
        if (this->board[i][col] != this->board[i + 1][col])
            return false;
    }

    for (int i {0}; i < this->Board::SIZE; ++i) {
        this->cross[i] = {i, col};
    }

    return true;
}

bool TicTacToe::isCrossedDiagonally()
{
    if (this->board[0][0] == Icon::BLANK)
        return false;

    for (int i {0}; i < this->Board::SIZE - 1; ++i) {
        if (this->board[i][i] != this->board[i + 1][i + 1])
            return false;
    }

    for (int i {0}; i < this->Board::SIZE; ++i) {
        this->cross[i] = {i, i};
    }

    return true;
}

bool TicTacToe::isCrossedAntidiagonally()
{
    const int n {this->Board::SIZE - 1};

    if (this->board[0][n] == Icon::BLANK)
        return false;

    for (int i {0}; i < n; ++i) {
        if (this->board[i][n - i] != this->board[i + 1][n - i - 1])
            return false;
    }

    for (int i {0}; i < this->Board::SIZE; ++i) {
        this->cross[i] = {i, n - i};
    }

    return true;
}
