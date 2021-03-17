#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Tic-Tac-Toe");

    int count = 0;
    for (auto &pb : {
         ui->pushButton_0_0, ui->pushButton_0_1, ui->pushButton_0_2,
         ui->pushButton_1_0, ui->pushButton_1_1, ui->pushButton_1_2,
         ui->pushButton_2_0, ui->pushButton_2_1, ui->pushButton_2_2
}) {
        int row = count / TicTacToe::Board::SIZE;
        int col = count % TicTacToe::Board::SIZE;
        this->pushButtons[row][col] = pb;

        QObject::connect(pb, &QPushButton::clicked, this, [=] {
            move(pb, row, col);
        });

        ++count;
    }

    ui->labelX->setText(QString(static_cast<char>(TicTacToe::Marker::X)));
    ui->labelO->setText(QString(static_cast<char>(TicTacToe::Marker::O)));
    ui->lcdScoreX->display(0);
    ui->lcdScoreO->display(0);

    start();
}

MainWindow::~MainWindow()
{
    delete ttt;
    delete ui;
}

void MainWindow::move(QPushButton *pb, int row, int col)
{
    auto marker = ttt->move(row, col);
    if (marker == TicTacToe::Marker::BLANK)
        return;

    pb->setText(QString(static_cast<char>(marker)));
    auto status = ttt->checkBoard();
    if (status != TicTacToe::GameStatus::CONTINUES)
        finish(status);
}

void MainWindow::start()
{
    delete ttt;
    ttt = new TicTacToe;
    const auto n = TicTacToe::Board::SIZE;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            auto marker = static_cast<char>(ttt->get(i, j));
            pushButtons[i][j]->setText(QString(marker));
        }
    }
}

void MainWindow::finish(TicTacToe::GameStatus status)
{
    if (status == TicTacToe::GameStatus::WON) {
        auto marker = ttt->getPlayerMarker();
        setScore(marker == TicTacToe::Marker::X
                 ? ui->lcdScoreX
                 : ui->lcdScoreO);
    }
    this->repaint();
    QThread::sleep(1);
    start();
}

void MainWindow::setScore(QLCDNumber *lcdScore)
{
    auto score = lcdScore->intValue();
    lcdScore->display(++score);
}

