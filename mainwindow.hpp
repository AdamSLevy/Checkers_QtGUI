#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>

#include "checkerboardgui.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handleWin(bool winner);
    void handleTurn(BitBoard bb);
    void handleResetBoard();
    void handleUndo();


private:
    Ui::MainWindow *ui;

    QGraphicsScene * scene;
    CheckerBoardGUI * board;
    QVector<BitBoard> m_gameHistory;
    BitBoard m_currentBB;
};

#endif // MAINWINDOW_H
