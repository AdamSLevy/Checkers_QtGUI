#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QRectF sceneRect = ui->graphicsView->rect();
    scene = new QGraphicsScene(this);
    board = new CheckerBoardGUI;
//    board->setTransform(QTransform::fromScale(2,2),true);
//    board->setTransform(QTransform::fromScale(6,6),true);

    scene->addItem(board);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    connect(ui->resetGame, &QPushButton::clicked,
            board, &CheckerBoardGUI::resetBoard);
    connect(board, &CheckerBoardGUI::win,
            this, &MainWindow::handleWin);
    connect(board, &CheckerBoardGUI::turn,
            this, &MainWindow::handleTurn);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleWin(bool winner)
{
    QMessageBox winMsg;
    winMsg.setIcon(QMessageBox::Information);
    winMsg.setText("Game Over!");
    QString winnerString;
    if(winner == BLK){
        winnerString = "Black";
    } else{
        winnerString = "Red";
    }
    winMsg.setInformativeText(winnerString + " wins!");
    winMsg.exec();
    board->resetBoard();
}

void MainWindow::handleTurn(bool turn)
{
    QString playerString;
    if(turn == BLK){
        playerString = "Black";
    } else{
        playerString = "Red";
    }
    ui->statusBar->showMessage(playerString + "'s turn");
}
