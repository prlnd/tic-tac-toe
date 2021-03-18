#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

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
    if (isStopped)
        return;

    auto marker {this->ttt.move(row, col)};
    if (marker == TicTacToe::Icon::BLANK)
        return;

    pb->setText(QString(static_cast<char>(marker)));

    auto status {this->ttt.checkBoard()};
    if (status != TicTacToe::GameStatus::CONTINUES)
        finish(status);
    else
        highlightPlayer(this->ttt.getNextPlayerIcon());
}

void MainWindow::start()
{
    this->ttt = TicTacToe();
    isStopped = false;
    resetPushButtons();
    highlightPlayer(this->ttt.getNextPlayerIcon());
}

void MainWindow::finish(TicTacToe::GameStatus status)
{
    isStopped = true;

    if (status == TicTacToe::GameStatus::WON) {
        auto marker {this->ttt.getLastPlayerIcon()};
        setScore(marker == TicTacToe::Icon::X
                 ? ui->labelScoreX
                 : ui->labelScoreO);
        highlightPlayer(this->ttt.getLastPlayerIcon());
    } else {
        highlightPlayer(TicTacToe::Icon::BLANK);
    }

    highlightRow();

//    this->repaint();
    QTimer::singleShot(1000, this, &MainWindow::start);
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
            auto marker {static_cast<char>(this->ttt.get(i, j))};
            auto &pb {pushButtons[i][j]};
            pb->setText(QString(marker));
            pb->setStyleSheet(this->basicStyle);
        }
    }
}

void MainWindow::highlightRow()
{

    for (auto &row : this->pushButtons) {
        for (auto &pb : row)
            pb->setStyleSheet(this->basicStyle + "color: lightgrey");
    }

    auto cross {this->ttt.getCross()};
    if (cross) {
        for (int i {0}; i < TicTacToe::Board::SIZE; ++i) {
            auto [row, col] {cross[i]};
            pushButtons[row][col]->setStyleSheet(this->basicStyle);
        }
    }
}

void MainWindow::highlightPlayer(TicTacToe::Icon icon)
{
    switch (icon) {
    case TicTacToe::Icon::X:
        ui->labelX->setStyleSheet("");
        ui->labelO->setStyleSheet("color: grey");
        ui->labelScoreX->setStyleSheet("");
        ui->labelScoreO->setStyleSheet("color: grey");
        break;
    case TicTacToe::Icon::O:
        ui->labelX->setStyleSheet("color: grey");
        ui->labelO->setStyleSheet("");
        ui->labelScoreX->setStyleSheet("color: grey");
        ui->labelScoreO->setStyleSheet("");
        break;
    default:
        ui->labelX->setStyleSheet("color: grey");
        ui->labelO->setStyleSheet("color: grey");
        ui->labelScoreX->setStyleSheet("color: grey");
        ui->labelScoreO->setStyleSheet("color: grey");
        break;
    }
}
