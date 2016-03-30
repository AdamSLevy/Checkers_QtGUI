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
            this, &MainWindow::handleResetBoard);
    connect(board, &CheckerBoardGUI::win,
            this, &MainWindow::handleWin);
    connect(board, &CheckerBoardGUI::turn,
            this, &MainWindow::handleTurn);
    connect(ui->undo, &QPushButton::clicked,
            this, &MainWindow::handleUndo);


    m_currentBB.red_pos = 0;
    m_currentBB.blk_pos = 0;
    board->resetBoard();
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
    m_gameHistory.clear();
    m_currentBB.red_pos = 0;
    m_currentBB.blk_pos = 0;
    ui->undo->setEnabled(false);
    board->resetBoard();
}

void MainWindow::handleTurn(BitBoard bb)
{
    QString playerString;
    if(bb.turn == BLK){
        playerString = "Black";
    } else{
        playerString = "Red";
    }
    ui->statusBar->showMessage(playerString + "'s turn");

    if(m_currentBB.blk_pos != 0 && m_currentBB.red_pos != 0){
        m_gameHistory.push_back(m_currentBB);
    }
    m_currentBB = bb;
    if(m_gameHistory.size() > 0){
        ui->undo->setEnabled(true);
    } else{
        ui->undo->setEnabled(false);
    }
    for(BitBoard b:m_gameHistory){
        print_bb(b);
    }
    print_bb(m_currentBB);
}

void MainWindow::handleResetBoard()
{
    m_gameHistory.clear();
    m_currentBB.red_pos = 0;
    m_currentBB.blk_pos = 0;
    board->resetBoard();
}

void MainWindow::handleUndo()
{
    if(m_gameHistory.size() > 0){
        m_currentBB.red_pos = 0;
        m_currentBB.blk_pos = 0;
        BitBoard last = m_gameHistory.last();
        m_gameHistory.pop_back();
        if(m_gameHistory.size() == 0){
            ui->undo->setEnabled(false);
        }
        board->setBoard(last);
    }
}
