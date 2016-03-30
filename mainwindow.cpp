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
}

MainWindow::~MainWindow()
{
    delete ui;
}
