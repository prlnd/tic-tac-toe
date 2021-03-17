#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLCDNumber>
#include "tictactoe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    TicTacToe *ttt = nullptr;
    QPushButton *pushButtons[TicTacToe::Board::SIZE][TicTacToe::Board::SIZE];

    Ui::MainWindow *ui;
    void move(QPushButton *pb, int row, int col);
    void start();
    void finish(TicTacToe::GameStatus status);
    void setScore(QLCDNumber *lcdScore);
};
#endif // MAINWINDOW_H
