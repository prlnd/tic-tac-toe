#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Tic-Tac-Toe");

    int count {0};
    for (auto &pb : {
         ui->pushButton_0_0, ui->pushButton_0_1, ui->pushButton_0_2,
         ui->pushButton_1_0, ui->pushButton_1_1, ui->pushButton_1_2,
         ui->pushButton_2_0, ui->pushButton_2_1, ui->pushButton_2_2
}) {
        int row {count / TicTacToe::Board::SIZE};
        int col {count % TicTacToe::Board::SIZE};
        this->pushButtons[row][col] = pb;

        QObject::connect(pb, &QPushButton::clicked, this, [=] {
            move(pb, row, col);
        });

        ++count;
    }

    ui->labelX->setText(QString(static_cast<char>(TicTacToe::Icon::X)));
    ui->labelO->setText(QString(static_cast<char>(TicTacToe::Icon::O)));
    ui->labelScoreX->setText("-");
    ui->labelScoreO->setText("-");

    start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::move(QPushButton *pb, int row, int col)
{
    auto marker {ttt.move(row, col)};
    if (marker == TicTacToe::Icon::BLANK)
        return;

    pb->setText(QString(static_cast<char>(marker)));

    auto status {ttt.checkBoard()};
    if (status != TicTacToe::GameStatus::CONTINUES)
        finish(status);
    else
        highlightPlayer(this->ttt.getNextPlayerIcon());
}

void MainWindow::start()
{
    ttt = TicTacToe();
    resetPushButtons();
    highlightPlayer(this->ttt.getNextPlayerIcon());
}

void MainWindow::finish(TicTacToe::GameStatus status)
{
    if (status == TicTacToe::GameStatus::WON) {
        auto marker {ttt.getLastPlayerIcon()};
        setScore(marker == TicTacToe::Icon::X
                 ? ui->labelScoreX
                 : ui->labelScoreO);
        setCrossBold();
        highlightPlayer(this->ttt.getLastPlayerIcon());
    } else {
        highlightPlayer(TicTacToe::Icon::BLANK);
    }

    this->repaint();
    QThread::msleep(1000);
    start();
}

void MainWindow::setScore(QLabel *labelScore)
{
    auto score {labelScore->text().toUInt()};
    labelScore->setText(QString::number(++score));
}

void MainWindow::resetPushButtons()
{
    const auto n {TicTacToe::Board::SIZE};
    for (int i {0}; i < n; ++i) {
        for (int j {0}; j < n; ++j) {
            auto marker {static_cast<char>(ttt.get(i, j))};
            auto &pb {pushButtons[i][j]};
            pb->setText(QString(marker));
            pb->setStyleSheet("");
        }
    }
}

void MainWindow::setCrossBold()
{
    auto cross {ttt.getCross()};

    for (auto &row : this->pushButtons) {
        for (auto &pb : row)
            pb->setStyleSheet("color: lightgrey");
    }

    for (int i {0}; i < TicTacToe::Board::SIZE; ++i) {
        auto row {cross[i][0]};
        auto col {cross[i][1]};
        pushButtons[row][col]->setStyleSheet("");
    }
}

void MainWindow::highlightPlayer(TicTacToe::Icon icon)
{
    switch (icon) {
    case TicTacToe::Icon::X:
        ui->labelX->setStyleSheet("");
        ui->labelO->setStyleSheet("color: grey");
        break;
    case TicTacToe::Icon::O:
        ui->labelX->setStyleSheet("color: grey");
        ui->labelO->setStyleSheet("");
        break;
    default:
        ui->labelX->setStyleSheet("color: grey");
        ui->labelO->setStyleSheet("color: grey");
        break;
    }
}
