#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
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

private slots:
    void start();

private:
    const QString basicStyle {"background-color: white; border: none;"};
    TicTacToe ttt;
    QPushButton *pushButtons[TicTacToe::Board::SIZE][TicTacToe::Board::SIZE];
    bool isStopped;

    Ui::MainWindow *ui;
    void move(QPushButton *pb, int row, int col);
    void finish(TicTacToe::GameStatus status);
    void setScore(QLabel *labelScore);
    void resetPushButtons();
    void highlightRow();
    void highlightPlayer(TicTacToe::Icon icon);
};
#endif // MAINWINDOW_H
